//
// Created by garci on 18/05/2026.
//

#include "Sospechoso.h"
#include <iostream>
using namespace std;

Sospechoso::Sospechoso() {
    nombre = "";
    culpable = false;
}

Sospechoso::Sospechoso(string nombre, vector<string> atributos) {
    nombre = nombre;
    culpable = false;
    atributos = atributos;
}

void Sospechoso::revelar(int indice) {
    if (indice > atributos.size()) {
        revelados.push_back((atributos)[indice]);
        indice++;
    }
}

void Sospechoso::mostrar() {
    cout << " " << nombre << " | atributos: ";
    if (revelados.empty()) {
        cout << "-";
    } else {
        for (int i = 0; i < revelados.size(); i++) {
            cout << revelados[i];
            if (i != revelados.size() - 1) cout << ", ";
        }
    }
    cout << endl;
}



