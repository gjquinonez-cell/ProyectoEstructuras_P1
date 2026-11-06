/***********************************************************************
 * Module:  Sistema.h
 * Author:  dell
 * Modified: jueves, 5 de noviembre de 2026 23:58:28
 * Purpose: Declaration of the class Sistema
 ***********************************************************************/

#ifndef SISTEMA_H
#define SISTEMA_H

#include "Docente.h"
#include "Materia.h"
#include "Asistencia.h"
#include "Horario.h"
#include "ListaDoble.h"
#include <string>
using std::string;

class Sistema
{
private:
    ListaDoble<Docente> docentes;
    ListaDoble<Materia> materias;
    ListaDoble<Asistencia> asistencias;
    string prefijo;
    string mensaje;

    void cargar(void);

    bool guardar(void) const;

    Nodo<Docente>* buscarDocente(const string& cedula) const;

    Nodo<Materia>* buscarMateria(const string& nrc) const;
    
    Nodo<Asistencia>* buscarAsistencia(const string& cedula,
                                      const string& fecha, int bloque) const;
    bool identificar(const string& cedula, const string& nombres,
                     const string& apellidos);

public:
    Sistema();
    Sistema(const string& prefijoArchivo);

    string getMensaje(void) const;
   
    const Asistencia* obtenerAsistencia(const string& cedula,
                                        const string& fecha, int bloque) const;
    bool registrarDocenteMateria(const Docente& docente, const Materia& materia);
    bool iniciarSesion(const string& cedula, const string& nombres,
                       const string& apellidos, const string& nrc,
                       const string& aula, const string& tipoAula,
                       const Horario& momento);
    bool cerrarSesion(const string& cedula, const string& nombres,
                      const string& apellidos, const Horario& momento);
    bool eliminarDocente(const string& cedula);
  
    void listarDocentes(void) const;

    void reporteAsistencia(void) const;
};

#endif
