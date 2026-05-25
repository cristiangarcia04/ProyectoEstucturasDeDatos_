#include "Juego.h"
#include "Acusacion.h"
#include <algorithm>
#include <chrono>
#include <iostream>
#include <limits>
#include <cctype>
#include <map>
using namespace std;

Juego::Juego() {
    inicio = nullptr;
    pistasEncontradas = 0;
    rng.seed(static_cast<unsigned int>(chrono::system_clock::now().time_since_epoch().count()));
    raizScore = nullptr;
    construirCiudad();
}

Juego::~Juego() {
    limpiarCiudad();
    liberarScores(raizScore);
}

void Juego::menuPrincipal() {
    char opcion;
    do {
        cout << "\n========== EL CASO DEL DETECTIVE ==========" << endl;
        cout << "1. Jugar" << endl;
        cout << "2. Consultar mejor puntaje de un detective" << endl;
        cout << "3. Ver ranking historico ABB" << endl;
        cout << "0. Salir" << endl;
        cout << "Opcion: ";
        cin >> opcion;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (opcion == '1') jugar();
        else if (opcion == '2') consultarPuntaje();
        else if (opcion == '3') mostrarRanking();
        else if (opcion != '0') cout << "Opcion no valida.\n";
    } while (opcion != '0');
}

void Juego::construirCiudad() {
    limpiarCiudad();

    map<int, Ubicacion*> filaAnterior;

    for (int f = 0; f < FILAS; f++) {
        Ubicacion* izquierda = nullptr;
        for (int c = 0; c < COLUMNAS; c++) {
            Ubicacion* actual = new Ubicacion(f, c);
            if (f == 0 || c == 0 || f == FILAS - 1 || c == COLUMNAS - 1) {
                actual->tipo = "borde";
                actual->simbolo = BORDE;
                actual->visible = true;
            }
            ubicaciones.push_back(actual);
            if (f == 0 && c == 0) inicio = actual;

            actual->izquierda = izquierda;
            if (izquierda != nullptr) izquierda->derecha = actual;

            actual->arriba = filaAnterior.count(c) ? filaAnterior[c] : nullptr;
            if (actual->arriba != nullptr) actual->arriba->abajo = actual;
            filaAnterior[c] = actual;
            izquierda = actual;
        }
    }
}

void Juego::limpiarCiudad() {
    for (Ubicacion* u : ubicaciones) delete u;
    ubicaciones.clear();
    inicio = nullptr;
}

Ubicacion* Juego::obtener(int fila, int columna) const {
    Ubicacion* actual = inicio;
    for (int f = 0; actual != nullptr && f < fila; f++) actual = actual->abajo;
    for (int c = 0; actual != nullptr && c < columna; c++) actual = actual->derecha;
    return actual;
}

list<Ubicacion*> Juego::posicionesInternasLibres(bool incluirVisitadas) const {
    list<Ubicacion*> libres;
    for (Ubicacion* u : ubicaciones) {
        if (u->fila > 0 && u->fila < FILAS - 1 && u->columna > 0 && u->columna < COLUMNAS - 1 &&
            u->tipo == "libre" && u->pista == nullptr && u->testigo == nullptr &&
            (incluirVisitadas || !u->visitado)) {
            libres.push_back(u);
        }
    }
    return libres;
}

Ubicacion* Juego::posicionAleatoriaLibre(bool incluirVisitadas) {
    list<Ubicacion*> libres = posicionesInternasLibres(incluirVisitadas);
    if (libres.empty()) return nullptr;
    uniform_int_distribution<int> dist(0, static_cast<int>(libres.size()) - 1);
    int salto = dist(rng);
    auto it = libres.begin();
    advance(it, salto);
    return *it;
}

void Juego::configurarNuevaPartida(const string& nombreDetective) {
    construirCiudad();
    pistasMapa.clear();
    testigosMapa.clear();
    while (!pistasRecolectadas.empty()) pistasRecolectadas.pop();
    while (!declaracionesPendientes.empty()) declaracionesPendientes.pop();
    sospechosos.clear();
    atributosRevelados.clear();
    detective = Detective(nombreDetective);
    culpableReal = "";
    pistasEncontradas = 0;

    crearSospechosos();
    colocarCallejones();
    colocarPistas();
    colocarTestigos();
    colocarDetective();
}

