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
    this->declaracion = declaracion;
    this->fila = fila;
    this->columna = columna;
    encontrado = false;
}

void Testigo::mostrar() const {
    cout << "El testigo dice: " << declaracion << endl;
}
