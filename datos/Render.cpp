//
// Created by garci on 18/05/2026.
//

#include "Render.h"
#include <iostream>
using namespace std;

void Render::imprimirTablero(char tablero[FILAS][COLUMNAS]) {
    for (int i = 0; i < FILAS; i++) {
        for (int j = 0; j < COLUMNAS; j++) {
            cout << tablero[i][j] << " ";
        }
        cout << endl;
    }
}