void Juego::colocarCallejones() {
    for (int i = 0; i < TOTAL_CALLEJONES; i++) {
        Ubicacion* u = posicionAleatoriaLibre(true);
        if (u == nullptr) return;
        u->tipo = "callejon";
        u->simbolo = CALLEJON;
        u->visible = false;
    }
}

void Juego::colocarPistas() {
    vector<string> tipos = {"huella", "coartada", "testimonio", "prueba_forense"};
    uniform_int_distribution<int> dist(0, static_cast<int>(tipos.size()) - 1);

    for (int i = 0; i < TOTAL_PISTAS; i++) {
        Ubicacion* u = posicionAleatoriaLibre(true);
        if (u == nullptr) return;
        pistasMapa.emplace_back(tipos[dist(rng)], u->fila, u->columna);
        Pista& pista = pistasMapa.back();
        u->tipo = "pista";
        u->simbolo = pista.simbolo;
        u->pista = &pista;
        u->visible = false;
    }
}

void Juego::colocarTestigos() {
    for (int i = 0; i < TOTAL_TESTIGOS; i++) {
        Ubicacion* u = posicionAleatoriaLibre(true);
        if (u == nullptr) return;
        testigosMapa.emplace_back("Vi un detalle que ayuda a identificar al culpable.", u->fila, u->columna);
        Testigo& testigo = testigosMapa.back();
        u->tipo = "testigo";
        u->simbolo = TESTIGO;
        u->testigo = &testigo;
        u->visible = false;
    }
}

void Juego::colocarDetective() {
    Ubicacion* u = posicionAleatoriaLibre(true);
    if (u == nullptr) return;
    detective.ubicar(u);
}

void Juego::crearSospechosos() {
    vector<Sospechoso> base = {
        Sospechoso("Carlos", {"alto", "cabello negro", "zurdo", "nariz recta", "hombre"}),
        Sospechoso("Diana", {"alta", "cabello rojo", "diestra", "piel clara", "mujer"}),
        Sospechoso("Eduardo", {"bajo", "cabello castano", "zurdo", "piel morena", "hombre"}),
        Sospechoso("Fernanda", {"alta", "cabello rojo", "zurda", "nariz pequena", "mujer"}),
        Sospechoso("Gonzalo", {"alto", "cabello rubio", "diestro", "piel clara", "hombre"}),
        Sospechoso("Hilda", {"alta", "cabello negro", "diestra", "piel morena", "mujer"}),
        Sospechoso("Ivan", {"mediano", "cabello castano", "zurdo", "nariz aguileña", "hombre"}),
        Sospechoso("Juliana", {"baja", "cabello rubio", "diestra", "piel clara", "mujer"}),
        Sospechoso("Kevin", {"alto", "cabello rojo", "diestro", "piel morena", "hombre"}),
        Sospechoso("Laura", {"mediana", "cabello negro", "zurda", "nariz recta", "mujer"})
    };

    shuffle(base.begin(), base.end(), rng);
    for (int i = 0; i < TOTAL_SOSPECHOSOS; i++) {
        sospechosos[base[i].nombre] = base[i];
    }

    uniform_int_distribution<int> dist(0, TOTAL_SOSPECHOSOS - 1);
    int indiceCulpable = dist(rng);
    auto it = sospechosos.begin();
    advance(it, indiceCulpable);
    it->second.culpable = true;
    culpableReal = it->second.nombre;
}

bool Juego::atributoYaRevelado(const string& atributo) const {
    return find(atributosRevelados.begin(), atributosRevelados.end(), atributo) != atributosRevelados.end();
}

void Juego::revelarAtributoCulpable() {
    Sospechoso& culpable = sospechosos[culpableReal];
    vector<string> pendientes;
    for (const string& atributo : culpable.atributos) {
        if (!atributoYaRevelado(atributo)) pendientes.push_back(atributo);
    }

    if (pendientes.empty()) {
        cout << "Ya se revelaron todos los atributos del culpable.\n";
        return;
    }

    uniform_int_distribution<int> dist(0, static_cast<int>(pendientes.size()) - 1);
    string revelado = pendientes[dist(rng)];
    atributosRevelados.push_back(revelado);
    cout << "Dato veridico revelado sobre el culpable: " << revelado << endl;
}

