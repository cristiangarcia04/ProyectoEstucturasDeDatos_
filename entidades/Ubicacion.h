//
// Created by garci on 18/05/2026.
//

#ifndef UBICACION_H
#define UBICACION_H
#include <string>
using namespace std;


struct Ubicacion {
    string tipo;
    int fila;
    int columna;
    int visitado;
    char simbolo;

    Ubicacion* arriba;
    Ubicacion* abajo;
    Ubicacion* izquierda;
    Ubicacion* derecha;

    Ubicacion(int f, int c);
};



#endif //UBICACION_H
