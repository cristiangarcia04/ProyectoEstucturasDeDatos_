//
// Created by garci on 18/05/2026.
//

#include "Testigo.h"
#include <iostream>
using namespace std;

Testigo::Testigo() {
    declaracion = "";
    fila = 0;
    columna = 0;
    encontrado = false;
}

Testigo::Testigo(string declaracion, int fila, int columna) {
    declaracion = declaracion;
    fila = fila;
    columna = columna;
    encontrado = false;
}

void Testigo::mostrar() {
    cout << "El testigo dice: " << declaracion << endl;
}

