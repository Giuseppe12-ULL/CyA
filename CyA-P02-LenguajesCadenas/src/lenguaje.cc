#include "lenguaje_cadena_alfabeto.h"

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
 * @brief Añade un nuevo objeto Cadena al Lenguaje.
 * 
 * Añade una cadena al conjunto del lenguaje, evitando duplicados automáticamente.
 * 
 * @param cadena Objeto Cadena que se desea incorporar.
 */
void Lenguaje::AgregarCadena(const Cadena& cadena) {
  lenguaje_.insert(cadena);
}

/**
 * @brief Elimina una cadena específica del lenguaje.
 * 
 * Busca el objeto Cadena proporcionado dentro del conjunto que conforma 
 * el lenguaje y lo elimina. Si la cadena no pertenece al lenguaje, 
 * el método finaliza sin alterar el conjunto.
 * 
 * @param cadena Objeto constante de tipo Cadena que se desea eliminar.
 */
void Lenguaje::EliminarCadena(const Cadena& cadena) {
  if (lenguaje_.find(cadena) == lenguaje_.end()) return;
  lenguaje_.erase(cadena);
}

/**
 * @brief Sobrecarga del operador de suma (+) para la concatenación de lenguajes.
 * 
 * Implementa la operación teórica de concatenación entre dos lenguajes (L1 · L2).
 * Genera un nuevo lenguaje combinando cada cadena del primer lenguaje con 
 * cada cadena del segundo lenguaje. Los duplicados generados se descartan 
 * automáticamente por la estructura de conjunto subyacente.
 * 
 * @param lengua_1 Primer objeto Lenguaje (prefijos de la concatenación).
 * @param lengua_2 Segundo objeto Lenguaje (sufijos de la concatenación).
 * @return Lenguaje Nuevo conjunto resultante de la operación L1 · L2.
 */
Lenguaje operator+(const Lenguaje& lenguaje_1, const Lenguaje& lenguaje_2) {
  Lenguaje concatenacion{};

  for (const auto& cadena_1 : lenguaje_1.lenguaje_) {
    for (const auto& cadena_2 : lenguaje_2.lenguaje_) {
      concatenacion.AgregarCadena(cadena_1 + cadena_2); 
    }
  }

  return concatenacion;
}




/**
 * @brief Sobrecarga del operador de potencia (^) para lenguajes.
 * 
 * Implementa la operación formal de potencia de un lenguaje (L^n), 
 * equivalente a concatenar el lenguaje consigo mismo n veces. 
 * Se basa en la propiedad de que L^0 genera de forma estricta un 
 * lenguaje que contiene únicamente la cadena vacía ('&').
 * 
 * @param lenguaje Objeto de la clase Lenguaje que actúa como base (L).
 * @param n Exponente entero que indica el número de concatenaciones sucesivas.
 * @return Lenguaje Nuevo conjunto resultante de la operación L^n.
 */
Lenguaje operator^(const Lenguaje& lenguaje, int n) {
  Lenguaje potencia{};
  potencia.AgregarCadena(Cadena{"&"}); 

  if (n <= 0) {
    return potencia;
  }

  for (int i{0}; i < n; ++i) {
    potencia = potencia + lenguaje;
  }

  return potencia;
}

/**
 * @brief Genera el lenguaje inverso.
 * 
 * Construye un nuevo lenguaje formado por la inversa de cada una de 
 * las cadenas que pertenecen al lenguaje actual.
 * 
 * @return Lenguaje Nuevo conjunto que contiene todas las cadenas invertidas.
 */
Lenguaje Lenguaje::Inversa() const {
  Lenguaje inversas{};

  for (const Cadena& cadena : lenguaje_) {
    inversas.AgregarCadena(cadena.Inversa());
  }

  return inversas;
}


/**
 * @brief Calcula la unión entre el lenguaje actual y otro proporcionado.
 * 
 * Genera un nuevo lenguaje que contiene todas las cadenas que pertenecen 
 * al lenguaje actual, al lenguaje pasado por parámetro, o a ambos. Los 
 * duplicados se eliminan automáticamente gracias a la estructura de conjunto.
 * 
 * @param lenguaje Objeto de la clase Lenguaje a unir.
 * @return Lenguaje Nuevo conjunto resultante de la operación L1 ∪ L2.
 */
Lenguaje Lenguaje::Union(const Lenguaje& lenguaje) const {
  Lenguaje union_lenguajes = *this; // Copiamos el primer lenguaje

  for (const Cadena& cadena : lenguaje.lenguaje_) {
    union_lenguajes.AgregarCadena(cadena); // Insertamos el segundo
  }
  
  return union_lenguajes;
}

/**
 * @brief Calcula la intersección entre el lenguaje actual y otro proporcionado.
 * 
 * Genera un nuevo lenguaje formado exclusivamente por aquellas cadenas 
 * que están presentes simultáneamente en ambos lenguajes.
 * 
 * @param lenguaje Objeto de la clase Lenguaje a intersecar.
 * @return Lenguaje Nuevo conjunto resultante de la operación L1 ∩ L2.
 */
