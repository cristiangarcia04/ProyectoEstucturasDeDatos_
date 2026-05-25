#include "Detective.h"
#include <iostream>
using namespace std;

Detective::Detective() {
    nombre = "";
    puntaje = 0;
    posicionAct = nullptr;
}

Detective::Detective(string nombre) {
    this->nombre = nombre;
    puntaje = 0;
    posicionAct = nullptr;
}

void Detective::ubicar(Ubicacion* ubicacion) {
    posicionAct = ubicacion;
    if (posicionAct != nullptr) {
        posicionAct->visitado = true;
        posicionAct->visible = true;
    }
}

void Detective::mover(Ubicacion* nueva) {
    posicionAct = nueva;
    if (posicionAct != nullptr) {
        posicionAct->visitado = true;
        posicionAct->visible = true;
    }
}

void Detective::aumentarPuntaje(int cantidad) {
    puntaje += cantidad;
    if (puntaje < 0) puntaje = 0;
}

void Detective::mostrarPuntaje() const {
    cout << nombre << ", tu puntaje actual es: " << puntaje << endl;
}
