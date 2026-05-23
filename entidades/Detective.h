//
// Created by garci on 18/05/2026.
//

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
    Detective(string nombre);

    void mover(Ubicacion* nueva);
    void aumentarPuntaje();
    void mostrarPuntaje();
};



#endif //DETECTIVE_H
