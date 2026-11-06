/***********************************************************************
 * Module:  Sistema.cpp
 * Author:  dell
 * Modified: jueves, 5 de noviembre de 2026 23:58:28
 * Purpose: Implementation of the class Sistema
 ***********************************************************************/

#include "Sistema.h"
#include "Validaciones.h"
#include <fstream>
#include <iostream>
#include <sstream>
using namespace std;

////////////////////////////////////////////////////////////////////////
// Name:       Sistema::Sistema()
// Purpose:    Implementation of Sistema::Sistema()
// Return:     
////////////////////////////////////////////////////////////////////////

// El constructor vacio reutiliza el constructor con ruta.
Sistema::Sistema() : Sistema("")
{
}

////////////////////////////////////////////////////////////////////////
// Name:       Sistema::Sistema(const string& prefijoArchivo)
// Purpose:    Implementation of Sistema::Sistema()
// Parameters:
// - prefijoArchivo
// Return:     
////////////////////////////////////////////////////////////////////////

Sistema::Sistema(const string& ruta)
{
    prefijo = ruta;
    cargar();
}

////////////////////////////////////////////////////////////////////////
// Name:       Sistema::getMensaje()
// Purpose:    Implementation of Sistema::getMensaje()
// Comment:    Firma exacta en C++: string getMensaje(void) const;
// Return:     string
////////////////////////////////////////////////////////////////////////

string Sistema::getMensaje(void) const
{
    return mensaje;
}

////////////////////////////////////////////////////////////////////////
// Name:       Sistema::buscarDocente(const string& cedula)
// Purpose:    Implementation of Sistema::buscarDocente()
// Comment:    Firma exacta en C++: Nodo<Docente>* buscarDocente(const string& cedula) const;
// Parameters:
// - cedula
// Return:     Nodo<Docente>*
////////////////////////////////////////////////////////////////////////

Nodo<Docente>* Sistema::buscarDocente(const string& cedula) const
{
    Nodo<Docente>* actual = docentes.getPrimero();
    while (actual != nullptr)
    {
        if (actual->getDato().getCedula() == cedula)
        {
            return actual;
        }
        actual = actual->getSiguiente();
    }
    return nullptr;
}

////////////////////////////////////////////////////////////////////////
// Name:       Sistema::buscarMateria(const string& nrc)
// Purpose:    Implementation of Sistema::buscarMateria()
// Comment:    Firma exacta en C++: Nodo<Materia>* buscarMateria(const string& nrc) const;
// Parameters:
// - nrc
// Return:     Nodo<Materia>*
////////////////////////////////////////////////////////////////////////

Nodo<Materia>* Sistema::buscarMateria(const string& nrc) const
{
    Nodo<Materia>* actual = materias.getPrimero();
    while (actual != nullptr)
    {
        if (actual->getDato().getNrc() == nrc)
        {
            return actual;
        }
        actual = actual->getSiguiente();
    }
    return nullptr;
}

////////////////////////////////////////////////////////////////////////
// Name:       Sistema::buscarAsistencia(const string& cedula, const string& fecha, int bloque)
// Purpose:    Implementation of Sistema::buscarAsistencia()
// Comment:    Firma exacta en C++: Nodo<Asistencia>* buscarAsistencia(const string& cedula, const string& fecha, int bloque) const;
// Parameters:
// - cedula
// - fecha
// - bloque
// Return:     Nodo<Asistencia>*
////////////////////////////////////////////////////////////////////////

Nodo<Asistencia>* Sistema::buscarAsistencia(const string& cedula,
                                               const string& fecha, int bloque) const
{
    Nodo<Asistencia>* actual = asistencias.getPrimero();
    while (actual != nullptr)
    {
        const Asistencia& dato = actual->getDato();
        if (dato.getCedula() == cedula &&
            dato.getFecha() == fecha && dato.getBloque() == bloque)
        {
            return actual;
        }
        actual = actual->getSiguiente();
    }
    return nullptr;
}

////////////////////////////////////////////////////////////////////////
// Name:       Sistema::obtenerAsistencia(const string& cedula, const string& fecha, int bloque)
// Purpose:    Implementation of Sistema::obtenerAsistencia()
// Comment:    Firma exacta en C++: const Asistencia* obtenerAsistencia(const string& cedula, const string& fecha, int bloque) const;
// Parameters:
// - cedula
// - fecha
// - bloque
// Return:     const  Asistencia*
////////////////////////////////////////////////////////////////////////

