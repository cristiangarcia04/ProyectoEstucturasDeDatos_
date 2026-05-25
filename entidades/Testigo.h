#ifndef TESTIGO_H
#define TESTIGO_H

#include <string>
using namespace std;

class Testigo {
public:
    string declaracion;
    int fila;
    int columna;
    bool encontrado;

    Testigo();
    Testigo(string declaracion, int fila, int columna);
    void mostrar() const;
};

#endif
