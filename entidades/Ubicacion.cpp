//
// Created by garci on 18/05/2026.
//

#include "Ubicacion.h"


Ubicacion::Ubicacion(int f, int c) {
    fila = f;
    columna = c;
    tipo = "libre";
    simbolo = 'o';
    visitado = false;
    arriba = nullptr;
    abajo = nullptr;
    izquierda = nullptr;
    derecha = nullptr;
}
