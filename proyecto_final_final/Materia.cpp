/***********************************************************************
 * Module:  Materia.cpp
 * Author:  dell
 * Modified: jueves, 5 de noviembre de 2026 23:58:28
 * Purpose: Implementation of the class Materia
 ***********************************************************************/

#include "Materia.h"
#include "Validaciones.h"

////////////////////////////////////////////////////////////////////////
// Name:       Materia::Materia()
// Purpose:    Implementation of Materia::Materia()
// Return:     
////////////////////////////////////////////////////////////////////////

Materia::Materia()
{
    nrc = "";
    nombre = "";
    cedulaDocente = "";
}

////////////////////////////////////////////////////////////////////////
// Name:       Materia::Materia(const string& nrc, const string& nombre, const string& cedulaDocente)
// Purpose:    Implementation of Materia::Materia()
// Parameters:
// - nrc
// - nombre
// - cedulaDocente
// Return:     
////////////////////////////////////////////////////////////////////////

Materia::Materia(const string& nrc, const string& nombre, const string& cedulaDocente)
{
    setNrc(nrc);
    setNombre(nombre);
    setCedulaDocente(cedulaDocente);
}

////////////////////////////////////////////////////////////////////////
// Name:       Materia::getNrc()
// Purpose:    Implementation of Materia::getNrc()
// Comment:    Firma exacta en C++: string getNrc(void) const;
// Return:     string
////////////////////////////////////////////////////////////////////////

string Materia::getNrc(void) const
{
    return nrc;
}

////////////////////////////////////////////////////////////////////////
// Name:       Materia::getNombre()
// Purpose:    Implementation of Materia::getNombre()
// Comment:    Firma exacta en C++: string getNombre(void) const;
// Return:     string
////////////////////////////////////////////////////////////////////////

string Materia::getNombre(void) const
{
    return nombre;
}

////////////////////////////////////////////////////////////////////////
// Name:       Materia::getCedulaDocente()
// Purpose:    Implementation of Materia::getCedulaDocente()
// Comment:    Firma exacta en C++: string getCedulaDocente(void) const;
// Return:     string
////////////////////////////////////////////////////////////////////////

string Materia::getCedulaDocente(void) const
{
    return cedulaDocente;
}

////////////////////////////////////////////////////////////////////////
// Name:       Materia::setNrc(const string& valor)
// Purpose:    Implementation of Materia::setNrc()
// Parameters:
// - valor
// Return:     void
////////////////////////////////////////////////////////////////////////

void Materia::setNrc(const string& valor)
{
    nrc = valor;
}

////////////////////////////////////////////////////////////////////////
// Name:       Materia::setNombre(const string& valor)
// Purpose:    Implementation of Materia::setNombre()
// Parameters:
// - valor
// Return:     void
////////////////////////////////////////////////////////////////////////

void Materia::setNombre(const string& valor)
{
    nombre = Validaciones::mayusculas(valor);
}

////////////////////////////////////////////////////////////////////////
// Name:       Materia::setCedulaDocente(const string& valor)
// Purpose:    Implementation of Materia::setCedulaDocente()
// Parameters:
// - valor
// Return:     void
////////////////////////////////////////////////////////////////////////

void Materia::setCedulaDocente(const string& valor)
{
    cedulaDocente = valor;
}
