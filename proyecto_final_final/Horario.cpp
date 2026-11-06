/***********************************************************************
 * Module:  Horario.cpp
 * Author:  dell
 * Modified: jueves, 5 de noviembre de 2026 23:58:28
 * Purpose: Implementation of the class Horario
 ***********************************************************************/

#include "Horario.h"
#include <ctime>
#include <iomanip>
#include <sstream>
using namespace std;

////////////////////////////////////////////////////////////////////////
// Name:       Horario::Horario()
// Purpose:    Implementation of Horario::Horario()
// Return:     
////////////////////////////////////////////////////////////////////////

Horario::Horario()
{
    anio = 2000;
    mes = 1;
    dia = 1;
    hora = 0;
    minuto = 0;
}

////////////////////////////////////////////////////////////////////////
// Name:       Horario::Horario(int anio, int mes, int dia, int hora, int minuto)
// Purpose:    Implementation of Horario::Horario()
// Parameters:
// - anio
// - mes
// - dia
// - hora
// - minuto
// Return:     
////////////////////////////////////////////////////////////////////////

Horario::Horario(int a, int m, int d, int h, int min)
{
    anio = a;
    mes = m;
    dia = d;
    hora = h;
    minuto = min;
}

////////////////////////////////////////////////////////////////////////
// Name:       Horario::getAnio()
// Purpose:    Implementation of Horario::getAnio()
// Comment:    Firma exacta en C++: int getAnio(void) const;
// Return:     int
////////////////////////////////////////////////////////////////////////

int Horario::getAnio(void) const
{
    return anio;
}

////////////////////////////////////////////////////////////////////////
// Name:       Horario::getMes()
// Purpose:    Implementation of Horario::getMes()
// Comment:    Firma exacta en C++: int getMes(void) const;
// Return:     int
////////////////////////////////////////////////////////////////////////

int Horario::getMes(void) const
{
    return mes;
}

////////////////////////////////////////////////////////////////////////
// Name:       Horario::getDia()
// Purpose:    Implementation of Horario::getDia()
// Comment:    Firma exacta en C++: int getDia(void) const;
// Return:     int
////////////////////////////////////////////////////////////////////////

int Horario::getDia(void) const
{
    return dia;
}

////////////////////////////////////////////////////////////////////////
// Name:       Horario::getHora()
// Purpose:    Implementation of Horario::getHora()
// Comment:    Firma exacta en C++: int getHora(void) const;
// Return:     int
////////////////////////////////////////////////////////////////////////

int Horario::getHora(void) const
{
    return hora;
}

////////////////////////////////////////////////////////////////////////
// Name:       Horario::getMinuto()
// Purpose:    Implementation of Horario::getMinuto()
// Comment:    Firma exacta en C++: int getMinuto(void) const;
// Return:     int
////////////////////////////////////////////////////////////////////////

int Horario::getMinuto(void) const
{
    return minuto;
}

////////////////////////////////////////////////////////////////////////
// Name:       Horario::getFecha()
// Purpose:    Implementation of Horario::getFecha()
// Comment:    Firma exacta en C++: string getFecha(void) const;
// Return:     string
////////////////////////////////////////////////////////////////////////

string Horario::getFecha(void) const
{
    ostringstream texto;
    texto << setfill('0') << setw(4) << anio << '-'
          << setw(2) << mes << '-' << setw(2) << dia;
    return texto.str();
}

////////////////////////////////////////////////////////////////////////
// Name:       Horario::getHoraTexto()
// Purpose:    Implementation of Horario::getHoraTexto()
// Comment:    Firma exacta en C++: string getHoraTexto(void) const;
// Return:     string
////////////////////////////////////////////////////////////////////////

string Horario::getHoraTexto(void) const
{
    ostringstream texto;
    texto << setfill('0') << setw(2) << hora << ':' << setw(2) << minuto;
    return texto.str();
}

////////////////////////////////////////////////////////////////////////
// Name:       Horario::esFechaValida()
// Purpose:    Implementation of Horario::esFechaValida()
// Comment:    Firma exacta en C++: bool esFechaValida(void) const;
// Return:     bool
////////////////////////////////////////////////////////////////////////

bool Horario::esFechaValida(void) const
{
    if (anio < 1900 || anio > 9999 || mes < 1 || mes > 12 ||
        dia < 1 || dia > 31 || hora < 0 || hora > 23 || minuto < 0 || minuto > 59)
    {
        return false;
    }
    tm fecha = {};
    fecha.tm_year = anio - 1900;
    fecha.tm_mon = mes - 1;
    fecha.tm_mday = dia;
    fecha.tm_hour = 12;
    fecha.tm_isdst = -1;
    if (mktime(&fecha) == -1)
    {
        return false;
    }
    return fecha.tm_year == anio - 1900 &&
           fecha.tm_mon == mes - 1 && fecha.tm_mday == dia;
}

////////////////////////////////////////////////////////////////////////
// Name:       Horario::esLaborable()
// Purpose:    Implementation of Horario::esLaborable()
// Comment:    Firma exacta en C++: bool esLaborable(void) const;
// Return:     bool
////////////////////////////////////////////////////////////////////////

bool Horario::esLaborable(void) const
{
    if (!esFechaValida())
    {
        return false;
    }
    tm fecha = {};
    fecha.tm_year = anio - 1900;
    fecha.tm_mon = mes - 1;
    fecha.tm_mday = dia;
    fecha.tm_hour = 12;
    fecha.tm_isdst = -1;
    mktime(&fecha);
    return fecha.tm_wday >= 1 && fecha.tm_wday <= 5;
}

////////////////////////////////////////////////////////////////////////
// Name:       Horario::bloqueIngreso()
// Purpose:    Implementation of Horario::bloqueIngreso()
// Comment:    Firma exacta en C++: int bloqueIngreso(void) const;
// Return:     int
////////////////////////////////////////////////////////////////////////

int Horario::bloqueIngreso(void) const
{
    if (!esLaborable() || hora < 7 || hora > 19 ||
        hora % 2 == 0 || minuto > 10)
    {
        return 0;
    }
    return (hora - 7) / 2 + 1;
}

////////////////////////////////////////////////////////////////////////
// Name:       Horario::bloqueSalida()
// Purpose:    Implementation of Horario::bloqueSalida()
// Comment:    Firma exacta en C++: int bloqueSalida(void) const;
// Return:     int
////////////////////////////////////////////////////////////////////////

int Horario::bloqueSalida(void) const
{
    if (!esLaborable() || hora < 8 || hora > 20 ||
        hora % 2 != 0 || minuto < 50)
    {
        return 0;
    }
    return (hora - 8) / 2 + 1;
}

////////////////////////////////////////////////////////////////////////
// Name:       Horario::ahora()
// Purpose:    Implementation of Horario::ahora()
// Return:     Horario
////////////////////////////////////////////////////////////////////////

Horario Horario::ahora(void)
{
    time_t instante = time(nullptr);
    tm* reloj = localtime(&instante);
    if (reloj == nullptr)
    {
        return Horario();
    }
    return Horario(reloj->tm_year + 1900, reloj->tm_mon + 1, reloj->tm_mday,
                   reloj->tm_hour, reloj->tm_min);
}
