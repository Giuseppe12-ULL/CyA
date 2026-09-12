// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 1: Contenedores Asociativos
// Autor: Giuseppe Fuentes Moreno
// Correo: alu0101644080@ull.edu.es
// Fecha: 08/09/2026
// Archivo: contenedor_asociativo.cc
// Descripción: Contiene la implementación detallada de los métodos y la 
//              sobrecarga de operadores para las clases Calificaciones 
//              y CalificacionesMultiples.

#include "contenedor_asociativo.h"

/**
 * @brief Se muestra un breve resumen del modo de empleo.
 * 
 */
void MostrarEmpleo(){
    std::cout << R"(
    Modo de empleo: ./Calificaciones notas.txx"
    "Pruebe 'p01_single_grades --help' para más información.
    
    )";
}

/**
 * @brief Se muestra una ayuda especial para el usuario.
 * 
 * @details La impresión se realiza con un string lineal multílinea "R(...)".
 * 
 */
void MostrarAyuda(){
    std::cout << R"(
    Uso: ./Calificaciones <fichero_entrada>

    Descripción:
    Este programa lee un fichero de texto que contiene las notas de los alumnos.
    Utiliza contenedores asociativos para procesar los datos, almacenando 
    únicamente la calificación más alta de cada estudiante o un conjunto de 
    calificaciones. Al finalizar, muestra la lista ordenada alfabéticamente.

    Opciones:
    --help            Muestra este mensaje de ayuda y termina.

    Formato del fichero de entrada:
    El archivo debe contener el nombre del estudiante y su nota separados 
    por un espacio, uno por línea.
    )";
}

/**
 * @brief Obtiene la calificación máxima de un usuario.
 * 
 * @details Utiliza .find() para buscar la clave de forma segura. Si el iterador 
 * alcanza el final del mapa (.end()), significa que no existe y retorna 0.0.
 * 
 * @param usuario Nombre del usuario a buscar.
 * @return float La calificación del usuario, o 0.0f si no se encuentra.
 */
float Calificaciones::getter_calificacion(const std::string& usuario) const {
    auto it = calificaciones.find(usuario);

    if (it != calificaciones.end()){
        return it->second;
    }

    return 0.0f;
}


/**
 * @brief Imprime las calificaciones en un flujo de salida.
 * 
 * @param out Flujo de salida de datos (ej. std::cout).
 * @param notas Objeto Calificaciones a imprimir.
 * @return std::ostream& Referencia al flujo de salida para permitir encadenamiento.
 */
std::ostream& operator<<(std::ostream& out, const Calificaciones& notas) {
    out << "Las máximas calificaciones de los usuarios son:\n";
    
    for(const auto& [usuario, calificacion] : notas.calificaciones) {
        out << usuario << " " << calificacion << "\n";
    }
    
    std::cout << "\n";
    return out;
}

/**
 * @brief Añade una nueva calificación o actualiza la nota máxima del usuario.
 * 
 * @details Si el usuario ya existe en el mapa, solo se actualiza su calificación 
 * si la nueva nota es mayor que la que ya tenía almacenada. Se imprimen los 
 * cambios.
 * 
 * @param usuario Nombre del alumno.
 * @param calificacion Nota obtenida por el alumno.
 */
void Calificaciones::AgregarCalificacion(const std::string& usuario, float calificacion) {
    auto it = calificaciones.find(usuario);

    if (it != calificaciones.end()) {
        if (it->second < calificacion) {
            it->second = calificacion;
        }
    } else {
        calificaciones[usuario] = calificacion;
    }

    std::cout << *this;
}


/**
 * @brief Filtra e imprime los estudiantes que alcanzan o superan una nota específica.
 * 
 * @details Itera sobre el mapa de calificaciones almacenando en un vector auxiliar 
 * a los alumnos que cumplen con el criterio. Al finalizar, imprime la lista de 
 * estudiantes o un mensaje indicando que ninguno superó el corte.
 * 
 * @param nota_corte El valor mínimo requerido para pasar el filtro.
 */
void Calificaciones::FiltrarNotaCorte(const float nota_corte) const {
    if (calificaciones.empty()) return;
    
    std::vector<std::string> estudiantes;

    for (const auto& par : calificaciones) {
        if (par.second >= nota_corte) {
            estudiantes.emplace_back(par.first);
        }
    }

    if (!estudiantes.empty()) {
        std::cout << "Los siguientes alumnos superaron la nota de corte de " << nota_corte << ":\n";
        for (const std::string& alumno : estudiantes) {
            std::cout << "- " << alumno << "\n"; 
        }
    } else {
        std::cout << "Ningún alumno supera la nota de corte.\n"; 
    }
}

