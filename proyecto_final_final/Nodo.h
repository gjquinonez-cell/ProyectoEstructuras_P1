/***********************************************************************
 * Module:  Nodo.h
 * Author:  dell
 * Modified: jueves, 5 de noviembre de 2026 23:58:28
 * Purpose: Declaration of the class Nodo
 * Comment: Plantilla C++: template <typename T> class Nodo. PowerDesigner 16.5 no genera plantillas C++ de forma nativa; el parametro de tipo T aparece en el nombre, los atributos y las firmas.
 ***********************************************************************/

#ifndef NODO_H
#define NODO_H

template <typename T>
class Nodo
{
private:
    T dato;
    Nodo<T>* anterior;
    Nodo<T>* siguiente;

public:
    Nodo();
    Nodo(const T& valor);
    T& getDato(void);

    const T& getDato(void) const;

    Nodo<T>* getAnterior(void) const;

    Nodo<T>* getSiguiente(void) const;
    void setDato(const T& valor);
    void setAnterior(Nodo<T>* nodo);
    void setSiguiente(Nodo<T>* nodo);
};

// Implementaciones de la plantilla (en el mismo .h).

////////////////////////////////////////////////////////////////////////
// Name:       Nodo::Nodo()
// Purpose:    Implementation of Nodo::Nodo()
// Return:     
////////////////////////////////////////////////////////////////////////

template <typename T>
Nodo<T>::Nodo()
{
    dato = T();
    anterior = nullptr;
    siguiente = nullptr;
}

////////////////////////////////////////////////////////////////////////
// Name:       Nodo::Nodo(const T& valor)
// Purpose:    Implementation of Nodo::Nodo()
// Parameters:
// - valor
// Return:     
////////////////////////////////////////////////////////////////////////

template <typename T>
Nodo<T>::Nodo(const T& valor)
{
    dato = valor;
    anterior = nullptr;
    siguiente = nullptr;
}

////////////////////////////////////////////////////////////////////////
// Name:       Nodo::getDato()
// Purpose:    Implementation of Nodo::getDato()
// Return:     T&
////////////////////////////////////////////////////////////////////////

template <typename T>
T& Nodo<T>::getDato(void)
{
    return dato;
}

////////////////////////////////////////////////////////////////////////
// Name:       Nodo::getDatoConst()
// Purpose:    Implementation of Nodo::getDatoConst()
// Comment:    Firma exacta en C++: const T& getDato(void) const;
// Return:     const T&
////////////////////////////////////////////////////////////////////////

template <typename T>
const T& Nodo<T>::getDato(void) const
{
    return dato;
}

////////////////////////////////////////////////////////////////////////
// Name:       Nodo::getAnterior()
// Purpose:    Implementation of Nodo::getAnterior()
// Comment:    Firma exacta en C++: Nodo<T>* getAnterior(void) const;
// Return:     Nodo<T>*
////////////////////////////////////////////////////////////////////////

template <typename T>
Nodo<T>* Nodo<T>::getAnterior(void) const
{
    return anterior;
}

////////////////////////////////////////////////////////////////////////
// Name:       Nodo::getSiguiente()
// Purpose:    Implementation of Nodo::getSiguiente()
// Comment:    Firma exacta en C++: Nodo<T>* getSiguiente(void) const;
// Return:     Nodo<T>*
////////////////////////////////////////////////////////////////////////

template <typename T>
Nodo<T>* Nodo<T>::getSiguiente(void) const
{
    return siguiente;
}

////////////////////////////////////////////////////////////////////////
// Name:       Nodo::setDato(const T& valor)
// Purpose:    Implementation of Nodo::setDato()
// Parameters:
// - valor
// Return:     void
////////////////////////////////////////////////////////////////////////

template <typename T>
void Nodo<T>::setDato(const T& valor)
{
    dato = valor;
}

////////////////////////////////////////////////////////////////////////
// Name:       Nodo::setAnterior(Nodo<T>* nodo)
// Purpose:    Implementation of Nodo::setAnterior()
// Parameters:
// - nodo
// Return:     void
////////////////////////////////////////////////////////////////////////

template <typename T>
void Nodo<T>::setAnterior(Nodo<T>* nodo)
{
    anterior = nodo;
}

////////////////////////////////////////////////////////////////////////
// Name:       Nodo::setSiguiente(Nodo<T>* nodo)
// Purpose:    Implementation of Nodo::setSiguiente()
// Parameters:
// - nodo
// Return:     void
////////////////////////////////////////////////////////////////////////

template <typename T>
void Nodo<T>::setSiguiente(Nodo<T>* nodo)
{
    siguiente = nodo;
}

#endif
