/***********************************************************************
 * Module:  Validaciones.cpp
 * Author:  dell
 * Modified: jueves, 5 de noviembre de 2026 23:58:28
 * Purpose: Implementation of the class Validaciones
 ***********************************************************************/

#include "Validaciones.h"
using namespace std;

////////////////////////////////////////////////////////////////////////
// Name:       Validaciones::mayusculas(const string& dato)
// Purpose:    Implementation of Validaciones::mayusculas()
// Parameters:
// - dato
// Return:     string
////////////////////////////////////////////////////////////////////////

string Validaciones::mayusculas(const string& dato)
{
    string resultado = dato;
    for (unsigned int i = 0; i < resultado.size(); i++)
    {
        unsigned char letra = static_cast<unsigned char>(resultado[i]);
        if (letra >= 'a' && letra <= 'z')
        {
            resultado[i] = static_cast<char>(letra - 32);
        }
        // Vocales con tilde y enie en UTF-8.
        else if (letra == 0xC3 && i + 1 < resultado.size())
        {
            unsigned char siguiente = static_cast<unsigned char>(resultado[i + 1]);
            if (siguiente == 0xA1 || siguiente == 0xA9 || siguiente == 0xAD ||
                siguiente == 0xB3 || siguiente == 0xBA || siguiente == 0xB1 ||
                siguiente == 0xBC)
            {
                resultado[i + 1] = static_cast<char>(siguiente - 32);
            }
            i++;
        }
        // La misma conversion para consolas Windows-1252.
        else if (letra == 0xE1 || letra == 0xE9 || letra == 0xED ||
                 letra == 0xF3 || letra == 0xFA || letra == 0xF1 || letra == 0xFC)
        {
            resultado[i] = static_cast<char>(letra - 32);
        }
    }
    return resultado;
}

////////////////////////////////////////////////////////////////////////
// Name:       Validaciones::numeros(const string& dato)
// Purpose:    Implementation of Validaciones::numeros()
// Parameters:
// - dato
// Return:     bool
////////////////////////////////////////////////////////////////////////

bool Validaciones::numeros(const string& dato)
{
    if (dato.empty())
    {
        return false;
    }
    for (unsigned int i = 0; i < dato.size(); i++)
    {
        if (dato[i] < '0' || dato[i] > '9')
        {
            return false;
        }
    }
    return true;
}

////////////////////////////////////////////////////////////////////////
// Name:       Validaciones::cedulaEcuatoriana(const string& cedula)
// Purpose:    Implementation of Validaciones::cedulaEcuatoriana()
// Parameters:
// - cedula
// Return:     bool
////////////////////////////////////////////////////////////////////////

bool Validaciones::cedulaEcuatoriana(const string& cedula)
{
    if (cedula.size() != 10 || !numeros(cedula))
    {
        return false;
    }
    int provincia = (cedula[0] - '0') * 10 + (cedula[1] - '0');
    int tercero = cedula[2] - '0';
    if (!((provincia >= 1 && provincia <= 24) || provincia == 30) ||
        tercero > 5 || (provincia == 30 && tercero < 4))
    {
        return false;
    }
    int suma = 0;
    for (int i = 0; i < 9; i++)
    {
        int numero = (cedula[i] - '0') * (i % 2 == 0 ? 2 : 1);
        if (numero > 9)
        {
            numero -= 9;
        }
        suma += numero;
    }
    return (10 - suma % 10) % 10 == cedula[9] - '0';
}

////////////////////////////////////////////////////////////////////////
// Name:       Validaciones::nombre(const string& dato)
// Purpose:    Implementation of Validaciones::nombre()
// Parameters:
// - dato
// Return:     bool
////////////////////////////////////////////////////////////////////////

bool Validaciones::nombre(const string& dato)
{
    if (dato.empty() || dato[0] == ' ' || dato[dato.size() - 1] == ' ')
    {
        return false;
    }
    for (unsigned int i = 0; i < dato.size(); i++)
    {
        unsigned char c = static_cast<unsigned char>(dato[i]);
        if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
        {
            continue;
        }
        if (c == ' ')
        {
            if (i > 0 && dato[i - 1] == ' ')
            {
                return false;
            }
        }
        else if (c == 0xC3 && i + 1 < dato.size())
        {
            unsigned char otro = static_cast<unsigned char>(dato[++i]);
            if (otro != 0x81 && otro != 0x89 && otro != 0x8D &&
                otro != 0x93 && otro != 0x9A && otro != 0xA1 &&
                otro != 0xA9 && otro != 0xAD && otro != 0xB3 &&
                otro != 0xBA && otro != 0x91 && otro != 0xB1 &&
                otro != 0x9C && otro != 0xBC)
            {
                return false;
            }
        }
        else if (c != 0xC1 && c != 0xC9 && c != 0xCD && c != 0xD3 &&
                 c != 0xDA && c != 0xE1 && c != 0xE9 && c != 0xED &&
                 c != 0xF3 && c != 0xFA && c != 0xD1 && c != 0xF1 &&
                 c != 0xDC && c != 0xFC)
        {
            return false;
        }
    }
    return true;
}

////////////////////////////////////////////////////////////////////////
// Name:       Validaciones::opcion(const string& dato, int minimo, int maximo)
// Purpose:    Implementation of Validaciones::opcion()
// Parameters:
// - dato
// - minimo
// - maximo
// Return:     bool
////////////////////////////////////////////////////////////////////////

bool Validaciones::opcion(const string& dato, int minimo, int maximo)
{
    if (!numeros(dato) || dato.size() > 2)
    {
        return false;
    }
    int valor = 0;
    for (unsigned int i = 0; i < dato.size(); i++)
    {
        valor = valor * 10 + (dato[i] - '0');
    }
    return valor >= minimo && valor <= maximo;
}

////////////////////////////////////////////////////////////////////////
// Name:       Validaciones::fecha(const string& dato)
// Purpose:    Implementation of Validaciones::fecha()
// Parameters:
// - dato
// Return:     bool
////////////////////////////////////////////////////////////////////////

bool Validaciones::fecha(const string& dato)
{
    if (dato.size() != 10 || dato[4] != '-' || dato[7] != '-')
    {
        return false;
    }
    for (unsigned int i = 0; i < dato.size(); i++)
    {
        if (i != 4 && i != 7 && (dato[i] < '0' || dato[i] > '9'))
        {
            return false;
        }
    }
    return true;
}

////////////////////////////////////////////////////////////////////////
// Name:       Validaciones::hora(const string& dato)
// Purpose:    Implementation of Validaciones::hora()
// Parameters:
// - dato
// Return:     bool
////////////////////////////////////////////////////////////////////////

bool Validaciones::hora(const string& dato)
{
    if (dato.size() != 5 || dato[2] != ':')
    {
        return false;
    }
    for (unsigned int i = 0; i < dato.size(); i++)
    {
        if (i != 2 && (dato[i] < '0' || dato[i] > '9'))
        {
            return false;
        }
    }
    return true;
}
