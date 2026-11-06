/***********************************************************************
 * Module:  Docente.cpp
 * Author:  dell
 * Modified: jueves, 5 de noviembre de 2026 23:58:28
 * Purpose: Implementation of the class Docente
 ***********************************************************************/

#include "Docente.h"
#include "Validaciones.h"

////////////////////////////////////////////////////////////////////////
// Name:       Docente::Docente()
// Purpose:    Implementation of Docente::Docente()
// Return:     
////////////////////////////////////////////////////////////////////////

Docente::Docente()
{
    cedula = "";
    nombres = "";
    apellidos = "";
}

////////////////////////////////////////////////////////////////////////
// Name:       Docente::Docente(const string& cedula, const string& nombres, const string& apellidos)
// Purpose:    Implementation of Docente::Docente()
// Parameters:
// - cedula
// - nombres
// - apellidos
// Return:     
////////////////////////////////////////////////////////////////////////

Docente::Docente(const string& cedula, const string& nombres, const string& apellidos)
{
    setCedula(cedula);
    setNombres(nombres);
    setApellidos(apellidos);
}

////////////////////////////////////////////////////////////////////////
// Name:       Docente::getCedula()
// Purpose:    Implementation of Docente::getCedula()
// Comment:    Firma exacta en C++: string getCedula(void) const;
// Return:     string
////////////////////////////////////////////////////////////////////////

string Docente::getCedula(void) const
{
    return cedula;
}

////////////////////////////////////////////////////////////////////////
// Name:       Docente::getNombres()
// Purpose:    Implementation of Docente::getNombres()
// Comment:    Firma exacta en C++: string getNombres(void) const;
// Return:     string
////////////////////////////////////////////////////////////////////////

string Docente::getNombres(void) const
{
    return nombres;
}

////////////////////////////////////////////////////////////////////////
// Name:       Docente::getApellidos()
// Purpose:    Implementation of Docente::getApellidos()
// Comment:    Firma exacta en C++: string getApellidos(void) const;
// Return:     string
////////////////////////////////////////////////////////////////////////

string Docente::getApellidos(void) const
{
    return apellidos;
}

////////////////////////////////////////////////////////////////////////
// Name:       Docente::setCedula(const string& valor)
// Purpose:    Implementation of Docente::setCedula()
// Parameters:
// - valor
// Return:     void
////////////////////////////////////////////////////////////////////////

void Docente::setCedula(const string& valor)
{
    cedula = valor;
}

////////////////////////////////////////////////////////////////////////
// Name:       Docente::setNombres(const string& valor)
// Purpose:    Implementation of Docente::setNombres()
// Parameters:
// - valor
// Return:     void
////////////////////////////////////////////////////////////////////////

void Docente::setNombres(const string& valor)
{
    nombres = Validaciones::mayusculas(valor);
}

////////////////////////////////////////////////////////////////////////
// Name:       Docente::setApellidos(const string& valor)
// Purpose:    Implementation of Docente::setApellidos()
// Parameters:
// - valor
// Return:     void
////////////////////////////////////////////////////////////////////////

void Docente::setApellidos(const string& valor)
{
    apellidos = Validaciones::mayusculas(valor);
}
