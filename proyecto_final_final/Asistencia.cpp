/***********************************************************************
 * Module:  Asistencia.cpp
 * Author:  dell
 * Modified: jueves, 5 de noviembre de 2026 23:58:28
 * Purpose: Implementation of the class Asistencia
 ***********************************************************************/

#include "Asistencia.h"
#include "Validaciones.h"

////////////////////////////////////////////////////////////////////////
// Name:       Asistencia::Asistencia()
// Purpose:    Implementation of Asistencia::Asistencia()
// Return:     
////////////////////////////////////////////////////////////////////////

Asistencia::Asistencia()
{
    cedula = "";
    nrc = "";
    aula = "";
    tipoAula = "";
    fecha = "";
    bloque = 0;
    ingreso = "";
    salida = "";
}

////////////////////////////////////////////////////////////////////////
// Name:       Asistencia::Asistencia(const string& cedula, const string& nrc, const string& aula, const string& tipoAula, const string& fecha, int bloque, const string& ingreso, const string& salida)
// Purpose:    Implementation of Asistencia::Asistencia()
// Parameters:
// - cedula
// - nrc
// - aula
// - tipoAula
// - fecha
// - bloque
// - ingreso
// - salida
// Return:     
////////////////////////////////////////////////////////////////////////

Asistencia::Asistencia(const string& cedula, const string& nrc, const string& aula, const string& tipoAula, const string& fecha, int bloque, const string& ingreso, const string& salida)
{
    setCedula(cedula);
    setNrc(nrc);
    setAula(aula);
    setTipoAula(tipoAula);
    setFecha(fecha);
    setBloque(bloque);
    setIngreso(ingreso);
    setSalida(salida);
}

////////////////////////////////////////////////////////////////////////
// Name:       Asistencia::getCedula()
// Purpose:    Implementation of Asistencia::getCedula()
// Comment:    Firma exacta en C++: string getCedula(void) const;
// Return:     string
////////////////////////////////////////////////////////////////////////

string Asistencia::getCedula(void) const
{
    return cedula;
}

////////////////////////////////////////////////////////////////////////
// Name:       Asistencia::getNrc()
// Purpose:    Implementation of Asistencia::getNrc()
// Comment:    Firma exacta en C++: string getNrc(void) const;
// Return:     string
////////////////////////////////////////////////////////////////////////

string Asistencia::getNrc(void) const
{
    return nrc;
}

////////////////////////////////////////////////////////////////////////
// Name:       Asistencia::getAula()
// Purpose:    Implementation of Asistencia::getAula()
// Comment:    Firma exacta en C++: string getAula(void) const;
// Return:     string
////////////////////////////////////////////////////////////////////////

string Asistencia::getAula(void) const
{
    return aula;
}

////////////////////////////////////////////////////////////////////////
// Name:       Asistencia::getTipoAula()
// Purpose:    Implementation of Asistencia::getTipoAula()
// Comment:    Firma exacta en C++: string getTipoAula(void) const;
// Return:     string
////////////////////////////////////////////////////////////////////////

string Asistencia::getTipoAula(void) const
{
    return tipoAula;
}

////////////////////////////////////////////////////////////////////////
// Name:       Asistencia::getFecha()
// Purpose:    Implementation of Asistencia::getFecha()
// Comment:    Firma exacta en C++: string getFecha(void) const;
// Return:     string
////////////////////////////////////////////////////////////////////////

string Asistencia::getFecha(void) const
{
    return fecha;
}

////////////////////////////////////////////////////////////////////////
// Name:       Asistencia::getBloque()
// Purpose:    Implementation of Asistencia::getBloque()
// Comment:    Firma exacta en C++: int getBloque(void) const;
// Return:     int
////////////////////////////////////////////////////////////////////////

int Asistencia::getBloque(void) const
{
    return bloque;
}

////////////////////////////////////////////////////////////////////////
// Name:       Asistencia::getIngreso()
// Purpose:    Implementation of Asistencia::getIngreso()
// Comment:    Firma exacta en C++: string getIngreso(void) const;
// Return:     string
////////////////////////////////////////////////////////////////////////

string Asistencia::getIngreso(void) const
{
    return ingreso;
}

////////////////////////////////////////////////////////////////////////
// Name:       Asistencia::getSalida()
// Purpose:    Implementation of Asistencia::getSalida()
// Comment:    Firma exacta en C++: string getSalida(void) const;
// Return:     string
////////////////////////////////////////////////////////////////////////

string Asistencia::getSalida(void) const
{
    return salida;
}

////////////////////////////////////////////////////////////////////////
// Name:       Asistencia::setCedula(const string& valor)
// Purpose:    Implementation of Asistencia::setCedula()
// Parameters:
// - valor
// Return:     void
////////////////////////////////////////////////////////////////////////

void Asistencia::setCedula(const string& valor)
{
    cedula = valor;
}

////////////////////////////////////////////////////////////////////////
// Name:       Asistencia::setNrc(const string& valor)
// Purpose:    Implementation of Asistencia::setNrc()
// Parameters:
// - valor
// Return:     void
////////////////////////////////////////////////////////////////////////

void Asistencia::setNrc(const string& valor)
{
    nrc = valor;
}

////////////////////////////////////////////////////////////////////////
// Name:       Asistencia::setAula(const string& valor)
// Purpose:    Implementation of Asistencia::setAula()
// Parameters:
// - valor
// Return:     void
////////////////////////////////////////////////////////////////////////

void Asistencia::setAula(const string& valor)
{
    aula = valor;
}

////////////////////////////////////////////////////////////////////////
// Name:       Asistencia::setTipoAula(const string& valor)
// Purpose:    Implementation of Asistencia::setTipoAula()
// Parameters:
// - valor
// Return:     void
////////////////////////////////////////////////////////////////////////

void Asistencia::setTipoAula(const string& valor)
{
    tipoAula = Validaciones::mayusculas(valor);
}

////////////////////////////////////////////////////////////////////////
// Name:       Asistencia::setFecha(const string& valor)
// Purpose:    Implementation of Asistencia::setFecha()
// Parameters:
// - valor
// Return:     void
////////////////////////////////////////////////////////////////////////

void Asistencia::setFecha(const string& valor)
{
    fecha = valor;
}

////////////////////////////////////////////////////////////////////////
// Name:       Asistencia::setBloque(int valor)
// Purpose:    Implementation of Asistencia::setBloque()
// Parameters:
// - valor
// Return:     void
////////////////////////////////////////////////////////////////////////

void Asistencia::setBloque(int valor)
{
    bloque = valor;
}

////////////////////////////////////////////////////////////////////////
// Name:       Asistencia::setIngreso(const string& valor)
// Purpose:    Implementation of Asistencia::setIngreso()
// Parameters:
// - valor
// Return:     void
////////////////////////////////////////////////////////////////////////

void Asistencia::setIngreso(const string& valor)
{
    ingreso = valor;
}

////////////////////////////////////////////////////////////////////////
// Name:       Asistencia::setSalida(const string& valor)
// Purpose:    Implementation of Asistencia::setSalida()
// Parameters:
// - valor
// Return:     void
////////////////////////////////////////////////////////////////////////

void Asistencia::setSalida(const string& valor)
{
    salida = valor;
}
