#include "Ubicacion.h"

Ubicacion::Ubicacion(int f, int c) {
    fila = f;
    columna = c;
    tipo = "libre";
    simbolo = 'o';
    visitado = false;
    visible = false;
    pista = nullptr;
    testigo = nullptr;
    arriba = nullptr;
    abajo = nullptr;
    izquierda = nullptr;
    derecha = nullptr;
}
