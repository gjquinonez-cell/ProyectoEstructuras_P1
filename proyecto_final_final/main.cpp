#include "Sistema.h"
#include "Validaciones.h"
#include <cstdlib>
#include <iostream>
#include <string>
using namespace std;

string leer(const string& mensaje)
{
    string dato;
    cout << mensaje;
    getline(cin, dato);
    return dato;
}

// No se pasa al siguiente campo hasta que el dato sea valido.
string leerDato(const string& mensaje, const string& tipo)
{
    while (cin)
    {
        string dato = Validaciones::mayusculas(leer(mensaje));
        if (!cin)
        {
            return "";
        }
        if (tipo == "cedula")
        {
            if (Validaciones::cedulaEcuatoriana(dato)) return dato;
            cout << "[!] CEDULA  INVALIDA.\n";
        }
        else if (tipo == "numero")
        {
            if (Validaciones::numeros(dato)) return dato;
            cout << "[!] INGRESE SOLO NUMEROS.\n";
        }
        else
        {
            if (Validaciones::nombre(dato)) return dato;
            cout << "[!] INGRESE SOLO LETRAS Y ESPACIOS.\n";
        }
    }
    return "";
}

string leerOpcion(const string& mensaje, int minimo, int maximo)
{
    while (cin)
    {
        string dato = leer(mensaje);
        if (!cin || Validaciones::opcion(dato, minimo, maximo))
        {
            return dato;
        }
        cout << "[!] OPCION INCORRECTA.\n";
    }
    return "";
}

Docente leerDocente(void)
{
    string cedula = leerDato("CEDULA: ", "cedula");
    if (!cin) return Docente();
    string nombres = leerDato("NOMBRES: ", "nombre");
    if (!cin) return Docente();
    string apellidos = leerDato("APELLIDOS: ", "nombre");
    return Docente(cedula, nombres, apellidos);
}

Horario obtenerMomento(bool simulando, const Horario& simulada)
{
    return simulando ? simulada : Horario::ahora();
}

Horario leerHoraSimulada(void)
{
    string fecha;
    string hora;
    while (cin)
    {
        fecha = leer("FECHA (AAAA-MM-DD): ");
        if (!cin) break;
        if (Validaciones::fecha(fecha))
        {
            Horario prueba(atoi(fecha.substr(0, 4).c_str()),
                           atoi(fecha.substr(5, 2).c_str()),
                           atoi(fecha.substr(8, 2).c_str()), 12, 0);
            if (prueba.esFechaValida()) break;
        }
        cout << "[!] FECHA INCORRECTA.\n";
    }
    while (cin)
    {
        hora = leer("HORA (HH:MM): ");
        if (!cin) break;
        if (Validaciones::hora(hora))
        {
            Horario prueba(2000, 1, 1,
                           atoi(hora.substr(0, 2).c_str()),
                           atoi(hora.substr(3, 2).c_str()));
            if (prueba.esFechaValida()) break;
        }
        cout << "[!] HORA INCORRECTA.\n";
    }
    if (!cin)
    {
        return Horario();
    }
    return Horario(atoi(fecha.substr(0, 4).c_str()),
                   atoi(fecha.substr(5, 2).c_str()),
                   atoi(fecha.substr(8, 2).c_str()),
                   atoi(hora.substr(0, 2).c_str()),
                   atoi(hora.substr(3, 2).c_str()));
}

int main(void)
{
    Sistema sistema;
    bool simulando = false;
    Horario simulada;
    string opcion;

    do
    {
        Horario momento = obtenerMomento(simulando, simulada);
        cout << "\n===== REGISTRO DE ASISTENCIA DOCENTE =====\n"
             << "1. REGISTRAR DOCENTE Y MATERIA\n"
             << "2. INICIAR SESION (MARCAR INGRESO)\n"
             << "3. CERRAR SESION (MARCAR SALIDA)\n"
             << "4. LISTAR DOCENTES\n"
             << "5. REPORTE DE ASISTENCIA\n"
             << "6. ELIMINAR DOCENTE\n"
             << "7. MODO DEMOSTRACION (SIMULAR HORA)\n"
             << "8. SALIR\n"
             << "HORA: " << momento.getFecha() << ' ' << momento.getHoraTexto()
             << (simulando ? " (SIMULADA)" : "") << '\n';
        opcion = leerOpcion("OPCION: ", 1, 8);
        if (!cin) break;

        if (opcion == "1")
        {
            Docente docente = leerDocente();
            if (!cin) break;
            string nombreMateria = leerDato("MATERIA: ", "nombre");
            string nrc = leerDato("NRC: ", "numero");
            if (!cin) break;
            sistema.registrarDocenteMateria(docente,
                Materia(nrc, nombreMateria, docente.getCedula()));
            cout << sistema.getMensaje() << '\n';
        }
        else if (opcion == "2")
        {
            momento = obtenerMomento(simulando, simulada);
            if (momento.bloqueIngreso() == 0)
            {
                cout << "[!] INGRESO SOLO DE LUNES A VIERNES DE 07:00 A 21:00 CON HASTA 10 MINUTOS.\n";
                continue;
            }
            Docente docente = leerDocente();
            if (!cin) break;
            string nrc = leerDato("NRC: ", "numero");
            string aula = leerDato("NUMERO DE AULA: ", "numero");
            string tipo = leerOpcion("TIPO (1=LABORATORIO, 2=ESTUDIO): ", 1, 2);
            if (!cin) break;
            momento = obtenerMomento(simulando, simulada);
            sistema.iniciarSesion(docente.getCedula(), docente.getNombres(),
                docente.getApellidos(), nrc, aula,
                tipo == "1" ? "LABORATORIO" : "ESTUDIO", momento);
            cout << sistema.getMensaje() << '\n';
        }
        else if (opcion == "3")
        {
            momento = obtenerMomento(simulando, simulada);
            if (momento.bloqueSalida() == 0)
            {
                cout << "[!] SALIDA SOLO EN LOS ULTIMOS 10 MINUTOS DEL BLOQUE.\n";
                continue;
            }
            Docente docente = leerDocente();
            if (!cin) break;
            momento = obtenerMomento(simulando, simulada);
            sistema.cerrarSesion(docente.getCedula(), docente.getNombres(),
                                 docente.getApellidos(), momento);
            cout << sistema.getMensaje() << '\n';
        }
        else if (opcion == "4")
        {
            sistema.listarDocentes();
        }
        else if (opcion == "5")
        {
            sistema.reporteAsistencia();
        }
        else if (opcion == "6")
        {
            string cedula = leerDato("CEDULA A ELIMINAR: ", "cedula");
            if (!cin) break;
            sistema.eliminarDocente(cedula);
            cout << sistema.getMensaje() << '\n';
        }
        else if (opcion == "7")
        {
            string modo = leerOpcion("1. SIMULAR HORA  2. HORA REAL: ", 1, 2);
            if (!cin) break;
            if (modo == "1")
            {
                simulada = leerHoraSimulada();
                if (!cin) break;
                simulando = true;
                cout << "HORA SIMULADA FIJADA.\n";
            }
            else
            {
                simulando = false;
                cout << "REGRESO A LA HORA REAL.\n";
            }
        }
    } while (opcion != "8" && cin);
    cout << "PROGRAMA FINALIZADO.\n";
    return 0;
}
