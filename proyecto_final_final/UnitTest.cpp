#include "Sistema.h"
#include "Validaciones.h"
#include <cstdio>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

int aprobadas = 0;
int fallidas = 0;

void comprobar(const string& nombre, const string& datos,
               bool esperado, bool obtenido)
{
    bool ok = esperado == obtenido;
    if (ok) aprobadas++;
    else fallidas++;
    cout << "Prueba: " << nombre << " | Datos: " << datos
              << " | Esperado: " << (esperado ? "SI" : "NO")
              << " | Obtenido: " << (obtenido ? "SI" : "NO")
              << " | " << (ok ? "APROBADA" : "FALLIDA") << '\n';
}
void igual(const string& nombre, const string& datos,
           int esperado, int obtenido)
{
    bool ok = esperado == obtenido;
    if (ok) aprobadas++;
    else fallidas++;
    cout << "Prueba: " << nombre << " | Datos: " << datos
              << " | Esperado: " << esperado << " | Obtenido: " << obtenido
              << " | " << (ok ? "APROBADA" : "FALLIDA") << '\n';
}
void limpiarArchivos()
{
    remove("__test_registros.txt");
}
int main()
{
    limpiarArchivos();
    comprobar("Mayusculas simples", "gandhi josue", true,
              Validaciones::mayusculas("gandhi josue") == "GANDHI JOSUE");
    comprobar("Mayusculas con acentos", "josé peña", true,
              Validaciones::mayusculas("josé peña") == "JOSÉ PEÑA");
    comprobar("Mayusculas con enie", "muñoz", true,
              Validaciones::mayusculas("muñoz") == "MUÑOZ");
    comprobar("Docente normaliza", "juan pérez", true,
              Docente("0503082596", "juan", "pérez").getApellidos() == "PÉREZ");
    comprobar("Materia normaliza", "estructura de datos", true,
              Materia("36865", "estructura de datos", "0503082596").getNombre() == "ESTRUCTURA DE DATOS");
    comprobar("Cedula valida", "0503082596", true,
             Validaciones::cedulaEcuatoriana("0503082596"));
    comprobar("Cedula valida", "0800837106", true,
             Validaciones::cedulaEcuatoriana("0800837106"));
    comprobar("Cedula valida", "1710034065", true,
             Validaciones::cedulaEcuatoriana("1710034065"));
    comprobar("Cedula valida", "0104047568", true,
             Validaciones::cedulaEcuatoriana("0104047568"));
    comprobar("Cedula incorrecta", "0503082595", false,
             Validaciones::cedulaEcuatoriana("0503082595"));
    comprobar("Cedula corta", "050308259", false,
             Validaciones::cedulaEcuatoriana("050308259"));
    comprobar("Cedula larga", "05030825960", false,
             Validaciones::cedulaEcuatoriana("05030825960"));
    comprobar("Cedula con letras", "050308A596", false,
             Validaciones::cedulaEcuatoriana("050308A596"));
    comprobar("Cedula vacia", "", false, Validaciones::cedulaEcuatoriana(""));
    comprobar("Provincia incorrecta", "0003082596", false,
             Validaciones::cedulaEcuatoriana("0003082596"));
    comprobar("Provincia incorrecta", "9903082596", false,
             Validaciones::cedulaEcuatoriana("9903082596"));
    comprobar("NRC correcto", "36865", true, Validaciones::numeros("36865"));
    comprobar("NRC letras", "A36865", false, Validaciones::numeros("A36865"));
    comprobar("NRC vacio", "", false, Validaciones::numeros(""));
    comprobar("Nombre sencillo", "Gandhi Josue", true, Validaciones::nombre("Gandhi Josue"));
    comprobar("Nombre con tilde", "Jos\xC3\xA9", true, Validaciones::nombre("Jos\xC3\xA9"));
    comprobar("Apellido con enie", "Pe\xC3\xB1" "a", true, Validaciones::nombre("Pe\xC3\xB1" "a"));
    comprobar("Enie Windows", "0xF1", true, Validaciones::nombre("Pe\xF1" "a"));
    comprobar("Nombre con digitos", "Jose2", false, Validaciones::nombre("Jose2"));
    comprobar("Nombre vacio", "", false, Validaciones::nombre(""));
    comprobar("Nombre doble espacio", "Juan  Luis", false, Validaciones::nombre("Juan  Luis"));
    comprobar("Nombre con espacio final", "Juan ", false, Validaciones::nombre("Juan "));
    comprobar("Materia valida", "Estructura de Datos", true, Validaciones::nombre("Estructura de Datos"));
    comprobar("Materia vacia", "", false, Validaciones::nombre(""));
    comprobar("Materia solo espacios", "   ", false, Validaciones::nombre("   "));
    comprobar("Materia separador prohibido", "Materia|Otra", false, Validaciones::nombre("Materia|Otra"));
    comprobar("Materia con numeros", "Programacion 2", false, Validaciones::nombre("Programacion 2"));
    comprobar("Materia con signos", "Algebra-Fisica", false, Validaciones::nombre("Algebra-Fisica"));
    comprobar("Materia con acento y enie", "Diseno y Programación", true, Validaciones::nombre("Diseño y Programación"));
    comprobar("Menu correcto", "8", true, Validaciones::opcion("8",1,8));
    comprobar("Menu incorrecto", "0", false, Validaciones::opcion("0",1,8));
    comprobar("Menu letras", "abc", false, Validaciones::opcion("abc",1,8));
    comprobar("Menu fuera", "10", false, Validaciones::opcion("10",1,8));
    comprobar("Formato fecha", "3000-11-08", true, Validaciones::fecha("3000-11-08"));
    comprobar("Formato fecha malo", "3000-15-25", true, Validaciones::fecha("3000-15-25"));
    comprobar("Formato fecha invalido", "3000", false, Validaciones::fecha("3000"));
    comprobar("Formato hora", "12:01", true, Validaciones::hora("12:01"));
    comprobar("Formato hora malo", "41:100", false, Validaciones::hora("41:100"));
    comprobar("Fecha inexistente", "2026-02-30", false, Horario(2026,2,30,9,0).esFechaValida());
    comprobar("Fecha valida", "2026-11-05", true, Horario(2026,11,5,9,0).esFechaValida());
    comprobar("Sabado", "2026-11-07", false, Horario(2026,11,7,7,0).esLaborable());
    comprobar("Domingo", "2026-11-08", false, Horario(2026,11,8,7,0).esLaborable());
    comprobar("Lunes", "2026-11-02", true, Horario(2026,11,2,7,0).esLaborable());

    {
        ListaDoble<int> numeros;
        comprobar("Lista doble vacia", "sin nodos", true, numeros.estaVacia());
        comprobar("Lista primero nulo", "sin nodos", true, numeros.getPrimero() == nullptr);
        comprobar("Lista ultimo nulo", "sin nodos", true, numeros.getUltimo() == nullptr);
        numeros.insertar(10);
        numeros.insertar(20);
        numeros.insertar(30);
        igual("Lista inicio", "10 20 30", 10, numeros.getPrimero()->getDato());
        igual("Lista final", "10 20 30", 30, numeros.getUltimo()->getDato());
        igual("Lista siguiente", "10 20 30", 20, numeros.getPrimero()->getSiguiente()->getDato());
        igual("Lista anterior", "10 20 30", 20, numeros.getUltimo()->getAnterior()->getDato());
        comprobar("Lista primero anterior nulo", "10", true, numeros.getPrimero()->getAnterior() == nullptr);
        comprobar("Lista ultimo siguiente nulo", "30", true, numeros.getUltimo()->getSiguiente() == nullptr);
        numeros.eliminar(numeros.getPrimero()->getSiguiente());
        igual("Eliminar nodo medio adelante", "10 30", 30, numeros.getPrimero()->getSiguiente()->getDato());
        igual("Eliminar nodo medio atras", "10 30", 10, numeros.getUltimo()->getAnterior()->getDato());
        numeros.eliminar(numeros.getPrimero());
        igual("Eliminar primero", "30", 30, numeros.getPrimero()->getDato());
        comprobar("Lista un nodo", "30", true, numeros.getPrimero() == numeros.getUltimo());
        numeros.eliminar(numeros.getUltimo());
        comprobar("Eliminar ultimo", "lista vacia", true, numeros.estaVacia());
        numeros.insertar(40);
        numeros.insertar(50);
        numeros.vaciar();
        comprobar("Vaciar lista doble", "40 50", true, numeros.getPrimero() == nullptr && numeros.getUltimo() == nullptr);
        comprobar("Eliminar nulo", "nullptr", false, numeros.eliminar(nullptr));
        comprobar("Eliminar ultimo vacio", "sin nodos", false,
                  numeros.eliminar(numeros.getUltimo()));
    }

    for (int b = 0; b < 7; b++) {
        int inicio = 7 + b*2;
        int fin = inicio + 1;
        igual("Ingreso inicio franja", to_string(inicio)+":00", b+1,
              Horario(2026,11,2,inicio,0).bloqueIngreso());
        igual("Ingreso ultimo minuto", to_string(inicio)+":10", b+1,
              Horario(2026,11,2,inicio,10).bloqueIngreso());
        igual("Ingreso un minuto tarde", to_string(inicio)+":11", 0,
              Horario(2026,11,2,inicio,11).bloqueIngreso());
        igual("Salida un minuto antes", to_string(fin)+":49", 0,
              Horario(2026,11,2,fin,49).bloqueSalida());
        igual("Salida primer minuto", to_string(fin)+":50", b+1,
              Horario(2026,11,2,fin,50).bloqueSalida());
        igual("Salida ultimo minuto", to_string(fin)+":59", b+1,
              Horario(2026,11,2,fin,59).bloqueSalida());
    }
    igual("Sabado no ingreso", "2026-11-07 07:00",0,Horario(2026,11,7,7,0).bloqueIngreso());
    igual("Domingo no ingreso", "2026-11-08 07:00",0,Horario(2026,11,8,7,0).bloqueIngreso());
    igual("Sabado no salida", "2026-11-07 08:50",0,Horario(2026,11,7,8,50).bloqueSalida());
    igual("Domingo no salida", "2026-11-08 08:50",0,Horario(2026,11,8,8,50).bloqueSalida());

    const string c1 = "0503082596";
    const string c2 = "0800837106";
    const string c3 = "1710034065";
    {
        Sistema sistema("__test_");
        comprobar("Registro 1", "Docente 1 NRC 36865",true,
                  sistema.registrarDocenteMateria(Docente(c1,"Gandhi Josue","Quinonez Corrales"),
                                                  Materia("36865","Estructura de Datos",c1)));
        comprobar("Registro materia adicional", "Docente 1 NRC 36866",true,
                  sistema.registrarDocenteMateria(Docente(c1,"Gandhi Josue","Quinonez Corrales"),
                                                  Materia("36866","Modelos Discretos",c1)));
        comprobar("Registro 2", "Docente 2 NRC 36867",true,
                  sistema.registrarDocenteMateria(Docente(c2,"Jose edien","Quinonez Simisterra"),
                                                  Materia("36867","Usabilidad",c2)));
        comprobar("NRC repetido", "36865",false,
                  sistema.registrarDocenteMateria(Docente(c1,"Gandhi Josue","Quinonez Corrales"),
                                                  Materia("36865","Repetida",c1)));
        comprobar("Cedula con otro nombre", c1,false,
                  sistema.registrarDocenteMateria(Docente(c1,"OTRO","Quinonez Corrales"),
                                                  Materia("36870","Prueba",c1)));
        comprobar("Cedula incorrecta registro", "0503082595",false,
                  sistema.registrarDocenteMateria(Docente("0503082595","Uno","Dos"),
                                                  Materia("36871","Prueba","0503082595")));
        comprobar("Nombre incorrecto", "Pepe123",false,
                  sistema.registrarDocenteMateria(Docente(c3,"Pepe123","Dos"),
                                                  Materia("36872","Prueba",c3)));
        comprobar("NRC no numerico", "MATERIA",false,
                  sistema.registrarDocenteMateria(Docente(c3,"Pedro","Dos"),
                                                  Materia("MATERIA","Prueba",c3)));
        comprobar("Rechazar materia numerica", "Calculo 2", false,
                  sistema.registrarDocenteMateria(Docente(c3,"Pedro","Vera"),
                                                  Materia("36998","Calculo 2",c3)));
        comprobar("Rechazar materia con simbolos", "Base-De-Datos", false,
                  sistema.registrarDocenteMateria(Docente(c3,"Pedro","Vera"),
                                                  Materia("36997","Base-De-Datos",c3)));
        comprobar("NRC sin docente", "cedula ajena",false,
                  sistema.registrarDocenteMateria(Docente(c3,"Pedro","Dos"),
                                                  Materia("36873","Prueba",c1)));
        comprobar("Docente no existe", "1710034065",false,
                  sistema.iniciarSesion(c3,"Pedro","Dos","36865","1","Laboratorio",Horario(2026,11,2,7,0)));
        comprobar("Nombre no coincide", "Cedula 1, otro nombre",false,
                  sistema.iniciarSesion(c1,"OTRO","Quinonez Corrales","36865","1","Laboratorio",Horario(2026,11,2,7,0)));
        comprobar("NRC de otro docente", "36867",false,
                  sistema.iniciarSesion(c1,"Gandhi Josue","Quinonez Corrales","36867","1","Laboratorio",Horario(2026,11,2,7,0)));
        comprobar("NRC inexistente", "99999",false,
                  sistema.iniciarSesion(c1,"Gandhi Josue","Quinonez Corrales","99999","1","Laboratorio",Horario(2026,11,2,7,0)));
        comprobar("Aula no numerica", "L1",false,
                  sistema.iniciarSesion(c1,"Gandhi Josue","Quinonez Corrales","36865","L1","Laboratorio",Horario(2026,11,2,7,0)));
        comprobar("Tipo aula invalido", "Patio",false,
                  sistema.iniciarSesion(c1,"Gandhi Josue","Quinonez Corrales","36865","1","Patio",Horario(2026,11,2,7,0)));
        comprobar("Ingreso tarde", "2026-11-02 07:11",false,
                  sistema.iniciarSesion(c1,"Gandhi Josue","Quinonez Corrales","36865","1","Laboratorio",Horario(2026,11,2,7,11)));
        comprobar("Ingreso sabado", "2026-11-07 07:00",false,
                  sistema.iniciarSesion(c1,"Gandhi Josue","Quinonez Corrales","36865","1","Laboratorio",Horario(2026,11,7,7,0)));
        comprobar("Ingreso domingo", "2026-11-08 07:00",false,
                  sistema.iniciarSesion(c1,"Gandhi Josue","Quinonez Corrales","36865","1","Laboratorio",Horario(2026,11,8,7,0)));
        comprobar("Busqueda sin asistencia", "2026-11-02 bloque 1", true,
                  sistema.obtenerAsistencia(c1,"2026-11-02",1) == nullptr);
        comprobar("Salida sin ingreso", "2026-11-02 08:50",false,
                  sistema.cerrarSesion(c1,"Gandhi Josue","Quinonez Corrales",Horario(2026,11,2,8,50)));
        comprobar("Ingreso valida identidad sin importar mayusculas", "gandhi jOsue / QUiNonez", true,
                  sistema.iniciarSesion(c1,"gandhi jOsue","QUINONEZ CORRALES","36865","1","laboratorio",Horario(2026,11,2,7,0)));
        comprobar("Ingreso duplicado mismo bloque", "2026-11-02 07:01", false,
                  sistema.iniciarSesion(c1,"GANDHI JOSUE","QUINONEZ CORRALES","36865","2","ESTUDIO",Horario(2026,11,2,7,1)));

        comprobar("Ingreso duplicado", "2026-11-02 07:03",false,
                  sistema.iniciarSesion(c1,"Gandhi Josue","Quinonez Corrales","36865","2","Estudio",Horario(2026,11,2,7,3)));
        comprobar("Aula ocupada", "Docente 2, lab 1",false,
                  sistema.iniciarSesion(c2,"Jose edien","Quinonez Simisterra","36867","1","Laboratorio",Horario(2026,11,2,7,5)));
        comprobar("Aula distinta", "Docente 2, lab 2",true,
                  sistema.iniciarSesion(c2,"Jose edien","Quinonez Simisterra","36867","2","Laboratorio",Horario(2026,11,2,7,5)));
        comprobar("Salida prematura", "08:49",false,
                  sistema.cerrarSesion(c1,"Gandhi Josue","Quinonez Corrales",Horario(2026,11,2,8,49)));
        comprobar("Salida valida", "08:50",true,
                  sistema.cerrarSesion(c1,"Gandhi Josue","Quinonez Corrales",Horario(2026,11,2,8,50)));
        comprobar("Salida repetida", "08:51",false,
                  sistema.cerrarSesion(c1,"Gandhi Josue","Quinonez Corrales",Horario(2026,11,2,8,51)));
        comprobar("Salida segundo docente", "08:59",true,
                  sistema.cerrarSesion(c2,"Jose edien","Quinonez Simisterra",Horario(2026,11,2,8,59)));
        comprobar("Salida fuera del bloque", "09:00",false,
                  sistema.cerrarSesion(c2,"Jose edien","Quinonez Simisterra",Horario(2026,11,2,9,0)));
        comprobar("Segundo bloque misma cedula", "09:10",true,
                  sistema.iniciarSesion(c1,"Gandhi Josue","Quinonez Corrales","36866","2","Estudio",Horario(2026,11,2,9,10)));
        comprobar("Salida segundo bloque", "10:59",true,
                  sistema.cerrarSesion(c1,"Gandhi Josue","Quinonez Corrales",Horario(2026,11,2,10,59)));
        comprobar("Ingreso siguiente dia", "2026-11-03 17:10",true,
                  sistema.iniciarSesion(c1,"Gandhi Josue","Quinonez Corrales","36865","4","Laboratorio",Horario(2026,11,3,17,10)));
        comprobar("Ingreso fuera siguiente dia", "2026-11-03 17:11",false,
                  sistema.iniciarSesion(c2,"Jose edien","Quinonez Simisterra","36867","8","Estudio",Horario(2026,11,3,17,11)));
        comprobar("Salida noche", "18:59",true,
                  sistema.cerrarSesion(c1,"Gandhi Josue","Quinonez Corrales",Horario(2026,11,3,18,59)));
        const Asistencia* registro = sistema.obtenerAsistencia(c1,"2026-11-02",1);
        comprobar("Buscar asistencia", "cedula 1 bloque 1",true,registro != nullptr);
        comprobar("Busqueda de otro bloque", "2026-11-02 bloque 3", true,
                  sistema.obtenerAsistencia(c1,"2026-11-02",3) == nullptr);
        if (registro != nullptr) {
            comprobar("Salida almacenada", "08:50",true,registro->getSalida() == "08:50");
            comprobar("NRC almacenado", "36865",true,registro->getNrc() == "36865");
            comprobar("Aula almacenada", "Laboratorio 1",true,registro->getAula() == "1" && registro->getTipoAula() == "LABORATORIO");
        }
        ostringstream salida;
        streambuf* anterior = cout.rdbuf(salida.rdbuf());
        sistema.reporteAsistencia();
        cout.rdbuf(anterior);
        comprobar("Reporte solo en orden de registro", "02 antes que 03", true,
                  salida.str().find("2026-11-02") < salida.str().find("2026-11-03"));
        comprobar("Reporte contiene datos en mayusculas", "GANDHI JOSUE", true,
                  salida.str().find("GANDHI JOSUE QUINONEZ CORRALES") != string::npos);
        comprobar("Reporte contiene materia en mayusculas", "ESTRUCTURA DE DATOS", true,
                  salida.str().find("ESTRUCTURA DE DATOS") != string::npos);
        {
            ifstream archivo("__test_registros.txt");
            string contenido((istreambuf_iterator<char>(archivo)), istreambuf_iterator<char>());
            comprobar("TXT seccion docentes", "# DOCENTES", true,
                      contenido.find("DOCENTES") != string::npos);
            comprobar("TXT seccion materias", "# MATERIAS", true,
                      contenido.find("MATERIAS") != string::npos);
            comprobar("TXT seccion asistencias", "# ASISTENCIAS", true,
                      contenido.find("ASISTENCIAS") != string::npos);
            comprobar("TXT usa nombres de registro", "DOCENTE|", true,
                      contenido.find("DOCENTE|") != string::npos &&
                      contenido.find("MATERIA|") != string::npos &&
                      contenido.find("ASISTENCIA|") != string::npos);
            comprobar("TXT no crea otros archivos", "un archivo", true,
                      contenido.find("MODELOS DISCRETOS") != string::npos);
        }
        comprobar("No eliminar con historial", c1,false,sistema.eliminarDocente(c1));
        comprobar("Tercer docente sin historial", c3,true,
                  sistema.registrarDocenteMateria(Docente(c3,"Pedro","Vera"),
                                                  Materia("36900","Programacion",c3)));
        comprobar("Eliminar tercero", c3,true,sistema.eliminarDocente(c3));
        comprobar("Eliminar no registrado", c3,false,sistema.eliminarDocente(c3));
    }
    {
        Sistema recuperado("__test_");
        ostringstream listado;
        streambuf* buffer = cout.rdbuf(listado.rdbuf());
        recuperado.listarDocentes();
        cout.rdbuf(buffer);
        comprobar("Carga TXT y conserva nombres", "GANDHI JOSUE", true,
                  listado.str().find("GANDHI JOSUE") != string::npos);
        comprobar("Carga TXT y conserva materia", "MODELOS DISCRETOS", true,
                  listado.str().find("MODELOS DISCRETOS") != string::npos);
        const Asistencia* a = recuperado.obtenerAsistencia(c1,"2026-11-02",1);
        comprobar("Recuperar salida TXT", "08:50",true,a != nullptr && a->getSalida() == "08:50");
        comprobar("Duplicado tras reinicio", "2026-11-02 07:09",false,
                  recuperado.iniciarSesion(c1,"Gandhi Josue","Quinonez Corrales","36865","4","Estudio",Horario(2026,11,2,7,9)));
        comprobar("Salida duplicada tras reinicio", "2026-11-02 08:59",false,
                  recuperado.cerrarSesion(c1,"Gandhi Josue","Quinonez Corrales",Horario(2026,11,2,8,59)));
    }
    // Compatibilidad con registros creados por la version anterior.
    {
        ofstream antiguo("__viejo_registros.txt");
        antiguo << "D|0503082596|GANDHI JOSUE|QUINONEZ CORRALES\n"
                << "M|36865|ESTRUCTURA DE DATOS|0503082596\n"
                << "A|0503082596|36865|1|LABORATORIO|2026-11-02|1|07:10|08:50\n";
    }
    {
        Sistema anterior("__viejo_");
        const Asistencia* a = anterior.obtenerAsistencia(c1, "2026-11-02", 1);
        comprobar("Lectura de archivo anterior", "D M A", true,
                  a != nullptr && a->getSalida() == "08:50");
    }
    remove("__viejo_registros.txt");
    limpiarArchivos();
    cout << "\nTOTAL: " << aprobadas + fallidas << " | APROBADAS: "
              << aprobadas << " | FALLIDAS: " << fallidas << '\n';
    return fallidas == 0 ? 0 : 1;
}