/**
 * @brief Muestra al estudiante (o estudiantes) con la calificación máxima.
 * 
 * @details Itera sobre todo el mapa buscando el valor más alto. Si varios 
 * estudiantes comparten la misma nota máxima, se almacenan y se imprimen todos.
 */
void Calificaciones::MejorEstudiante() const {
    if (calificaciones.empty()) return; 

    float nota_maxima = -1.0f;
    std::vector<std::string> mejores_estudiantes;

    for (const auto& par : calificaciones) {
        if (par.second > nota_maxima) {
            nota_maxima = par.second;
            mejores_estudiantes.clear();
            mejores_estudiantes.push_back(par.first);
            
        } else if (par.second == nota_maxima) {
            mejores_estudiantes.push_back(par.first);
        }
    }

    std::cout << "La mejor calificación de la asignatura es " << nota_maxima << " puntos.\n";
    std::cout << "Obtenida por:\n";
    for (const std::string& alumno : mejores_estudiantes) {
        std::cout << "- " << alumno << "\n";
    }
    std::cout << "\n";
}


/**
 * @brief Elimina la calificación de un estudiante.
 * 
 * @details Utiliza el método `.erase()` mediante la clave. En un mapa normal, 
 * esto elimina la única entrada correspondiente a dicho usuario y devuelve 1 
 * si se borró con éxito, o 0 si no existía. Este valor de retorno se utiliza 
 * para verificar si la operación tuvo efecto.
 * 
 * @param usuario Identificador del alumno a dar de baja.
 */
void Calificaciones::EliminarEstudiante(const std::string& usuario) {
    std::size_t eliminados = calificaciones.erase(usuario);

    if (eliminados > 0) {
        std::cout << "Se ha eliminado al usuario: " << usuario 
                  << " (Se borraron " << eliminados << " registros)\n\n" 
                  << *this;
    } else {
        std::cout << "No se pudo eliminar: El usuario '" << usuario << "' no existe.\n\n";
    }
}

/**
 * @brief Lee calificaciones desde un flujo de entrada (fichero) y las guarda.
 * 
 * @details Si la clave no existe, se inserta. Si ya existe, se compara y solo 
 * se actualiza si la nota leída es mayor a la almacenada actualmente.
 * 
 * @param input Flujo de entrada de datos (ej. std::ifstream).
 * @param notas Objeto Calificaciones donde se guardarán los datos.
 * @return std::ifstream& Referencia al flujo de entrada.
 */
std::ifstream& operator>>(std::ifstream& input, Calificaciones& notas) {
    std::string usuario, linea;
    float calificacion;
    
    while (std::getline(input, linea)) {
        std::stringstream linea_flujo{linea};
        
        if (linea_flujo >> usuario >> calificacion) {
            auto it = notas.calificaciones.find(usuario);

            if (it != notas.calificaciones.end()) {
                if (it->second < calificacion) {
                    it->second = calificacion; 
                }
            } else {
                notas.calificaciones[usuario] = calificacion;
            }
        }
    }
    
    return input; 
}

/**
 * @brief Obtiene el historial completo de calificaciones de un alumno.
 * 
 * @details Utiliza `equal_range` para extraer un rango de iteradores que abarca 
 * todas las apariciones de las notas de un usuario específico dentro del multimapa.
 * 
 * @param usuario Nombre del alumno a buscar.
 * @return std::vector<float> Vector con todas las notas. Estará vacío si no hay coincidencias.
 */
std::vector<float> CalificacionesMultiples::getter_calificaciones(const std::string& usuario) const {
    auto rango = calificaciones_multiples.equal_range(usuario);
    std::vector<float> calificaciones;
  
    if (rango.first == rango.second){
        std::cout << "No se han encontrado calificaciones para el alumno: " << usuario << "\n";
        return calificaciones;
    }

    for (auto it = rango.first; it != rango.second; ++it){
        calificaciones.emplace_back(it->second);
    }

    return calificaciones;
}

/**
 * @brief Añade una nueva calificación e imprime la modificación.
 * 
 * @param usuario Nombre del alumno.
 * @param calificacion Nota obtenida por el alumno.
 */
void CalificacionesMultiples::AgregarCalificacion(const std::string& usuario, float calificacion) {
    calificaciones_multiples.insert({usuario,calificacion});

    std::cout << *this;
}

/**
 * @brief Calcula la nota media de un estudiante.
 * 
 * @details Reutiliza el getter para obtener el historial de notas. Si el 
 * estudiante no tiene calificaciones, devuelve 0.0 para evitar divisiones por cero.
 * 
 * @param usuario El identificador del alumno a consultar.
 * @return float La media de las notas, o 0.0f si no hay registros.
 */
