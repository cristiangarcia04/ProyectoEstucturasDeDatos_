#ifndef PISTA_H
#define PISTA_H

#include <string>
using namespace std;

class Pista {
public:
    string tipo;
    int fila;
    int columna;
    bool recogido;
    char simbolo;

    Pista();
    Pista(string t, int f, int c);
    string getNombre() const;
};

#endif
