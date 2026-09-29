// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 4: Expresiones regulares en C++
// Autor: Giuseppe Fuentes Moreno
// Correo: alu0101644080@ull.edu.es
// Fecha: 29/09/2026
// Archivo: expresion_regular.cc
// Descripción: Contiene la implementación de los métodos de la clase ParseoHTML, 
//              encargados de extraer etiquetas, atributos, estructura y comentarios 
//              de un fichero HTML mediante la librería <regex>.

#include "expresion_regular.h"

/**
 * @brief Extrae las etiquetas que definen la estructura básica del documento HTML.
 * 
 * Analiza la línea de código en busca de las etiquetas principales de estructura 
 * (DOCTYPE, html, head, body). Si detecta la declaración de DOCTYPE, registra 
 * su versión (HTML5). Si detecta la apertura de las otras etiquetas estructurales, 
 * las convierte a mayúsculas y las registra como encontradas ("True") en el 
 * contenedor correspondiente. Las etiquetas de cierre son ignoradas automáticamente.
 * 
 * @param linea Referencia constante a la cadena de texto de la línea a analizar.
 * @param num_linea Número de la línea correspondiente dentro del archivo original.
 */
void ParseoHTML::ExtraerEstructura(const std::string& linea, int num_linea) {
    std::regex estructura_ocurrencia(R"(<(/|!)?(html|DOCTYPE\s+html|head|body)>)");
    std::smatch coincidencia;

    if (std::regex_search(linea, coincidencia, estructura_ocurrencia)) {
        
        std::string etiqueta_encontrada = coincidencia[2].str();

        if (etiqueta_encontrada == "DOCTYPE html") {
            estructura_["DOCTYPE"] = "HTML5";
            linea_doctype_ = num_linea;
        } 
        else if (coincidencia[1].str() != "/") {
            for (auto & c: etiqueta_encontrada) c = toupper(c);
            
            estructura_[etiqueta_encontrada] = "True";
        }
    }
}

/**
 * @brief Extrae todas las etiquetas HTML presentes en una línea de código.
 * 
 * Utiliza un iterador de expresiones regulares para localizar todas las etiquetas 
 * (de apertura o cierre) que existan en la cadena suministrada. Es capaz de extraer 
 * el nombre de la etiqueta aislando cualquier atributo que la acompañe.
 * Los resultados se insertan en el contenedor multimap de la clase.
 * 
 * @param linea Referencia constante a la cadena de texto de la línea a analizar.
 * @param num_linea Número de la línea correspondiente dentro del archivo original.
 */
void ParseoHTML::ExtraerEtiquetas(const std::string& linea, int num_linea){
    std::regex patron(R"(<(/?[a-z0-9]+)[^>]*>)");
    
    auto inicio{std::sregex_iterator(linea.begin(),linea.end(),patron)};
    auto fin{std::sregex_iterator()};

    for (auto i{inicio}; i != fin; ++i){
        std::smatch ocurrencia{*i};

        std::string etiqueta{ocurrencia[1].str()};

        etiquetas_.insert({num_linea,etiqueta});
    }
    
}

/**
 * @brief Extrae los atributos presentes en las etiquetas HTML de una línea.
 * 
 * Localiza la primera etiqueta de apertura en la línea suministrada y utiliza 
 * un iterador de expresiones regulares para extraer todos los pares clave="valor" 
 * que contenga (ej. href="enlace"). Si la etiqueta posee atributos, la estructura 
 * resultante se almacena en el contenedor de la clase.
 * 
 * @param linea Referencia constante a la cadena de texto de la línea a analizar.
 * @param num_linea Número de la línea correspondiente dentro del archivo original.
 */
