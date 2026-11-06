# ProyectoEstructuras_P1
Subt. Cabezas Kevin
Subt. Quiñonez Gandhi
# Sistema de Registro de Asistencia Docente

Proyecto final del primer parcial

## Funcionalidades
- Registro de docentes y materias con NRC.
- Validación de cédula ecuatoriana.
- Registro de entrada y salida por horarios.
- Uso de listas doblemente enlazadas.
- Almacenamiento en `registros.txt`.

## Compilación

**Programa principal:**
```bash
g++ -std=c++11 Docente.cpp Materia.cpp Asistencia.cpp Horario.cpp Validaciones.cpp Sistema.cpp main.cpp -o asistencia.exe
```

**Pruebas unitarias:**
```bash
g++ -std=c++11 Docente.cpp Materia.cpp Asistencia.cpp Horario.cpp Validaciones.cpp Sistema.cpp UnitTest.cpp -o pruebas.exe
```

## Ejecución
```bash
./asistencia.exe
./pruebas.exe
```

**Herramientas:** Visual Studio Code, g++ y PowerDesigner 16.5.