char Juego::simboloVisible(Ubicacion* u) const {
    if (u == nullptr) return '?';
    if (u == detective.posicionAct) return DETECTIVE;
    if (u->tipo == "borde") return BORDE;
    if (u->visible) {
        if (u->tipo == "callejon") return CALLEJON;
        if (u->tipo == "testigo" && u->testigo != nullptr && !u->testigo->encontrado) return TESTIGO;
        return ' ';
    }
    return VACIO;
}

void Juego::mostrarTablero() const {
    cout << endl;
    detective.mostrarPuntaje();
    for (int f = 0; f < FILAS; f++) {
        for (int c = 0; c < COLUMNAS; c++) {
            cout << simboloVisible(obtener(f, c)) << ' ';
        }
        cout << endl;
    }
    cout << "Pistas recolectadas: " << pistasEncontradas << "/" << TOTAL_PISTAS << endl;
}

void Juego::jugar() {
    string nombre;
    cout << "\nNombre del detective: ";
    getline(cin, nombre);
    if (nombre.empty()) nombre = "Detective";
    configurarNuevaPartida(nombre);

    cout << "\nComandos: W/A/S/D mover, T ver pila de pistas, X usar ultima pista, s minuscula ver sospechosos, I interrogar, Q rendirse.\n";
    mostrarTablero();

    char comando;
    bool rendido = false;
    while (pistasEncontradas < TOTAL_PISTAS && !rendido) {
        cout << "\nComando > ";
        cin >> comando;
        if (comando == 's') {
            mostrarSospechosos();
            continue;
        }
        comando = static_cast<char>(toupper(static_cast<unsigned char>(comando)));

        if (comando == ARRIBA || comando == ABAJO || comando == IZQUIERDA || comando == DERECHA) {
            intentarMover(comando);
            mostrarTablero();
        } else if (comando == 'T') {
            mostrarPilaPistas();
        } else if (comando == 'X') {
            usarUltimaPista();
            mostrarTablero();
        } else if (comando == 'S') {
            mostrarSospechosos();
        } else if (comando == 'I') {
            interrogarTestigo();
        } else if (comando == 'Q') {
            rendido = true;
            cout << "Te rendiste. El caso queda fracasado.\n";
            detective.puntaje *= 2;
            raizScore = insertarScore(raizScore, detective.nombre, detective.puntaje);
        } else {
            cout << "Comando no valido.\n";
        }
    }

    if (!rendido) faseAcusacion();
}

void Juego::intentarMover(char direccion) {
    Ubicacion* destino = nullptr;
    if (direccion == ARRIBA) destino = detective.posicionAct->arriba;
    else if (direccion == ABAJO) destino = detective.posicionAct->abajo;
    else if (direccion == IZQUIERDA) destino = detective.posicionAct->izquierda;
    else if (direccion == DERECHA) destino = detective.posicionAct->derecha;

    detective.aumentarPuntaje();

    if (destino == nullptr || destino->tipo == "borde") {
        cout << "No puedes atravesar los edificios (#).\n";
        return;
    }
    if (destino->tipo == "callejon") {
        destino->visible = true;
        cout << "Callejon cerrado descubierto (|). Debes buscar otra ruta.\n";
        return;
    }

    detective.mover(destino);
    revisarContenido(destino);
}

void Juego::revisarContenido(Ubicacion* ubicacion) {
    if (ubicacion->pista != nullptr && !ubicacion->pista->recogido) {
        ubicacion->pista->recogido = true;
        Pista encontrada = *ubicacion->pista;
        pistasRecolectadas.push(encontrada);
        pistasEncontradas++;
        cout << "Recogiste una pista: " << encontrada.getNombre() << " (" << encontrada.simbolo << ").\n";
        ubicacion->pista = nullptr;
        ubicacion->tipo = "libre";
        ubicacion->simbolo = ' ';
        revelarAtributoCulpable();
    }

    if (ubicacion->testigo != nullptr && !ubicacion->testigo->encontrado) {
        ubicacion->testigo->encontrado = true;
        declaracionesPendientes.push(*ubicacion->testigo);
        cout << "Encontraste un testigo. Su declaracion entro a la cola. Usa I para interrogar.\n";
        ubicacion->testigo = nullptr;
        ubicacion->tipo = "libre";
        ubicacion->simbolo = ' ';
    }
}

