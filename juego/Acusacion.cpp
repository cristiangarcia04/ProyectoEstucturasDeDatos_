#include "Acusacion.h"
#include <iostream>
using namespace std;

bool Acusacion::acusar(const string& nombreAcusado,
                       unordered_map<string, Sospechoso>& tablaSospechosos,
                       const string& culpableReal) {
    cout << "\nBusqueda en Tabla Hash por nombre: hash[\"" << nombreAcusado << "\"]" << endl;
    auto encontrado = tablaSospechosos.find(nombreAcusado);
    if (encontrado == tablaSospechosos.end()) {
        cout << "Ese sospechoso no existe en la Tabla Hash. Busqueda promedio O(1)." << endl;
        return false;
    }

    cout << "Sospechoso encontrado con busqueda promedio O(1)." << endl;
    return encontrado->second.nombre == culpableReal;
}
