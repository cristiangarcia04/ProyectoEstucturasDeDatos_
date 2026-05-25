#ifndef UBICACION_H
#define UBICACION_H

#include <string>
using namespace std;

struct Pista;
struct Testigo;

struct Ubicacion {
    string tipo;          // borde, libre, callejon, pista, testigo
    int fila;
    int columna;
    bool visitado;
    bool visible;
    char simbolo;         // simbolo real del contenido
    Pista* pista;
    Testigo* testigo;

    Ubicacion* arriba;
    Ubicacion* abajo;
    Ubicacion* izquierda;
    Ubicacion* derecha;

    Ubicacion(int f, int c);
};

#endif
