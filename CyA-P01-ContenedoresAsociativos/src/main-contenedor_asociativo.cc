// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 1: Contenedores Asociativos
// Autor: Giuseppe Fuentes Moreno
// Correo: alu0101644080@ull.edu.es
// Fecha: 08/09/2026
// Archivo: p01_single_grades.cc
// Descripción: Programa cliente. Contiene la función main del proyecto 
//              que utiliza las clases de los contenedores asociativos 
//              para procesar y mostrar las notas desde un fichero de texto.

#include "contenedor_asociativo.h" 

int main(int argc, char* argv[]) {
    if (argc != 2) {
        MostrarEmpleo(); 
        return 1; 
    }

    std::string direccion = argv[1];

    if (direccion == "--help") {
        MostrarAyuda();
        return 0; 
    }

    std::ifstream archivo(direccion);
    if (!archivo) {
        std::cout << "No se ha podido abrir el archivo: " << direccion << "\n";
        return 1;
    }

    Calificaciones calificaciones;
    CalificacionesMultiples calificaciones_multiples;

    archivo >> calificaciones_multiples;

    archivo.clear(); // Limpiamos la bandera de "Fin de archivo"
    archivo.seekg(0); // Movemos el cursor a la posición 0 (al principio)

    archivo >> calificaciones;

    std::cout << "=== ESTADO INICIAL ===\n\n";
    std::cout << calificaciones;
    std::cout << calificaciones_multiples;

    std::cout << "=== PRUEBAS DE INSERCIÓN ===\n\n";
    calificaciones.AgregarCalificacion("alu0101644080", 9.4);
    calificaciones_multiples.AgregarCalificacion("alu0101644080", 9.2);

    std::cout << "=== PRUEBAS MAPA (Calificaciones) ===\n\n";

    calificaciones.MejorEstudiante();

    std::cout << "Filtrando por nota de corte (ej. 7.0):\n";
    calificaciones.FiltrarNotaCorte(7.0f);
    std::cout << "\n";

    std::cout << "Eliminando al estudiante insertado:\n";
    calificaciones.EliminarEstudiante("alu0101644080");

    std::cout << "=== PRUEBAS MULTIMAPA (CalificacionesMultiples) ===\n\n";

    std::string alumno_prueba = "alu0155555555";
    std::cout << "La nota media de " << alumno_prueba << " es: " 
                << calificaciones_multiples.MediaEstudiante(alumno_prueba) << "\n\n";
                
    calificaciones_multiples.ContadorConvocatorias();
    std::cout << "\n";

    std::cout << "Eliminando al estudiante insertado en el multimapa:\n";
    calificaciones_multiples.EliminarEstudiante("alu0101644080");

    return 0;
}