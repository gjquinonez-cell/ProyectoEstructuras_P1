/***********************************************************************
 * Module:  Docente.h
 * Author:  dell
 * Modified: jueves, 5 de noviembre de 2026 23:58:28
 * Purpose: Declaration of the class Docente
 ***********************************************************************/

#ifndef DOCENTE_H
#define DOCENTE_H

#include <string>
using std::string;

class Docente
{
private:
    string cedula;
    string nombres;
    string apellidos;

public:
    Docente();
    Docente(const string& cedula, const string& nombres, const string& apellidos);

    string getCedula(void) const;

    string getNombres(void) const;

    string getApellidos(void) const;
    void setCedula(const string& valor);
    void setNombres(const string& valor);
    void setApellidos(const string& valor);
};

#endif