void Juego::mostrarPilaPistas() const {
    cout << "\n" << detective.nombre << ", mira las pistas que llevas (Pila):\n";
    if (pistasRecolectadas.empty()) {
        cout << "  La pila esta vacia.\n";
        return;
    }

    stack<Pista> copia = pistasRecolectadas;
    int posicion = 0;
    while (!copia.empty()) {
        Pista p = copia.top();
        copia.pop();
        cout << "  ['# " << p.simbolo << " #']";
        if (posicion == 0) cout << " <- ultima, se usa con X";
        cout << "  " << p.getNombre() << endl;
        posicion++;
    }
}

void Juego::usarUltimaPista() {
    if (pistasRecolectadas.empty()) {
        cout << "No tienes pistas para usar.\n";
        return;
    }

    Pista pista = pistasRecolectadas.top();
    pistasRecolectadas.pop();
    if (pistasEncontradas > 0) pistasEncontradas--;

    cout << "Usaste la pista: " << pista.getNombre() << endl;
    if (pista.tipo == "huella") {
        detective.puntaje /= 2;
        cout << "Beneficio: tu puntaje se redujo a la mitad.\n";
    } else if (pista.tipo == "coartada") {
        eliminarCallejonesAleatorios(2);
        cout << "Beneficio: se eliminaron 2 callejones cerrados aleatorios.\n";
    } else if (pista.tipo == "testimonio") {
        uniform_int_distribution<int> dist(0, 1);
        if (dist(rng) == 0) {
            detective.puntaje = 0;
            cout << "El testimonio te ayudo: puntaje en cero.\n";
        } else {
            detective.puntaje *= 2;
            cout << "El testimonio confundio el caso: puntaje duplicado.\n";
        }
    } else if (pista.tipo == "prueba_forense") {
        teletransportarDetective();
        cout << "Beneficio: te moviste aleatoriamente a otra ubicacion no descubierta.\n";
    }

    reubicarPista(pista);
    resetearVisibilidad();
    cout << "La pista volvio al mapa y se ocultaron de nuevo las calles visitadas.\n";
}

void Juego::reubicarPista(Pista pistaUsada) {
    Ubicacion* u = posicionAleatoriaLibre(true);
    if (u == nullptr) return;
    pistasMapa.push_back(Pista(pistaUsada.tipo, u->fila, u->columna));
    Pista& nueva = pistasMapa.back();
    u->tipo = "pista";
    u->simbolo = nueva.simbolo;
    u->pista = &nueva;
    u->visible = false;
}

void Juego::resetearVisibilidad() {
    for (Ubicacion* u : ubicaciones) {
        if (u->tipo != "borde" && u != detective.posicionAct) {
            u->visible = (u->tipo == "callejon" && u->visible);
            u->visitado = false;
        }
    }
    if (detective.posicionAct != nullptr) {
        detective.posicionAct->visible = true;
        detective.posicionAct->visitado = true;
    }
}

void Juego::eliminarCallejonesAleatorios(int cantidad) {
    list<Ubicacion*> callejones;
    for (Ubicacion* u : ubicaciones) if (u->tipo == "callejon") callejones.push_back(u);

    for (int i = 0; i < cantidad && !callejones.empty(); i++) {
        uniform_int_distribution<int> dist(0, static_cast<int>(callejones.size()) - 1);
        int salto = dist(rng);
        auto it = callejones.begin();
        advance(it, salto);
        Ubicacion* u = *it;
        u->tipo = "libre";
        u->simbolo = ' ';
        u->visible = true;
        callejones.erase(it);
    }
}

void Juego::teletransportarDetective() {
    Ubicacion* u = posicionAleatoriaLibre(false);
    if (u == nullptr) u = posicionAleatoriaLibre(true);
    if (u != nullptr) detective.mover(u);
}