void ParseoHTML::ExtraerAtributos(const std::string& linea, int num_linea) {
    std::regex patron_etiqueta(R"(<([a-zA-Z0-9]+)[^>]*>)");
    
    std::regex patron_atributo(R"([a-zA-Z\-]+="[^"]+")"); 
    std::smatch coincidencia_etiqueta;
    
    if (std::regex_search(linea, coincidencia_etiqueta, patron_etiqueta)) {
        
        Atributo atributo;
        atributo.linea = num_linea;
        atributo.etiqueta = coincidencia_etiqueta[1].str();
        
        auto inicio = std::sregex_iterator(linea.begin(), linea.end(), patron_atributo);
        auto fin = std::sregex_iterator();

        std::vector<std::string> lista_atributos;
        
        for (auto i = inicio; i != fin; ++i) {
            std::smatch ocurrencia = *i;
            lista_atributos.emplace_back(ocurrencia[0].str());
        }

        if (!lista_atributos.empty()) {
            atributo.atributos = lista_atributos;
            atributos_.emplace_back(atributo);
        }
    }
}


/**
 * @brief Procesa y extrae los comentarios HTML, tanto de una como de múltiples líneas.
 * 
 * Implementa una máquina de estados mediante la bandera `en_comentario_`. 
 * Si la clase no se encuentra procesando un bloque de comentarios, busca 
 * comentarios inline de una sola línea o la apertura de un nuevo bloque multilínea. 
 * Si ya se encuentra dentro de un bloque multilínea, concatena el contenido de 
 * la línea actual y comprueba si contiene la etiqueta de cierre (-->).
 * 
 * @param linea Referencia constante a la cadena de texto de la línea a analizar.
 * @param num_linea Número de la línea correspondiente dentro del archivo original.
 */
void ParseoHTML::ProcesarComentarios(const std::string& linea, int num_linea) {
    if (en_comentario_) {
        comentario_actual_.contenido += "\n" + linea;

        std::regex patron_cierre(R"(-->)");
        if (std::regex_search(linea, patron_cierre)) {
            comentario_actual_.linea_final = num_linea;
            comentarios_.emplace_back(comentario_actual_);
            
            en_comentario_ = false; 
            if (comentario_actual_.linea_comienzo == linea_doctype_ + 1 ){
                descripcion_ = comentario_actual_.contenido;
            }
        }
        return;
    }

    std::regex patron_unica_linea(R"(<!--(.*?)-->)");
    std::smatch coincidencia;
    
    if (std::regex_search(linea, coincidencia, patron_unica_linea)) {
        Comentario comentario;
        comentario.linea_comienzo = num_linea;
        comentario.linea_final = num_linea;
        comentario.contenido = coincidencia[0].str(); 
        
        comentarios_.emplace_back(comentario);
        if (num_linea == linea_doctype_ + 1){
            descripcion_  = comentario.contenido;
        }
        return;
    }
    
    std::regex patron_apertura(R"(<!--)");
    if (std::regex_search(linea, patron_apertura)) {
        en_comentario_ = true;
        comentario_actual_.linea_comienzo = num_linea;
        comentario_actual_.contenido = linea;
    }
}

/**
 * @brief Orquestador principal que lee y procesa un archivo HTML línea a línea.
 * 
 * Abre el archivo especificado y lo recorre secuencialmente. En cada iteración, 
 * delega la línea leída a los métodos trabajadores encargados de extraer la información.
 * Utiliza el estado interno de la clase para omitir el análisis de etiquetas, 
 * atributos y estructura cuando el lector se encuentra dentro de un bloque de 
 * comentarios multilínea.
 * 
 * @param ruta_documento Ruta o nombre del archivo HTML de entrada que se va a analizar.
 */
void ParseoHTML::ParsearDocumento(const std::string& ruta_documento){
    std::ifstream input(ruta_documento);

    if (!input){
        std::cout << "No se ha podido abrir el archivo " << ruta_documento << ".\n";
        MostrarAyuda();
        return;
    }

    std::string linea;
    int contador_linea{1};
    programa_ = ruta_documento;

    while(std::getline(input,linea)){
        ProcesarComentarios(linea,contador_linea);
        if(!en_comentario_){
            ExtraerAtributos(linea,contador_linea);
            ExtraerEstructura(linea,contador_linea);
            ExtraerEtiquetas(linea,contador_linea);
        }
        ++contador_linea;
    }
}


/**
 * @brief Sobrecarga del operador de inserción para volcar el análisis HTML.
 * 
 * Formatea el contenido almacenado en la clase ParseoHTML para que coincida 
 * estrictamente con el formato de salida exigido en la práctica, dividiendo 
 * la información en bloques: PROGRAM, DESCRIPTION, STRUCTURE, TAGS, 
 * ATTRIBUTES y COMMENTS.
 * 
 * @param out Flujo de salida (ej. archivo o std::cout).
 * @param html Objeto constante de la clase ParseoHTML que contiene los datos.
 * @return std::ostream& Referencia al flujo de salida modificado.
 */
std::ostream& operator<<(std::ostream& out, const ParseoHTML& html) {
    // 1. PROGRAMA
    out << "PROGRAM : " << html.programa_ << "\n\n";

    // 2. DESCRIPCIÓN
    out << "DESCRIPTION :\n";
    if (!html.descripcion_.empty()) {
        out << html.descripcion_ << "\n";
    } else {
        out << "No se asigno una descripción al documento." << "\n";
    }
    out << "\n";

    // 3. ESTRUCTURA BÁSICA
    out << "STRUCTURE :\n";
    if (html.estructura_.count("HTML")) out << "HTML : " << html.estructura_.at("HTML") << "\n";
    if (html.estructura_.count("HEAD")) out << "HEAD : " << html.estructura_.at("HEAD") << "\n";
    if (html.estructura_.count("BODY")) out << "BODY : " << html.estructura_.at("BODY") << "\n";
    if (html.estructura_.count("DOCTYPE")) out << "DOCTYPE : " << html.estructura_.at("DOCTYPE") << "\n";
    out << "\n";

    out << "TAGS :\n";
    for (const auto& par : html.etiquetas_) {
        out << "[ Line " << par.first << "] " << par.second << "\n";
    }
    out << "\n";

    // 5. ATRIBUTOS
    out << "ATTRIBUTES :\n";
    for (const auto& atributo : html.atributos_) {
        out << "[ Line " << atributo.linea << "] " << atributo.etiqueta << "\n";
        for (const auto& texto_atributo : atributo.atributos) {
            out << texto_atributo << "\n";
        }
        out << "\n";
    }

    // 6. COMENTARIOS
    out << "COMMENTS :\n";
    for (size_t i = 0; i < html.comentarios_.size(); ++i) {
        const auto& comentario = html.comentarios_[i];
        
        if (comentario.linea_comienzo == comentario.linea_final) {
            out << "[ Line " << comentario.linea_comienzo << "]";
            if (i == 0 && html.linea_doctype_ != -1) out << " DESCRIPTION"; 
            out << "\n";
        } else {
            out << "[ Line " << comentario.linea_comienzo << " - " << comentario.linea_final << "]\n";
        }
        out << comentario.contenido << "\n\n";
    }

    return out;
}

/**
 * @brief Muestra el modo correcto de ejecución del programa.
 * 
 * Imprime por pantalla la sintaxis necesaria para invocar el ejecutable 
 * con los parámetros requeridos por la línea de comandos.
 */
void MostrarUso() {
    std::cout << "Modo de uso: ./ExpresionesRegulares <fichero_entrada.html> <fichero_salida.txt>\n"
              << "Pruebe './ExpresionesRegulares --help' para mas informacion.\n";
}

/**
 * @brief Muestra la ayuda detallada del programa.
 * 
 * Explica el propósito del programa, los parámetros requeridos (fichero de 
 * entrada HTML y fichero de salida para el análisis) y su significado.
 */
void MostrarAyuda() {
    std::cout << "Analizador de codigo HTML mediante Expresiones Regulares.\n\n"
              << "USO:\n"
              << "  ./ExpresionesRegulares <fichero_entrada.html> <fichero_salida.txt>\n\n"
              << "PARAMETROS:\n"
              << "  <fichero_entrada.html>  Archivo de texto con codigo HTML sintacticamente correcto a analizar.\n"
              << "  <fichero_salida.txt>    Archivo de texto donde se generara el resumen de la estructura (etiquetas, atributos y comentarios).\n";
}