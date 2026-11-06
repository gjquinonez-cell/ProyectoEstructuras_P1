/***********************************************************************
 * Module:  Validaciones.h
 * Author:  dell
 * Modified: jueves, 5 de noviembre de 2026 23:58:28
 * Purpose: Declaration of the class Validaciones
 ***********************************************************************/

#ifndef VALIDACIONES_H
#define VALIDACIONES_H

#include <string>
using std::string;

class Validaciones
{
public:
    static string mayusculas(const string& dato);
    static bool numeros(const string& dato);
    static bool cedulaEcuatoriana(const string& cedula);
    static bool nombre(const string& dato);
    static bool opcion(const string& dato, int minimo, int maximo);
    static bool fecha(const string& dato);
    static bool hora(const string& dato);
};

#endif
