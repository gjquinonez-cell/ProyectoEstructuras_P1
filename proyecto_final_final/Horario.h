/***********************************************************************
 * Module:  Horario.h
 * Author:  dell
 * Modified: jueves, 5 de noviembre de 2026 23:58:28
 * Purpose: Declaration of the class Horario
 ***********************************************************************/

#ifndef HORARIO_H
#define HORARIO_H

#include <string>
using std::string;

class Horario
{
private:
    int anio;
    int mes;
    int dia;
    int hora;
    int minuto;

public:
    Horario();
    Horario(int anio, int mes, int dia, int hora, int minuto);

    int getAnio(void) const;

    int getMes(void) const;

    int getDia(void) const;

    int getHora(void) const;

    int getMinuto(void) const;

    string getFecha(void) const;

    string getHoraTexto(void) const;

    bool esFechaValida(void) const;

    bool esLaborable(void) const;

    int bloqueIngreso(void) const;

    int bloqueSalida(void) const;
    static Horario ahora(void);
};

#endif
