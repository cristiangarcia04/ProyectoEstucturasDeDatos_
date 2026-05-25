#include "Sospechoso.h"
#include <iostream>
using namespace std;

Sospechoso::Sospechoso() {
    nombre = "";
    culpable = false;
}

Sospechoso::Sospechoso(string nombre, vector<string> atributos) {
    this->nombre = nombre;
    this->atributos = atributos;
    culpable = false;
}

bool Sospechoso::tieneAtributo(const string& atributo) const {
    for (const string& actual : atributos) {
        if (actual == atributo) return true;
    }
    return false;
}

void Sospechoso::mostrarConRevelados(const vector<string>& atributosRevelados) const {
    cout << "  " << nombre << " | atributos: ";
    for (size_t i = 0; i < atributos.size(); i++) {
        cout << atributos[i];
        if (i + 1 < atributos.size()) cout << ", ";
    }

    cout << " | coincide con pistas: ";
    bool alguno = false;
    for (const string& atributo : atributosRevelados) {
        if (tieneAtributo(atributo)) {
            if (alguno) cout << ", ";
            cout << atributo;
            alguno = true;
        }
    }
    if (!alguno) cout << "-";
    cout << endl;
}
