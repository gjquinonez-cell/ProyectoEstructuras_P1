/***********************************************************************
 * Module:  Asistencia.h
 * Author:  dell
 * Modified: jueves, 5 de noviembre de 2026 23:58:28
 * Purpose: Declaration of the class Asistencia
 ***********************************************************************/

#ifndef ASISTENCIA_H
#define ASISTENCIA_H

#include <string>
using std::string;

class Asistencia
{
private:
    string cedula;
    string nrc;
    string aula;
    string tipoAula;
    string fecha;
    int bloque;
    string ingreso;
    string salida;

public:
    Asistencia();
    Asistencia(const string& cedula, const string& nrc, const string& aula, const string& tipoAula, const string& fecha, int bloque, const string& ingreso, const string& salida);

    string getCedula(void) const;

    string getNrc(void) const;

    string getAula(void) const;

    string getTipoAula(void) const;

    string getFecha(void) const;

    int getBloque(void) const;

    string getIngreso(void) const;

    string getSalida(void) const;
    void setCedula(const string& valor);
    void setNrc(const string& valor);
    void setAula(const string& valor);
    void setTipoAula(const string& valor);
    void setFecha(const string& valor);
    void setBloque(int valor);
    void setIngreso(const string& valor);
    void setSalida(const string& valor);
};

#endif
