//
// Created by garci on 18/05/2026.
//

#ifndef SOSPECHOSO_H
#define SOSPECHOSO_H
#include <string>
#include <vector>
using namespace std;

class Sospechoso {
public:
    string nombre;
    vector<string> atributos;
    vector<string> revelados;
    bool culpable;
    Sospechoso();
    Sospechoso(string nombre, vector<string> atributos);

    void revelar(int indice);
    void mostrar();
};
#endif //SOSPECHOSO_H
