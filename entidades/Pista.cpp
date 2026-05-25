#include "Pista.h"

Pista::Pista() {
    tipo = "huella";
    fila = 0;
    columna = 0;
    recogido = false;
    simbolo = 'H';
}

Pista::Pista(string t, int f, int c) {
    tipo = t;
    fila = f;
    columna = c;
    recogido = false;

    if (tipo == "huella") simbolo = 'H';
    else if (tipo == "coartada") simbolo = 'C';
    else if (tipo == "testimonio") simbolo = 'T';
    else simbolo = 'P';
}

string Pista::getNombre() const {
    if (tipo == "huella") return "Huella";
    if (tipo == "coartada") return "Coartada";
    if (tipo == "testimonio") return "Testimonio";
    if (tipo == "prueba_forense") return "Prueba forense";
    return "Pista desconocida";
}
