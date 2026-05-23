//
// Created by garci on 18/05/2026.
//

#ifndef PISTA_H
#define PISTA_H
using namespace std;
#include <string>

class Pista {
public:
    string tipo;
    int fila;
    int columna;
    bool recogido;
    char simbolo;

    Pista(string t, int f, int c);
    string getNombre();
};



#endif //PISTA_H