const Asistencia* Sistema::obtenerAsistencia(const string& cedula,
                                             const string& fecha, int bloque) const
{
    Nodo<Asistencia>* encontrado = buscarAsistencia(cedula, fecha, bloque);
    if (encontrado == nullptr)
    {
        return nullptr;
    }
    return &encontrado->getDato();
}

////////////////////////////////////////////////////////////////////////
// Name:       Sistema::cargar()
// Purpose:    Implementation of Sistema::cargar()
// Return:     void
////////////////////////////////////////////////////////////////////////

// Los titulos del archivo comienzan con # y se ignoran al cargar.
// Tambien se aceptan registros D, M y A de versiones anteriores.
void Sistema::cargar(void)
{
    ifstream archivo(prefijo + "registros.txt");
    string linea, tipo, a, b, c, d, e, f, g, h;

    while (getline(archivo, linea))
    {
        stringstream datos(linea);
        if (!getline(datos, tipo, '|'))
        {
            continue;
        }
        if (tipo == "DOCENTE" || tipo == "D")
        {
            if (getline(datos, a, '|') && getline(datos, b, '|') &&
                getline(datos, c, '|') && Validaciones::cedulaEcuatoriana(a) &&
                Validaciones::nombre(b) && Validaciones::nombre(c) &&
                buscarDocente(a) == nullptr)
            {
                docentes.insertar(Docente(a, b, c));
            }
        }
        else if (tipo == "MATERIA" || tipo == "M")
        {
            if (getline(datos, a, '|') && getline(datos, b, '|') &&
                getline(datos, c, '|') && Validaciones::numeros(a) &&
                Validaciones::nombre(b) && buscarDocente(c) != nullptr &&
                buscarMateria(a) == nullptr)
            {
                materias.insertar(Materia(a, b, c));
            }
        }
        else if (tipo == "ASISTENCIA" || tipo == "A")
        {
            if (!(getline(datos, a, '|') && getline(datos, b, '|') &&
                  getline(datos, c, '|') && getline(datos, d, '|') &&
                  getline(datos, e, '|') && getline(datos, f, '|') &&
                  getline(datos, g, '|') && getline(datos, h, '|')))
            {
                continue;
            }
            string tipoAula = Validaciones::mayusculas(d);
            Nodo<Materia>* materia = buscarMateria(b);
            if (!Validaciones::cedulaEcuatoriana(a) || !Validaciones::numeros(b) ||
                !Validaciones::numeros(c) ||
                (tipoAula != "LABORATORIO" && tipoAula != "ESTUDIO") ||
                !Validaciones::fecha(e) || !Validaciones::opcion(f, 1, 7) ||
                !Validaciones::hora(g) || (h != "_" && !Validaciones::hora(h)) ||
                buscarDocente(a) == nullptr || materia == nullptr ||
                materia->getDato().getCedulaDocente() != a ||
                obtenerAsistencia(a, e, f[0] - '0') != nullptr)
            {
                continue;
            }
            int bloque = f[0] - '0';
            Horario entrada(stoi(e.substr(0, 4)), stoi(e.substr(5, 2)),
                            stoi(e.substr(8, 2)), stoi(g.substr(0, 2)),
                            stoi(g.substr(3, 2)));
            if (entrada.bloqueIngreso() != bloque)
            {
                continue;
            }
            if (h != "_")
            {
                Horario salida(entrada.getAnio(), entrada.getMes(), entrada.getDia(),
                               stoi(h.substr(0, 2)), stoi(h.substr(3, 2)));
                if (salida.bloqueSalida() != bloque)
                {
                    continue;
                }
            }
            asistencias.insertar(Asistencia(a, b, c, tipoAula, e,
                                           bloque, g, h == "_" ? "" : h));
        }
    }
}

////////////////////////////////////////////////////////////////////////
// Name:       Sistema::guardar()
// Purpose:    Implementation of Sistema::guardar()
// Comment:    Firma exacta en C++: bool guardar(void) const;
// Return:     bool
////////////////////////////////////////////////////////////////////////

