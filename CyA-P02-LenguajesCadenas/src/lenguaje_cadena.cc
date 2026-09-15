// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 2: Lenguaje y Cadenas
// Autor: Giuseppe Fuentes Moreno
// Correo: alu0101644080@ull.edu.es
// Fecha: 15/09/2026
// Archivo: lenguaje_cadena.cc
// Descripción: Contiene la implementación detallada de los métodos y la 
//              sobrecarga de operadores para las clases Lenguaje, Cadena
//              y Alfabeto.


#include "lenguaje_cadena.h"

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
    1 : Alfabeto   - Escribe el alfabeto asociado a la cadena.
    2 : Longitud   - Calcula la longitud de la cadena.
    3 : Inversa    - Genera la inversa de la cadena.
    4 : Prefijos   - Genera el lenguaje de prefijos de la cadena.
    5 : Sufijos    - Genera el lenguaje de sufijos de la cadena.
    6 : Validacion - Comprueba si la cadena esta sobre el alfabeto (OK/ERROR).
  --------------------------------------------------------
  
)";
}

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
void Alfabeto::AgregarSimbolo(char simbolo) {
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
 * @brief Sobrecarga del operador de extracción para leer una Cadena.
 * 
 * Lee una palabra desde el flujo de entrada y actualiza el 
 * contenido de la Cadena.
 * 
 * @param input Flujo de entrada (fichero o consola).
 * @param cadena Objeto de la clase Cadena a modificar.
 * @return std::istream& Referencia al flujo de entrada.
 */
std::istream& operator>>(std::istream& input, Cadena& cadena) {
  std::string cadena_;
  if (input >> cadena_) {
    cadena.setter_cadena(cadena_);
  }

  return input;
}

/**
 * @brief Calcula la longitud teórica de la cadena.
 * 
 * Devuelve el número de caracteres de la cadena. Si se trata de 
 * la cadena vacía ('&'), su longitud es estrictamente 0.
 * 
 * @return int Longitud total de la cadena.
 */
int Cadena::Longitud() const {
  if (cadena_ == "&") {
    return 0;
  }

  return static_cast<int>(cadena_.size());
}

/**
 * @brief Comprueba si la cadena está definida sobre un alfabeto asociado.
 * 
 * Verifica que todos los caracteres de la cadena pertenezcan al alfabeto dado. 
 * La cadena vacía ('&') siempre es válida.
 * 
 * @param alfabeto Objeto Alfabeto con los símbolos permitidos.
 * @return true Si todos los caracteres son válidos.
 * @return false Si existe al menos un carácter no permitido.
 */
bool Cadena::Validacion(const Alfabeto& alfabeto) const {
  const auto alfabeto_ = alfabeto.getter_alfabeto();
  
  if (alfabeto_.empty()) return false;
  if (cadena_ == "&") return true;

  for (const char caracter : cadena_) {
    if (alfabeto_.find(caracter) == alfabeto_.end()) {
      return false; 
    }
  }

  return true;
}

/**
 * @brief Genera el lenguaje formado por todos los prefijos de la cadena.
 * 
 * Construye progresivamente todas las subcadenas iniciales, incluyendo 
 * siempre la cadena vacía ('&') como prefijo universal por definición.
 * 
 * @return Lenguaje Conjunto que contiene todos los prefijos generados.
 */
Lenguaje Cadena::Prefijos() const {
  Lenguaje lenguaje;
  lenguaje.AgregarCadena(Cadena{"&"}); // La cadena vacía siempre es prefijo

  if (cadena_ == "&") {
    return lenguaje;
  }

  std::string cadena{""};
  for (int i{0}; i < static_cast<int>(cadena_.size()); ++i) {
    cadena += cadena_[i]; 
    lenguaje.AgregarCadena(Cadena{cadena});
  }
  
  return lenguaje;
}


/**
 * @brief Genera el lenguaje formado por todos los sufijos de la cadena.
 * 
 * Construye progresivamente todas las subcadenas finales iterando de 
 * atrás hacia adelante. Incluye siempre la cadena vacía ('&') como 
 * sufijo universal por definición teórica.
 * 
 * @return Lenguaje Conjunto que contiene todos los sufijos generados.
 */
Lenguaje Cadena::Sufijos() const {
  Lenguaje lenguaje;
  lenguaje.AgregarCadena(Cadena{"&"}); 

  if (cadena_ == "&") {
    return lenguaje;
  }

  std::string cadena{""};
  for (int i{static_cast<int>(cadena_.size()) - 1}; i >= 0; --i) {
    cadena = cadena_[i] + cadena; 
    lenguaje.AgregarCadena(Cadena{cadena});
  }
  
  return lenguaje;
}


/**
 * @brief Calcula y devuelve la inversa de la cadena.
 * 
 * Devuelve un nuevo objeto Cadena con el orden de los caracteres invertido.
 * 
 * @return Cadena Nuevo objeto con la secuencia invertida.
 */
Cadena Cadena::Inversa() const {
  if (cadena_ == "&") {
    return Cadena{"&"};
  }

  std::string cadena_inversa{""};
  
  for (int i = static_cast<int>(cadena_.size()) - 1; i >= 0; --i) {
    cadena_inversa += cadena_[i];
  }

  return Cadena{cadena_inversa};
}

/**
 * @brief Sobrecarga del operador de inserción para imprimir un Lenguaje.
 * 
 * Imprime el conjunto de cadenas del lenguaje con formato matemático 
 * (ej. {&, a, ab}). Si está vacío, imprime {}.
 * 
 * @param out Flujo de salida.
 * @param lenguaje Objeto de la clase Lenguaje a imprimir.
 * @return std::ostream& Referencia al flujo de salida.
 */
std::ostream& operator<<(std::ostream& out, const Lenguaje& lenguaje) {
  if (lenguaje.lenguaje_.empty()) {
    out << "{}";
    return out;
  }

  out << "{";
  size_t i{0};
  for (const Cadena& cadena : lenguaje.lenguaje_) {
    out << cadena << ((i == lenguaje.lenguaje_.size() - 1) ? "}" : ", ");
    i++; 
  }
  return out;
}

/**
 * @brief Sobrecarga del operador de inserción para imprimir una Cadena.
 * 
 * Escribe la secuencia de caracteres de la cadena en el flujo de salida.
 * 
 * @param out Flujo de salida.
 * @param cadena Objeto constante de la clase Cadena a imprimir.
 * @return std::ostream& Referencia al flujo de salida.
 */
std::ostream& operator<<(std::ostream& out, const Cadena& cadena){
  out << cadena.cadena_;
  return out;
}

/**
 * @brief Sobrecarga del operador menor que (<) para comparar cadenas.
 * 
 * Compara dos cadenas priorizando su longitud. En caso de empate, 
 * utiliza el orden alfabético para desempatar y evitar falsos duplicados en sets.
 * 
 * @param cadena_1 Primer objeto Cadena.
 * @param cadena_2 Segundo objeto Cadena.
 * @return true Si cadena_1 es menor que cadena_2.
 * @return false En caso contrario.
 */
bool operator<(const Cadena& cadena_1, const Cadena& cadena_2) {
  if (cadena_1.cadena_.size() == cadena_2.cadena_.size()) {
    return cadena_1.cadena_ < cadena_2.cadena_;
  }
  
  return cadena_1.cadena_.size() < cadena_2.cadena_.size();
}

/**
 * @brief Añade un nuevo objeto Cadena al Lenguaje.
 * 
 * Añade una cadena al conjunto del lenguaje, evitando duplicados automáticamente.
 * 
 * @param cadena Objeto Cadena que se desea incorporar.
 */
void Lenguaje::AgregarCadena(const Cadena& cadena) {
  lenguaje_.insert(cadena);
}