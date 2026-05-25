#ifndef JUEGO_H
#define JUEGO_H

#include <list>
#include <queue>
#include <stack>
#include <string>
#include <unordered_map>
#include <vector>
#include <random>
#include "../datos/Predefinidos.h"
#include "../entidades/Detective.h"
#include "../entidades/Pista.h"
#include "../entidades/Sospechoso.h"
#include "../entidades/Testigo.h"
#include "../entidades/Ubicacion.h"
using namespace std;

class Juego {
private:
    struct NodoScore {
        string nombre;
        int mejorPuntaje;
        NodoScore* izquierda;
        NodoScore* derecha;
        NodoScore(string n, int p) : nombre(n), mejorPuntaje(p), izquierda(nullptr), derecha(nullptr) {}
    };

    Ubicacion* inicio;
    list<Ubicacion*> ubicaciones;
    list<Pista> pistasMapa;
    list<Testigo> testigosMapa;
    stack<Pista> pistasRecolectadas;
    queue<Testigo> declaracionesPendientes;
    unordered_map<string, Sospechoso> sospechosos;
    vector<string> atributosRevelados;
    Detective detective;
    string culpableReal;
    int pistasEncontradas;
    mt19937 rng;
    NodoScore* raizScore;

    void construirCiudad();
    void limpiarCiudad();
    Ubicacion* obtener(int fila, int columna) const;
    list<Ubicacion*> posicionesInternasLibres(bool incluirVisitadas = true) const;
    Ubicacion* posicionAleatoriaLibre(bool incluirVisitadas = true);
    void configurarNuevaPartida(const string& nombreDetective);
    void colocarCallejones();
    void colocarPistas();
    void colocarTestigos();
    void colocarDetective();
    void crearSospechosos();
    void revelarAtributoCulpable();
    void mostrarTablero() const;
    char simboloVisible(Ubicacion* u) const;
    void intentarMover(char direccion);
    void revisarContenido(Ubicacion* ubicacion);
    void mostrarPilaPistas() const;
    void usarUltimaPista();
    void reubicarPista(Pista pistaUsada);
    void resetearVisibilidad();
    void eliminarCallejonesAleatorios(int cantidad);
    void teletransportarDetective();
    void mostrarSospechosos() const;
    void interrogarTestigo();
    void faseAcusacion();
    bool atributoYaRevelado(const string& atributo) const;

    NodoScore* insertarScore(NodoScore* nodo, const string& nombre, int puntaje);
    NodoScore* buscarScore(NodoScore* nodo, const string& nombre) const;
    void imprimirScores(NodoScore* nodo) const;
    void liberarScores(NodoScore* nodo);

public:
    Juego();
    ~Juego();

    void menuPrincipal();
    void jugar();
    void consultarPuntaje();
    void mostrarRanking();
};

#endif