bool Sistema::guardar(void) const
{
    ofstream archivo(prefijo + "registros.txt");
    if (!archivo)
    {
        return false;
    }

    archivo << "# ================= DOCENTES =================\n"
           << "# CEDULA | NOMBRES | APELLIDOS\n";
    Nodo<Docente>* d = docentes.getPrimero();
    while (d != nullptr)
    {
        const Docente& dato = d->getDato();
        archivo << "DOCENTE|" << dato.getCedula() << '|' << dato.getNombres() << '|'
                << dato.getApellidos() << '\n';
        d = d->getSiguiente();
    }

    archivo << "\n# ================= MATERIAS =================\n"
           << "# NRC | MATERIA | CEDULA DEL DOCENTE\n";
    Nodo<Materia>* m = materias.getPrimero();
    while (m != nullptr)
    {
        const Materia& dato = m->getDato();
        archivo << "MATERIA|" << dato.getNrc() << '|' << dato.getNombre() << '|'
                << dato.getCedulaDocente() << '\n';
        m = m->getSiguiente();
    }

    archivo << "\n# ================= ASISTENCIAS =================\n"
           << "# CEDULA | NRC | AULA | TIPO | FECHA | BLOQUE | ENTRADA | SALIDA\n";
    Nodo<Asistencia>* a = asistencias.getPrimero();
    while (a != nullptr)
    {
        const Asistencia& dato = a->getDato();
        archivo << "ASISTENCIA|" << dato.getCedula() << '|' << dato.getNrc() << '|'
                << dato.getAula() << '|' << dato.getTipoAula() << '|'
                << dato.getFecha() << '|' << dato.getBloque() << '|'
                << dato.getIngreso() << '|'
                << (dato.getSalida().empty() ? "_" : dato.getSalida()) << '\n';
        a = a->getSiguiente();
    }
    archivo.flush();
    return archivo.good();
}

////////////////////////////////////////////////////////////////////////
// Name:       Sistema::registrarDocenteMateria(const Docente& docente, const Materia& materia)
// Purpose:    Implementation of Sistema::registrarDocenteMateria()
// Parameters:
// - docente
// - materia
// Return:     bool
////////////////////////////////////////////////////////////////////////

bool Sistema::registrarDocenteMateria(const Docente& d, const Materia& m)
{
    if (!Validaciones::cedulaEcuatoriana(d.getCedula()) ||
        !Validaciones::nombre(d.getNombres()) ||
        !Validaciones::nombre(d.getApellidos()))
    {
        mensaje = "CEDULA, NOMBRES O APELLIDOS INCORRECTOS.";
        return false;
    }
    if (!Validaciones::numeros(m.getNrc()) || !Validaciones::nombre(m.getNombre()) ||
        m.getCedulaDocente() != d.getCedula())
    {
        mensaje = "MATERIA O NRC INCORRECTOS.";
        return false;
    }
    if (buscarMateria(m.getNrc()) != nullptr)
    {
        mensaje = "ESE NRC YA ESTA REGISTRADO.";
        return false;
    }

    Nodo<Docente>* encontrado = buscarDocente(d.getCedula());
    if (encontrado != nullptr &&
        (encontrado->getDato().getNombres() != d.getNombres() ||
         encontrado->getDato().getApellidos() != d.getApellidos()))
    {
        mensaje = "LA CEDULA CORRESPONDE A OTRO NOMBRE.";
        return false;
    }

    bool nuevo = encontrado == nullptr;
    if (nuevo)
    {
        docentes.insertar(d);
    }
    materias.insertar(m);

    if (!guardar())
    {
        materias.eliminar(materias.getUltimo());
        if (nuevo)
        {
            docentes.eliminar(docentes.getUltimo());
        }
        mensaje = "NO SE PUDIERON GUARDAR LOS DATOS.";
        return false;
    }
    mensaje = nuevo ? "DOCENTE Y MATERIA REGISTRADOS." : "MATERIA AGREGADA AL DOCENTE.";
    return true;
}

////////////////////////////////////////////////////////////////////////
// Name:       Sistema::identificar(const string& cedula, const string& nombres, const string& apellidos)
// Purpose:    Implementation of Sistema::identificar()
// Parameters:
// - cedula
// - nombres
// - apellidos
// Return:     bool
////////////////////////////////////////////////////////////////////////

bool Sistema::identificar(const string& cedula, const string& nombres,
                         const string& apellidos)
{
    if (!Validaciones::cedulaEcuatoriana(cedula))
    {
        mensaje = "CEDULA INCORRECTA.";
        return false;
    }
    Nodo<Docente>* docente = buscarDocente(cedula);
    if (docente == nullptr)
    {
        mensaje = "DOCENTE NO REGISTRADO.";
        return false;
    }
    if (docente->getDato().getNombres() != Validaciones::mayusculas(nombres) ||
        docente->getDato().getApellidos() != Validaciones::mayusculas(apellidos))
    {
        mensaje = "NOMBRES O APELLIDOS NO COINCIDEN CON LA CEDULA.";
        return false;
    }
    return true;
}

