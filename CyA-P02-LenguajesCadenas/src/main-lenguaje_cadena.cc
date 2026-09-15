// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 2: Lenguajes y Cadenas
// Autor: Giuseppe Fuentes Moreno
// Correo: alu0101644080@ull.edu.es
// Fecha: 15/09/2026
// Archivo: main-lenguaje_cadena.cc
// Descripción: Programa cliente. Contiene la función main del proyecto 
//              que utiliza las clases para procesar lenguajes y cadenas.


#include "lenguaje_cadena.h"

int main(int argc, char* argv[]) {
  if (argc == 2 && std::string{argv[1]} == "--help") {
    MostrarAyuda();
    return 0;
  }

  if (argc != 4) {
    MostrarUso();
    return 1;
  }

  std::string direccion_entrada{argv[1]};
  std::string direccion_salida{argv[2]};
  int opcode{std::atoi(argv[3])};

  std::ifstream archivo_entrada{direccion_entrada};
  std::ofstream archivo_salida{direccion_salida}; 

  if (!archivo_entrada || !archivo_salida) {
    std::cout << "No se ha podido abrir alguno de los dos ficheros: " 
              << direccion_entrada << " | " << direccion_salida << " .\n";
    return 1;
  }

  std::string linea;
  
  
  while (std::getline(archivo_entrada, linea)) {
    std::stringstream flujo_linea{linea};
    Cadena cadena;
    Alfabeto alfabeto;
    
    if (flujo_linea >> cadena >> alfabeto) {
      
      switch (opcode) {
        case 1:
          // Alfabeto: Imprime la cadena y el alfabeto asociado entre llaves
          archivo_salida << cadena << ": " << alfabeto << "\n";
          break;
          
        case 2:
          // Longitud: Imprime el valor numérico de la longitud de la cadena
          archivo_salida << cadena.Longitud() << "\n";
          break;
          
        case 3:
          // Inversa: Imprime la cadena original, una flecha, y la cadena invertida
          archivo_salida << cadena << " -> " << cadena.Inversa() << "\n";
          break;
          
        case 4:
          // Prefijos: Genera el lenguaje de prefijos y lo imprime con formato de conjunto
          archivo_salida << cadena.Prefijos() << "\n";
          break;
          
        case 5:
          // Sufijos: Genera el lenguaje de sufijos y lo imprime con formato de conjunto
          archivo_salida << cadena.Sufijos() << "\n";
          break;
          
        case 6:
          // Validación: Comprueba la pertenencia de los símbolos e imprime OK o ERROR
          archivo_salida << (cadena.Validacion(alfabeto) ? "OK" : "ERROR") << "\n";
          break;
          
        default:
          // Si el opcode no está entre 1 y 6, abortamos mostrando el uso
          std::cout << "Error: Código de operación (opcode) no válido.\n";
          MostrarUso();
          return 1;
      }
    }
  }
  
  return 0;
}