Lenguaje Lenguaje::Interseccion(const Lenguaje& lenguaje) const {
  Lenguaje interseccion{};

  for (const Cadena& cadena : this->lenguaje_) {
    if (lenguaje.lenguaje_.find(cadena) != lenguaje.lenguaje_.end()) {
      interseccion.AgregarCadena(cadena);
    }
  }

  return interseccion;
}


/**
 * @brief Calcula la diferencia entre el lenguaje actual y otro proporcionado.
 * 
 * Genera un nuevo lenguaje formado por todas las cadenas que pertenecen 
 * al lenguaje actual (L1) pero que NO están presentes en el lenguaje 
 * pasado por parámetro (L2). Corresponde a la operación de conjuntos L1 \ L2.
 * 
 * @param lenguaje Objeto de la clase Lenguaje que se va a restar.
 * @return Lenguaje Nuevo conjunto resultante de la diferencia.
 */
Lenguaje Lenguaje::Diferencia(const Lenguaje& lenguaje) const {
  Lenguaje diferencia{};

  for (const Cadena& cadena : this->lenguaje_) {
    if (lenguaje.lenguaje_.find(cadena) == lenguaje.lenguaje_.end()) {
      diferencia.AgregarCadena(cadena);
    }
  }

  return diferencia;
}

/**
 * @brief Comprueba si el lenguaje actual es un sublenguaje de otro.
 * 
 * Verifica matemáticamente si el lenguaje actual (L1) es un subconjunto 
 * del lenguaje proporcionado por parámetro (L2), es decir, si L1 ⊆ L2. 
 * Se cumple por definición que el lenguaje vacío es sublenguaje 
 * de cualquier otro lenguaje.
 * 
 * @param lenguaje Objeto de la clase Lenguaje (L2) contra el que se va a comparar.
 * @return true Si todos los elementos del lenguaje actual pertenecen al lenguaje proporcionado.
 * @return false Si existe al menos un elemento en el lenguaje actual que no está en el proporcionado.
 */
bool Lenguaje::EsSublenguaje(const Lenguaje& lenguaje) const {
  if (this->lenguaje_.empty()) {
    return true; 
  }

  for (const Cadena& cadena : this->lenguaje_) {
    if (lenguaje.lenguaje_.find(cadena) == lenguaje.lenguaje_.end()) {
      return false;
    }
  }

  return true;
}


/**
 * @brief Sobrecarga del operador de igualdad (==) para lenguajes.
 * 
 * Verifica matemáticamente si dos lenguajes son estrictamente iguales. 
 * Dos lenguajes se consideran iguales si tienen la misma cardinalidad 
 * (tamaño) y contienen exactamente el mismo conjunto de cadenas.
 * 
 * @param lenguaje_1 Primer objeto de la clase Lenguaje a comparar.
 * @param lenguaje_2 Segundo objeto de la clase Lenguaje a comparar.
 * @return true Si ambos lenguajes tienen exactamente los mismos elementos.
 * @return false Si difieren en tamaño o contienen elementos distintos.
 */
bool operator==(const Lenguaje& lenguaje_1, const Lenguaje& lenguaje_2) {
  if (lenguaje_1.lenguaje_.size() != lenguaje_2.lenguaje_.size()) {
    return false;
  }

  for (const Cadena& cadena : lenguaje_1.lenguaje_) {
    if (lenguaje_2.lenguaje_.find(cadena) == lenguaje_2.lenguaje_.end()) {
      return false; 
    }
  }

  return true;
}


/**
 * @brief Calcula el Cierre de Kleene (L*) del lenguaje hasta una potencia máxima.
 * 
 * El Cierre de Kleene es la unión infinita de todas las potencias del lenguaje 
 * (L^0 ∪ L^1 ∪ L^2 ...). Como en programación no podemos calcular conjuntos 
 * infinitos, se limita el cálculo hasta una potencia máxima dada. 
 * Garantiza la inclusión de L^0, es decir, la cadena vacía ('&').
 * 
 * @param max_potencia Límite superior de iteraciones (n) para aproximar el cierre.
 * @return Lenguaje Nuevo conjunto que contiene la aproximación de L*.
 */
Lenguaje Lenguaje::CierreKleene(int max_potencia) const {
  Lenguaje resultado{};
  
  resultado.AgregarCadena(Cadena{"&"});

  for (int i{1}; i <= max_potencia; ++i) {
    resultado = resultado.Union(*this ^ i);
  }

  return resultado;
}

/**
 * @brief Calcula el Cierre Positivo (L+) del lenguaje hasta una potencia máxima.
 * 
 * El Cierre Positivo es la unión infinita de todas las potencias del lenguaje 
 * excluyendo explícitamente L^0, es decir, arrancando desde L^1 
 * (L^1 ∪ L^2 ∪ L^3 ...). Se limita computacionalmente mediante max_potencia.
 * 
 * @param max_potencia Límite superior de iteraciones (n) para aproximar el cierre.
 * @return Lenguaje Nuevo conjunto que contiene la aproximación de L+.
 */
Lenguaje Lenguaje::CierrePositivo(int max_potencia) const {
  Lenguaje resultado{};

  for (int i{1}; i <= max_potencia; ++i) {
    resultado = resultado.Union(*this ^ i);
  }

  return resultado;
}