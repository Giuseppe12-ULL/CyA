// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 4: Expresiones regulares en C++
// Autor: Giuseppe Fuentes Moreno
// Correo: alu0101644080@ull.edu.es
// Fecha: 29/09/2026
// Archivo: main_expresion_regular.cc
// Descripción: Contiene la función principal (main) del programa, encargada 
//              de procesar los argumentos de la línea de comandos e instanciar 
//              la clase ParseoHTML para analizar el fichero de entrada.


#include "expresion_regular.h"

int main(int argc, char* argv[]) {
    if (argc == 2 && std::string{argv[1]} == "--help") {
        MostrarAyuda();
        return 0;
    }

    if (argc != 3) {
        MostrarUso();
        return 1;
    }

    std::string direccion_entrada{argv[1]};
    std::string direccion_salida{argv[2]};

    std::ofstream out(direccion_salida);

    if (!out) {
        std::cout << "No se ha podido abrir el documento " << direccion_salida << ".\n";
        MostrarAyuda();
        return 1;
    }

    ParseoHTML html;
    html.ParsearDocumento(direccion_entrada);
    out << html;

    return 0;
}