void Juego::mostrarSospechosos() const {
    cout << "\n" << detective.nombre << ", sospechosos del caso (Tabla Hash):\n";
    cout << "Atributos confirmados del culpable: ";
    if (atributosRevelados.empty()) cout << "-";
    for (size_t i = 0; i < atributosRevelados.size(); i++) {
        cout << atributosRevelados[i];
        if (i + 1 < atributosRevelados.size()) cout << ", ";
    }
    cout << endl;

    for (const auto& par : sospechosos) {
        cout << "Bucket hash " << (hash<string>{}(par.first) % 17) << " -> ";
        par.second.mostrarConRevelados(atributosRevelados);
    }
}

void Juego::interrogarTestigo() {
    if (declaracionesPendientes.empty()) {
        cout << "No hay declaraciones pendientes en la cola.\n";
        return;
    }

    Testigo testigo = declaracionesPendientes.front();
    declaracionesPendientes.pop();
    cout << "\nInterrogando al siguiente testigo de la Cola (FIFO)...\n";
    testigo.mostrar();
    revelarAtributoCulpable();
}

void Juego::faseAcusacion() {
    cout << "\n" << detective.nombre << ", has recolectado las 10 pistas. Es momento de acusar.\n";
    mostrarSospechosos();
    cout << "\nSospechosos disponibles: ";
    int i = 0;
    for (const auto& par : sospechosos) {
        if (i++ > 0) cout << ", ";
        cout << par.first;
    }
    cout << "\n¿A quien acusas? > ";
    string acusado;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, acusado);

    bool gano = Acusacion::acusar(acusado, sospechosos, culpableReal);
    if (gano) {
        cout << "¡Caso resuelto! " << culpableReal << " era la persona culpable.\n";
    } else {
        detective.puntaje *= 2;
        cout << "Acusacion incorrecta. El caso se cierra como fracasado.\n";
        cout << "La persona culpable era: " << culpableReal << endl;
    }
    cout << "Puntaje final: " << detective.puntaje << " movimientos.\n";
    raizScore = insertarScore(raizScore, detective.nombre, detective.puntaje);
}

Juego::NodoScore* Juego::insertarScore(NodoScore* nodo, const string& nombre, int puntaje) {
    if (nodo == nullptr) return new NodoScore(nombre, puntaje);
    if (puntaje < nodo->mejorPuntaje) nodo->izquierda = insertarScore(nodo->izquierda, nombre, puntaje);
    else if (puntaje > nodo->mejorPuntaje) nodo->derecha = insertarScore(nodo->derecha, nombre, puntaje);
    else {
        if (nombre < nodo->nombre) nodo->izquierda = insertarScore(nodo->izquierda, nombre, puntaje);
        else if (nombre > nodo->nombre) nodo->derecha = insertarScore(nodo->derecha, nombre, puntaje);
    }

    if (nodo->nombre == nombre && puntaje < nodo->mejorPuntaje) nodo->mejorPuntaje = puntaje;
    return nodo;
}

Juego::NodoScore* Juego::buscarScore(NodoScore* nodo, const string& nombre) const {
    if (nodo == nullptr) return nullptr;
    if (nodo->nombre == nombre) return nodo;
    NodoScore* izq = buscarScore(nodo->izquierda, nombre);
    if (izq != nullptr) return izq;
    return buscarScore(nodo->derecha, nombre);
}

void Juego::consultarPuntaje() {
    string nombre;
    cout << "Nombre del detective a buscar: ";
    getline(cin, nombre);
    NodoScore* encontrado = buscarScore(raizScore, nombre);
    if (encontrado == nullptr) cout << nombre << " no tiene puntajes registrados.\n";
    else cout << nombre << " ya jugo. Mejor puntaje: " << encontrado->mejorPuntaje << endl;
}

void Juego::mostrarRanking() {
    cout << "\nRanking historico por ABB (menor puntaje a mayor):\n";
    if (raizScore == nullptr) cout << "  No hay puntajes registrados.\n";
    else imprimirScores(raizScore);
}

void Juego::imprimirScores(NodoScore* nodo) const {
    if (nodo == nullptr) return;
    imprimirScores(nodo->izquierda);
    cout << "  " << nodo->nombre << " -> " << nodo->mejorPuntaje << endl;
    imprimirScores(nodo->derecha);
}

void Juego::liberarScores(NodoScore* nodo) {
    if (nodo == nullptr) return;
    liberarScores(nodo->izquierda);
    liberarScores(nodo->derecha);
    delete nodo;
}
