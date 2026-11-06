/***********************************************************************
 * Module:  Materia.h
 * Author:  dell
 * Modified: jueves, 5 de noviembre de 2026 23:58:28
 * Purpose: Declaration of the class Materia
 ***********************************************************************/

#ifndef MATERIA_H
#define MATERIA_H

#include <string>
using std::string;

class Materia
{
private:
    string nrc;
    string nombre;
    string cedulaDocente;

public:
    Materia();
    Materia(const string& nrc, const string& nombre, const string& cedulaDocente);

    string getNrc(void) const;

    string getNombre(void) const;

    string getCedulaDocente(void) const;
    void setNrc(const string& valor);
    void setNombre(const string& valor);
    void setCedulaDocente(const string& valor);
};

#endif