////////////////////////////////////////////////////////////////////////
// Name:       Sistema::iniciarSesion(const string& cedula, const string& nombres, const string& apellidos, const string& nrc, const string& aula, const string& tipoAula, const Horario& momento)
// Purpose:    Implementation of Sistema::iniciarSesion()
// Parameters:
// - cedula
// - nombres
// - apellidos
// - nrc
// - aula
// - tipoAula
// - momento
// Return:     bool
////////////////////////////////////////////////////////////////////////

bool Sistema::iniciarSesion(const string& cedula, const string& nombres,
                           const string& apellidos, const string& nrc,
                           const string& aula, const string& tipoAula,
                           const Horario& momento)
{
    if (!identificar(cedula, nombres, apellidos))
    {
        return false;
    }
    int bloque = momento.bloqueIngreso();
    if (bloque == 0)
    {
        mensaje = "INGRESO FUERA DEL HORARIO PERMITIDO (MINUTOS 00 A 10).";
        return false;
    }
    Nodo<Materia>* materia = buscarMateria(nrc);
    if (materia == nullptr || materia->getDato().getCedulaDocente() != cedula)
    {
        mensaje = "EL NRC NO CORRESPONDE AL DOCENTE.";
        return false;
    }
    string tipo = Validaciones::mayusculas(tipoAula);
    if (!Validaciones::numeros(aula) || (tipo != "LABORATORIO" && tipo != "ESTUDIO"))
    {
        mensaje = "AULA O TIPO DE AULA INCORRECTOS.";
        return false;
    }

    Nodo<Asistencia>* actual = asistencias.getPrimero();
    while (actual != nullptr)
    {
        const Asistencia& a = actual->getDato();
        if (a.getFecha() == momento.getFecha() && a.getBloque() == bloque)
        {
            if (a.getCedula() == cedula)
            {
                mensaje = "YA EXISTE INGRESO DE ESTE DOCENTE EN EL BLOQUE.";
                return false;
            }
            if (a.getAula() == aula && a.getTipoAula() == tipo)
            {
                mensaje = "AULA OCUPADA EN ESTE BLOQUE.";
                return false;
            }
        }
        actual = actual->getSiguiente();
    }

    asistencias.insertar(Asistencia(cedula, nrc, aula, tipo,
                                    momento.getFecha(), bloque,
                                    momento.getHoraTexto(), ""));
    if (!guardar())
    {
        asistencias.eliminar(asistencias.getUltimo());
        mensaje = "NO SE PUDO GUARDAR EL INGRESO.";
        return false;
    }
    int inicio = 7 + (bloque - 1) * 2;
    mensaje = "INGRESO: " + momento.getHoraTexto() + " | BLOQUE " +
              to_string(inicio) + ":00 A " + to_string(inicio + 2) + ":00";
    return true;
}

////////////////////////////////////////////////////////////////////////
// Name:       Sistema::cerrarSesion(const string& cedula, const string& nombres, const string& apellidos, const Horario& momento)
// Purpose:    Implementation of Sistema::cerrarSesion()
// Parameters:
// - cedula
// - nombres
// - apellidos
// - momento
// Return:     bool
////////////////////////////////////////////////////////////////////////

bool Sistema::cerrarSesion(const string& cedula, const string& nombres,
                          const string& apellidos, const Horario& momento)
{
    if (!identificar(cedula, nombres, apellidos))
    {
        return false;
    }
    int bloque = momento.bloqueSalida();
    if (bloque == 0)
    {
        mensaje = "SALIDA FUERA DEL HORARIO PERMITIDO (ULTIMOS 10 MINUTOS).";
        return false;
    }

    Nodo<Asistencia>* encontrado = buscarAsistencia(cedula, momento.getFecha(), bloque);
    if (encontrado == nullptr)
    {
        mensaje = "NO EXISTE INGRESO PREVIO EN ESTE BLOQUE.";
        return false;
    }

    Asistencia& asistencia = encontrado->getDato();
    if (!asistencia.getSalida().empty())
    {
        mensaje = "LA SALIDA YA FUE REGISTRADA.";
        return false;
    }

    asistencia.setSalida(momento.getHoraTexto());
    if (!guardar())
    {
        asistencia.setSalida("");
        mensaje = "NO SE PUDO GUARDAR LA SALIDA.";
        return false;
    }
    mensaje = "SALIDA REGISTRADA A LAS " + momento.getHoraTexto() + ".";
    return true;
}

