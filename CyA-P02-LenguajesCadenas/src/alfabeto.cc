// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 1: Lenguaje y Cadenas
// Autor: Giuseppe Fuentes Moreno
// Correo: alu0101644080@ull.edu.es
// Fecha: 19/09/2026
// Archivo: alfabeto.cc
// Descripción: Contiene la implementación de la clase Alfabeto.

#include "lenguaje_cadena_alfabeto.h"

/**
 * @brief Muestra el modo de empleo básico del programa.
 * 
 * Imprime por pantalla la sintaxis correcta para ejecutar el programa 
 * utilizando un raw string literal para mayor legibilidad del código.
 */
void MostrarUso() {
  std::cout << R"(

  Modo de empleo: ./LenguajeCadena filein.txt fileout.txt opcode
  Pruebe './LenguajeCadena --help' para más información.

)";
}

/**
 * @brief Muestra el menú de ayuda detallado del programa.
 * 
 * Imprime por pantalla un texto explicativo sobre el funcionamiento del 
 * programa y los códigos de operación, formateado mediante un raw string literal.
 */

void MostrarAyuda() {
  std::cout << R"(
  Programa: Cadenas y Lenguajes
  --------------------------------------------------------
  Este programa lee un fichero de texto donde cada linea 
  contiene una cadena y su alfabeto correspondiente, y le 
  aplica una operacion matematica o teorica segun el opcode.

  USO CORRECTO:
    ./LenguajeCadena filein.txt fileout.txt opcode

  FORMATO DEL FICHERO DE ENTRADA:
    cadena alfabeto
    Ejemplo: abbab ab
    (Nota: El simbolo '&' representa la cadena vacia).

  CODIGOS DE OPERACION (opcode):
    1 : Alfabeto      - Escribe el alfabeto asociado a la cadena.
    2 : Longitud      - Calcula la longitud de la cadena.
    3 : Inversa       - Genera la inversa de la cadena.
    4 : Prefijos      - Genera el lenguaje de prefijos de la cadena.
    5 : Sufijos       - Genera el lenguaje de sufijos de la cadena.
    6 : Validacion    - Comprueba si la cadena esta sobre el alfabeto (OK/ERROR).
    7 : Subsecuencias - Genera el lenguaje de subsecuencias (2^n combinaciones).
    8 : Oper. Cadenas - Prueba Subcadena, Prefijo y Sufijo común (contra aux "ab").
    9 : Potencia      - Eleva la cadena al cubo (cadena ^ 3).
   10 : Op. Lenguajes - Muestra Union, Interseccion, Diferencia, Concatenacion y 
                        Cierres usando los Prefijos y Sufijos como L1 y L2.
  --------------------------------------------------------
  
)";
}

// =========================================================================
// ---------------------- IMPLEMENTACIÓN DEL ALFABETO ----------------------
// =========================================================================

/**
 * @brief Constructor parametrizado de la clase Alfabeto.
 * 
 * Construye un Alfabeto extrayendo los caracteres únicos de la cadena 
 * proporcionada, omitiendo el símbolo reservado '&'.
 * 
 * @param simbolos Cadena de texto con los símbolos iniciales.
 */
Alfabeto::Alfabeto(const std::string& simbolos) {
  if (simbolos.empty()) return;

  for (const char caracter : simbolos) {
    if (caracter == '&') continue;
    alfabeto_.insert(caracter);
  }
}

/**
 * @brief Añade un nuevo símbolo de forma individual al alfabeto.
 * 
 * Inserta un símbolo en el alfabeto si no es un espacio en blanco 
 * ni el símbolo reservado de cadena vacía ('&').
 * 
 * @param simbolo Carácter individual que se desea incorporar.
 */
void Alfabeto::AgregarSimbolo(const char simbolo) {
  if (simbolo == ' ' || simbolo == '&') {
    return;
  }
  
  alfabeto_.insert(simbolo);
}

/**
 * @brief Sobrecarga del operador de inserción para imprimir un alfabeto.
 * 
 * Imprime el alfabeto en el flujo de salida con formato de conjunto (ej. {a, b}).
 * 
 * @param out Flujo de salida (fichero o consola).
 * @param alfabeto Objeto constante de la clase Alfabeto a imprimir.
 * @return std::ostream& Referencia al flujo de salida.
 */
std::ostream& operator<<(std::ostream& out, const Alfabeto& alfabeto) {
  if (alfabeto.alfabeto_.empty()) {
    out << "Los alfabetos no pueden ser conjuntos vacíos.\n";
    return out;
  }

  out << "{";
  size_t i{0};
  for (const char simbolo : alfabeto.alfabeto_) {
    out << simbolo << ((i == alfabeto.alfabeto_.size() - 1) ? "}" : ", ");
    i++; 
  }
  return out;
}

/**
 * @brief Sobrecarga del operador de extracción para leer un alfabeto.
 * 
 * Lee caracteres de un flujo de entrada y los inserta en el alfabeto 
 * utilizando AgregarSimbolo().
 * 
 * @param input Flujo de entrada (fichero o consola).
 * @param alfabeto Objeto de la clase Alfabeto a poblar.
 * @return std::istream& Referencia al flujo de entrada.
 */
std::istream& operator>>(std::istream& input, Alfabeto& alfabeto) {
  std::string simbolos;
  
  if (input >> simbolos) {
    for (const char caracter : simbolos) {
      alfabeto.AgregarSimbolo(caracter);
    }
  }

  return input;
}

/**
 * @brief Elimina un símbolo específico del alfabeto.
 * 
 * Busca el carácter indicado en el conjunto que conforma el alfabeto y lo borra.
 * Si el símbolo no se encuentra presente, muestra un mensaje informativo 
 * por la salida estándar y no altera el conjunto.
 * 
 * @param simbolo Carácter individual que se desea eliminar del alfabeto.
 */
void Alfabeto::EliminarSimbolo(const char simbolo) {
  alfabeto_.erase(simbolo);
}
