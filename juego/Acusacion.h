#ifndef ACUSACION_H
#define ACUSACION_H

#include <string>
#include <unordered_map>
#include "../entidades/Sospechoso.h"
using namespace std;

class Acusacion {
public:
    static bool acusar(const string& nombreAcusado,
                       unordered_map<string, Sospechoso>& tablaSospechosos,
                       const string& culpableReal);
};

#endif
