//
// Created by garci on 18/05/2026.
//

#include "Pista.h"


Pista::Pista(string t, int f, int c) {
    tipo = t;
    fila = f;
    columna = c;
    recogido =false;

    if (tipo ==  "huella") {
        simbolo = 'H';
    } else if (tipo  ==  "coartada") {
        simbolo = 'C';
    } else if (tipo  ==  "testimonio") {
        simbolo = 'T';
    } else {
        simbolo = 'P';
    }
}

string Pista::getNombre() {
    if (tipo == "huella") {
        return "huella";
    } if (tipo  ==  "coartada") {
        return "coartada";
    } if (tipo  ==  "testimonio") {
        return "testimonio";
    } if (tipo  ==  "Prueba_forense") {
        return "Prueba forense";
    }
    return "desconocida";
}
