/***********************************************************************
 * Module:  ListaDoble.h
 * Author:  dell
 * Modified: jueves, 5 de noviembre de 2026 23:58:28
 * Purpose: Declaration of the class ListaDoble
 * Comment: Plantilla C++: template <typename T> class ListaDoble. PowerDesigner 16.5 no genera plantillas C++ de forma nativa; el parametro de tipo T aparece en el nombre, los atributos y las firmas.
 ***********************************************************************/

#ifndef LISTADOBLE_H
#define LISTADOBLE_H

#include "Nodo.h"

template <typename T>
class ListaDoble
{
private:
    Nodo<T>* primero;
    Nodo<T>* ultimo;

public:
    ListaDoble();
    ~ListaDoble();

    Nodo<T>* getPrimero(void) const;

    Nodo<T>* getUltimo(void) const;

    bool estaVacia(void) const;
    void insertar(const T& dato);
    bool eliminar(Nodo<T>* nodo);
    void vaciar(void);

    // Una lista con nodos dinamicos no se debe copiar directamente.

    ListaDoble(const ListaDoble<T>&) = delete;

    ListaDoble<T>& operator=(const ListaDoble<T>&) = delete;
};

////////////////////////////////////////////////////////////////////////
// Name:       ListaDoble::ListaDoble()
// Purpose:    Implementation of ListaDoble::ListaDoble()
// Return:     
////////////////////////////////////////////////////////////////////////

template <typename T>
ListaDoble<T>::ListaDoble()
{
    primero = nullptr;
    ultimo = nullptr;
}

////////////////////////////////////////////////////////////////////////
// Name:       ListaDoble::Destructor_ListaDoble()
// Purpose:    Implementation of ListaDoble::Destructor_ListaDoble()
// Return:     void
////////////////////////////////////////////////////////////////////////

template <typename T>
ListaDoble<T>::~ListaDoble()
{
    vaciar();
}

////////////////////////////////////////////////////////////////////////
// Name:       ListaDoble::getPrimero()
// Purpose:    Implementation of ListaDoble::getPrimero()
// Comment:    Firma exacta en C++: Nodo<T>* getPrimero(void) const;
// Return:     Nodo<T>*
////////////////////////////////////////////////////////////////////////

template <typename T>
Nodo<T>* ListaDoble<T>::getPrimero(void) const
{
    return primero;
}

////////////////////////////////////////////////////////////////////////
// Name:       ListaDoble::getUltimo()
// Purpose:    Implementation of ListaDoble::getUltimo()
// Comment:    Firma exacta en C++: Nodo<T>* getUltimo(void) const;
// Return:     Nodo<T>*
////////////////////////////////////////////////////////////////////////

template <typename T>
Nodo<T>* ListaDoble<T>::getUltimo(void) const
{
    return ultimo;
}

////////////////////////////////////////////////////////////////////////
// Name:       ListaDoble::estaVacia()
// Purpose:    Implementation of ListaDoble::estaVacia()
// Comment:    Firma exacta en C++: bool estaVacia(void) const;
// Return:     bool
////////////////////////////////////////////////////////////////////////

template <typename T>
bool ListaDoble<T>::estaVacia(void) const
{
    return primero == nullptr;
}

////////////////////////////////////////////////////////////////////////
// Name:       ListaDoble::insertar(const T& dato)
// Purpose:    Implementation of ListaDoble::insertar()
// Parameters:
// - dato
// Return:     void
////////////////////////////////////////////////////////////////////////

template <typename T>
void ListaDoble<T>::insertar(const T& dato)
{
    Nodo<T>* nuevo = new Nodo<T>(dato);

    if (primero == nullptr)
    {
        primero = nuevo;
        ultimo = nuevo;
    }
    else
    {
        nuevo->setAnterior(ultimo);
        ultimo->setSiguiente(nuevo);
        ultimo = nuevo;
    }
}

////////////////////////////////////////////////////////////////////////
// Name:       ListaDoble::eliminar(Nodo<T>* nodo)
// Purpose:    Implementation of ListaDoble::eliminar()
// Parameters:
// - nodo
// Return:     bool
////////////////////////////////////////////////////////////////////////

template <typename T>
bool ListaDoble<T>::eliminar(Nodo<T>* nodo)
{
    if (nodo == nullptr)
    {
        return false;
    }

    if (nodo->getAnterior() == nullptr)
    {
        primero = nodo->getSiguiente();
    }
    else
    {
        nodo->getAnterior()->setSiguiente(nodo->getSiguiente());
    }

    if (nodo->getSiguiente() == nullptr)
    {
        ultimo = nodo->getAnterior();
    }
    else
    {
        nodo->getSiguiente()->setAnterior(nodo->getAnterior());
    }

    delete nodo;
    return true;
}

////////////////////////////////////////////////////////////////////////
// Name:       ListaDoble::vaciar()
// Purpose:    Implementation of ListaDoble::vaciar()
// Return:     void
////////////////////////////////////////////////////////////////////////

template <typename T>
void ListaDoble<T>::vaciar(void)
{
    while (primero != nullptr)
    {
        eliminar(primero);
    }
}

#endif