////////////////////////////////////////////////////////////////////////
// Name:       Sistema::eliminarDocente(const string& cedula)
// Purpose:    Implementation of Sistema::eliminarDocente()
// Parameters:
// - cedula
// Return:     bool
////////////////////////////////////////////////////////////////////////

bool Sistema::eliminarDocente(const string& cedula)
{
    if (!Validaciones::cedulaEcuatoriana(cedula))
    {
        mensaje = "CEDULA INCORRECTA.";
        return false;
    }
    Nodo<Docente>* docente = buscarDocente(cedula);
    if (docente == nullptr)
    {
        mensaje = "DOCENTE NO REGISTRADO.";
        return false;
    }

    Nodo<Asistencia>* actual = asistencias.getPrimero();
    while (actual != nullptr)
    {
        if (actual->getDato().getCedula() == cedula)
        {
            mensaje = "NO SE PUEDE ELIMINAR: EL DOCENTE TIENE HISTORIAL.";
            return false;
        }
        actual = actual->getSiguiente();
    }
    Nodo<Materia>* materia = materias.getPrimero();
    while (materia != nullptr)
    {
        Nodo<Materia>* siguiente = materia->getSiguiente();
        if (materia->getDato().getCedulaDocente() == cedula)
        {
            materias.eliminar(materia);
        }
        materia = siguiente;
    }
    docentes.eliminar(docente);
    if (!guardar())
    {
        mensaje = "NO SE PUDO GUARDAR LA ELIMINACION.";
        return false;
    }
    mensaje = "DOCENTE Y MATERIAS ELIMINADOS.";
    return true;
}

////////////////////////////////////////////////////////////////////////
// Name:       Sistema::listarDocentes()
// Purpose:    Implementation of Sistema::listarDocentes()
// Comment:    Firma exacta en C++: void listarDocentes(void) const;
// Return:     void
////////////////////////////////////////////////////////////////////////

void Sistema::listarDocentes(void) const
{
    Nodo<Docente>* docente = docentes.getPrimero();
    if (docente == nullptr)
    {
        cout << "NO HAY DOCENTES REGISTRADOS.\n";
        return;
    }
    while (docente != nullptr)
    {
        const Docente& d = docente->getDato();
        cout << "CEDULA: " << d.getCedula() << " | " << d.getNombres()
             << ' ' << d.getApellidos() << '\n';
        Nodo<Materia>* materia = materias.getPrimero();
        while (materia != nullptr)
        {
            if (materia->getDato().getCedulaDocente() == d.getCedula())
            {
                cout << "  MATERIA: " << materia->getDato().getNombre()
                     << " | NRC: " << materia->getDato().getNrc() << '\n';
            }
            materia = materia->getSiguiente();
        }
        docente = docente->getSiguiente();
    }
}

////////////////////////////////////////////////////////////////////////
// Name:       Sistema::reporteAsistencia()
// Purpose:    Implementation of Sistema::reporteAsistencia()
// Comment:    Firma exacta en C++: void reporteAsistencia(void) const;
// Return:     void
////////////////////////////////////////////////////////////////////////

// Unico reporte: sigue el orden en que se insertaron las asistencias.
void Sistema::reporteAsistencia(void) const
{
    Nodo<Asistencia>* actual = asistencias.getPrimero();
    if (actual == nullptr)
    {
        cout << "NO HAY ASISTENCIAS.\n";
        return;
    }
    while (actual != nullptr)
    {
        const Asistencia& a = actual->getDato();
        Nodo<Docente>* d = buscarDocente(a.getCedula());
        Nodo<Materia>* m = buscarMateria(a.getNrc());
        cout << a.getFecha() << " | BLOQUE " << (7 + (a.getBloque() - 1) * 2)
             << "H | " << (d == nullptr ? a.getCedula() :
                           d->getDato().getNombres() + " " + d->getDato().getApellidos())
             << "\n  MATERIA: " << (m == nullptr ? "?" : m->getDato().getNombre())
             << " | NRC: " << a.getNrc()
             << " | AULA: " << a.getTipoAula() << ' ' << a.getAula()
             << "\n  ENTRADA: " << a.getIngreso()
             << " | SALIDA: " << (a.getSalida().empty() ? "PENDIENTE" : a.getSalida())
             << '\n';
        actual = actual->getSiguiente();
    }
}
