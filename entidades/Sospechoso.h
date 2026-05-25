#ifndef SOSPECHOSO_H
#define SOSPECHOSO_H

#include <string>
#include <vector>
using namespace std;

class Sospechoso {
public:
    string nombre;
    vector<string> atributos;
    bool culpable;

    Sospechoso();
    Sospechoso(string nombre, vector<string> atributos);

    bool tieneAtributo(const string& atributo) const;
    void mostrarConRevelados(const vector<string>& atributosRevelados) const;
};

#endif
