//
// Created by garci on 18/05/2026.
//

#include "Detective.h"
#include <iostream>
using namespace std;

Detective::Detective() {
    nombre = "";
    puntaje = 0;
    posicionAct = nullptr;
}

Detective::Detective(string nombre) {
    nombre = nombre;
    puntaje = 0;
    posicionAct = nullptr;
}

void Detective::mover(Ubicacion *nueva) {
    posicionAct->simbolo = ' ';
    posicionAct = nueva;
    posicionAct->simbolo = 'D';
    posicionAct->visitado = true;
}

void Detective::aumentarPuntaje() {
    puntaje++;
}

void Detective::mostrarPuntaje() {
    cout << nombre << "tu puntaje es: " << puntaje << endl;
}

