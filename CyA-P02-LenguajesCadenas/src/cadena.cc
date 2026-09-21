// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 1: Lenguaje y Cadenas
// Autor: Giuseppe Fuentes Moreno
// Correo: alu0101644080@ull.edu.es
// Fecha: 19/09/2026
// Archivo: cadena.cc
// Descripción: Contiene la implementación de la clase Cadena.


#include "lenguaje_cadena_alfabeto.h"

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
    if (alfabeto_.find(Simbolo(caracter)) == alfabeto_.end()) {
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
 * @brief Sobrecarga del operador de suma (+) para concatenar cadenas.
 * 
 * Concatena dos objetos Cadena respetando la regla teórica de que 
 * el símbolo '&' representa la cadena vacía y, por tanto, actúa 
 * como elemento neutro de la concatenación.
 * 
 * @param cadena_1 Primer objeto Cadena a concatenar.
 * @param cadena_2 Segundo objeto Cadena a concatenar.
 * @return Cadena Nuevo objeto resultante de la concatenación.
 */
Cadena operator+(const Cadena& cadena_1, const Cadena& cadena_2) {
  if (cadena_1.cadena_ == "&") {
    return cadena_2;
  }
  
  if (cadena_2.cadena_ == "&") {
    return cadena_1;
  }

  return Cadena{cadena_1.cadena_ + cadena_2.cadena_};
}

/**
 * @brief Sobrecarga del operador de igualdad (==) para comparar dos cadenas.
 * 
 * Comprueba si dos objetos de la clase Cadena son exactamente iguales 
 * comparando de forma estricta su contenido interno.
 * 
 * @param cadena_1 Primer objeto Cadena a comparar.
 * @param cadena_2 Segundo objeto Cadena a comparar.
 * @return true Si las secuencias de caracteres de ambas cadenas son idénticas.
 * @return false Si las secuencias de caracteres son diferentes.
 */
bool operator==(const Cadena& cadena_1, const Cadena& cadena_2) {
  return cadena_1.cadena_ == cadena_2.cadena_;
}

/**
 * @brief Sobrecarga del operador de potencia (^) para la concatenación sucesiva.
 * 
 * Implementa la operación formal de potencia de una cadena, donde w^n 
 * equivale a concatenar la cadena w consigo misma n veces. 
 * Se cumple la propiedad teórica de que w^0 es la cadena vacía ('&').
 * 
 * @param cadena_1 Objeto Cadena base (w).
 * @param n Exponente entero que indica el número de concatenaciones.
 * @return Cadena Nuevo objeto resultante de la operación w^n.
 */
Cadena operator^(const Cadena& cadena_1, const int n) {
  if (n <= 0) {
    return Cadena{"&"};
  }

  if (n == 1 || cadena_1.cadena_ == "&") {
    return cadena_1;
  }

  std::string resultado{""};
  for (int i{0}; i < n; ++i) {
    resultado += cadena_1.cadena_;
  }

  return Cadena{resultado};
}


/**
 * @brief Comprueba si una cadena dada es subcadena de la cadena actual.
 * 
 * Verifica si la secuencia de caracteres de la cadena pasada por parámetro 
 * se encuentra contenida de forma exacta y contigua dentro de la cadena original. 
 * Respeta la propiedad teórica de que la cadena vacía ('&') es siempre 
 * subcadena de cualquier cadena.
 * 
 * @param subcadena Objeto de la clase Cadena que se desea buscar.
 * @return true Si la subcadena se encuentra contenida en la cadena actual.
 * @return false Si la secuencia de caracteres no forma parte de la cadena.
 */
bool Cadena::EsSubcadena(const Cadena& subcadena) const {
  if (subcadena.cadena_ == "&") return true;
  return cadena_.find(subcadena.cadena_) != std::string::npos;
}


/**
 * @brief Obtiene el prefijo común más largo entre dos cadenas.
 * 
 * Compara ambas cadenas desde el inicio (izquierda a derecha) para encontrar
 * la secuencia de caracteres común más extensa. Si no tienen ningún carácter 
 * inicial en común, o si alguna es la cadena vacía, devuelve '&'.
 * 
 * @param cadena Objeto Cadena con el que se va a comparar.
 * @return Cadena Nuevo objeto que contiene el prefijo común hallado.
 */
Cadena Cadena::PrefijoComun(const Cadena& cadena) const {
  if (cadena_ == "&" || cadena.cadena_ == "&") {
    return Cadena{"&"};
  }

  std::string prefijo{""};
  for (size_t i{0}; i < cadena_.size() && i < cadena.cadena_.size(); ++i) {
    if (cadena_[i] == cadena.cadena_[i]) {
      prefijo += cadena_[i];
    } else {
      break; 
    }
  }

  return (prefijo.empty()) ? Cadena{"&"} : Cadena{prefijo};
}

/**
 * @brief Obtiene el sufijo común más largo entre dos cadenas.
 * 
 * Compara ambas cadenas desde el final hacia el principio (derecha a izquierda) 
 * para encontrar la terminación común más extensa. Si no tienen ninguna 
 * terminación en común, o si alguna es la cadena vacía, devuelve '&'.
 * 
 * @param cadena Objeto Cadena con el que se va a comparar.
 * @return Cadena Nuevo objeto que contiene el sufijo común hallado.
 */
Cadena Cadena::SufijoComun(const Cadena& cadena) const {
  if (cadena_ == "&" || cadena.cadena_ == "&") {
    return Cadena{"&"};
  }

  std::string sufijo{""};
  
  int i = static_cast<int>(cadena_.size()) - 1;
  int j = static_cast<int>(cadena.cadena_.size()) - 1;

  while (i >= 0 && j >= 0) {
    if (cadena_[i] == cadena.cadena_[j]) {
      sufijo = cadena_[i] + sufijo; 
    } else {
      break;
    }
    --i;
    --j;
  }

  return (sufijo.empty()) ? Cadena{"&"} : Cadena{sufijo};
}


/**
 * @brief Genera el lenguaje formado por todas las subsecuencias de la cadena.
 * 
 * Una subsecuencia se forma eliminando cero o más caracteres de la cadena 
 * original sin alterar el orden relativo de los restantes. El algoritmo 
 * evalúa 2^n combinaciones utilizando operaciones a nivel de bits, garantizando 
 * que se extraigan todas las secuencias posibles (con y sin saltos contiguos).
 * 
 * @return Lenguaje Conjunto que contiene todas las subsecuencias generadas.
 */
Lenguaje Cadena::Subsecuencias() const {
  Lenguaje subsecuencias;
  
  if (cadena_ == "&") {
    subsecuencias.AgregarCadena(Cadena{"&"});
    return subsecuencias;
  }

  int n = static_cast<int>(cadena_.size());
  // 1 << n es el equivalente rápido en C++ a 2 elevado a n
  int total_combinaciones = 1 << n; 

  // Contamos desde 0 hasta (2^n - 1)
  for (int i{0}; i < total_combinaciones; ++i) {
    std::string subsecuencia_actual{""};
    
    // Revisamos los 'n' bits del número 'i'
    for (int j{0}; j < n; ++j) {
      // Si el bit j-ésimo de i es un 1, incluimos ese carácter
      if (i & (1 << j)) {
        subsecuencia_actual += cadena_[j];
      }
    }
    
    // Si no cogimos ninguna letra (i == 0), añadimos el símbolo '&'
    if (subsecuencia_actual.empty()) {
      subsecuencias.AgregarCadena(Cadena{"&"});
    } else {
      subsecuencias.AgregarCadena(Cadena{subsecuencia_actual});
    }
  }

  return subsecuencias;
}
