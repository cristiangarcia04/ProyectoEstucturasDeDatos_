#ifndef DETECTIVE_H
#define DETECTIVE_H

#include <string>
#include "Ubicacion.h"
using namespace std;

class Detective {
public:
    string nombre;
    int puntaje;
    Ubicacion* posicionAct;

    Detective();
    explicit Detective(string nombre);

    void ubicar(Ubicacion* ubicacion);
    void mover(Ubicacion* nueva);
    void aumentarPuntaje(int cantidad = 1);
    void mostrarPuntaje() const;
};

#endif