float CalificacionesMultiples::MediaEstudiante(const std::string& usuario) const {
    std::vector<float> calificaciones_estudiante{this->getter_calificaciones(usuario)};
    
    if (calificaciones_estudiante.empty()) {
        return 0.0f; 
    }

    float media{0.0f};

    for (float nota : calificaciones_estudiante) {
        media += nota;
    }

    return media / calificaciones_estudiante.size();
}

/**
 * @brief Encuentra e imprime al alumno con mayor número de convocatorias (notas).
 * 
 * @details Se recorre el multimapa evaluando únicamente las claves únicas. 
 * Esto se logra gracias al método `upper_bound(clave)`, el cual busca en el 
 * árbol interno y devuelve un iterador que apunta directamente al primer elemento 
 * cuya clave sea diferente (estrictamente mayor). Esto nos permite "saltar" 
 * todos los registros duplicados del alumno actual de un solo paso.
 */
void CalificacionesMultiples::ContadorConvocatorias() const {
    std::pair<std::string, int> alumno_repetidor{"", 0};

    for (auto it{calificaciones_multiples.begin()}; it != calificaciones_multiples.end();) {
        
        int contador = calificaciones_multiples.count(it->first);
        
        if (contador > alumno_repetidor.second) {
            alumno_repetidor.first = it->first;
            alumno_repetidor.second = contador;
        }

        it = calificaciones_multiples.upper_bound(it->first);
    }

    if (alumno_repetidor.second > 0) {
        std::cout << "El alumno con mas intentos es " << alumno_repetidor.first 
                  << " con " << alumno_repetidor.second << " convocatorias.\n";
    }
}

/**
 * @brief Elimina todo el historial de calificaciones de un estudiante.
 * 
 * @details Utiliza el método `.erase()` mediante la clave. En un multimapa, 
 * esto elimina todas las entradas que coincidan con dicho usuario y devuelve 
 * la cantidad de registros borrados. Este valor de retorno se utiliza para 
 * verificar si la operación tuvo efecto.
 * 
 * @param usuario Identificador del alumno a dar de baja.
 */
void CalificacionesMultiples::EliminarEstudiante(const std::string& usuario) {
    std::size_t eliminados = calificaciones_multiples.erase(usuario);

    if (eliminados > 0) {
        std::cout << "Se ha eliminado al usuario: " << usuario 
                  << " (Se borraron " << eliminados << " registros)\n\n" 
                  << *this;
    } else {
        std::cout << "No se pudo eliminar: El usuario '" << usuario << "' no existe.\n\n";
    }
}


/**
 * @brief Lee el historial de calificaciones desde un fichero hacia el multimapa.
 * 
 * @details Inserta cada línea válida leída como un nuevo par clave-valor, 
 * permitiendo claves duplicadas automáticamente.
 * 
 * @param input Flujo de entrada de datos.
 * @param notas_multiples Objeto CalificacionesMultiples a poblar.
 * @return std::ifstream& Referencia al flujo de entrada.
 */
std::ifstream& operator>>(std::ifstream& input, CalificacionesMultiples& notas_multiples) {
    std::string usuario, linea;
    float calificacion;
    
    while (std::getline(input, linea)) {
        std::stringstream linea_flujo{linea};
        
        if (linea_flujo >> usuario >> calificacion) {
            notas_multiples.calificaciones_multiples.insert({usuario, calificacion});
        }
    }
    
    return input; 
}

/**
 * @brief Imprime el historial de calificaciones agrupadas por usuario.
 * 
 * @details Aprovecha el ordenamiento automático del multimapa. Detecta cuándo 
 * cambia la clave (usuario) para aplicar saltos de línea e imprimir el nuevo nombre, 
 * manteniendo las notas del mismo usuario en una sola línea.
 * 
 * @param out Flujo de salida de datos.
 * @param notas_multiples Objeto CalificacionesMultiples a imprimir.
 * @return std::ostream& Referencia al flujo de salida.
 */
std::ostream& operator<<(std::ostream& out, const CalificacionesMultiples& notas_multiples) {
    out << "Las calificaciones de los usuarios son:\n";
    std::string usuario_actual = "";
    
    for (const auto& par : notas_multiples.calificaciones_multiples) {
        if (usuario_actual != par.first) {
            if (usuario_actual != "") {
                out << "\n";
            }
            
            usuario_actual = par.first;
            out << usuario_actual << ": ";
        }
        out << par.second << " ";
    }
    
    out << "\n\n"; 
    
    return out;
}