//
// Created by garci on 18/05/2026.
//

#ifndef TESTIGO_H
#define TESTIGO_H
#include <string>
#include "Ubicacion.h"
using namespace std;


class Testigo {
public:
    string declaracion;
    int fila;
    int columna;
    bool encontrado;

    Testigo();
    Testigo(string declaracion, int fila, int columna);

    void mostrar();
};



#endif //TESTIGO_H
