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


#include "lenguaje_cadena_alfabeto.h"


int main(int argc, char* argv[]) {
  if (argc == 2 && std::string{argv[1]} == "--help") {
    MostrarAyuda();
    return 0;
  }

  if (argc != 4) {
    MostrarAyuda(); 
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
          // Alfabeto
          archivo_salida << cadena << ": " << alfabeto << "\n";
          break;
          
        case 2:
          // Longitud
          archivo_salida << cadena.Longitud() << "\n";
          break;
          
        case 3:
          // Inversa
          archivo_salida << cadena << " -> " << cadena.Inversa() << "\n";
          break;
          
        case 4:
          // Prefijos
          archivo_salida << cadena.Prefijos() << "\n";
          break;
          
        case 5:
          // Sufijos
          archivo_salida << cadena.Sufijos() << "\n";
          break;
          
        case 6:
          // Validacion
          archivo_salida << (cadena.Validacion(alfabeto) ? "OK" : "ERROR") << "\n";
          break;

        case 7:
          // Subsecuencias (Nuevo método generador de lenguajes)
          archivo_salida << cadena.Subsecuencias() << "\n";
          break;

        case 8: {
          // Operaciones entre cadenas (usando una cadena auxiliar "ab" de prueba)
          Cadena aux{"ab"};
          archivo_salida << "Cadena: " << cadena << " | Aux: " << aux << "\n"
                         << " - EsSubcadena('ab'): " << (cadena.EsSubcadena(aux) ? "Si" : "No") << "\n"
                         << " - Prefijo Comun: " << cadena.PrefijoComun(aux) << "\n"
                         << " - Sufijo Comun: " << cadena.SufijoComun(aux) << "\n\n";
          break;
        }

        case 9:
          // Potencia de cadena (Probamos n = 3)
          archivo_salida << "Cadena original: " << cadena << "\n"
                         << "Cadena ^ 3: " << (cadena ^ 3) << "\n\n";
          break;

        case 10: {
          // Operaciones avanzadas de Lenguajes
          // Generamos L1 y L2 a partir de la propia cadena para poder operar
          Lenguaje L1 = cadena.Prefijos();
          Lenguaje L2 = cadena.Sufijos();

          archivo_salida << "--- OPERACIONES DE LENGUAJES PARA CADENA: " << cadena << " ---\n"
                         << "L1 (Prefijos) : " << L1 << "\n"
                         << "L2 (Sufijos)  : " << L2 << "\n"
                         << "Union (L1 U L2): " << L1.Union(L2) << "\n"
                         << "Intersec (L1 n L2): " << L1.Interseccion(L2) << "\n"
                         << "Diferencia (L1 - L2): " << L1.Diferencia(L2) << "\n"
                         << "Concatenacion (L1 + L2): " << (L1 + L2) << "\n"
                         << "L1 es sublenguaje de L1 U L2? : " 
                         << (L1.EsSublenguaje(L1.Union(L2)) ? "Si" : "No") << "\n"
                         << "Cierre Kleene L1 (n=2): " << L1.CierreKleene(2) << "\n"
                         << "--------------------------------------------------------\n\n";
          break;
        }
          
        default:
          std::cout << "Error: Código de operación (opcode) no válido.\n";
          MostrarAyuda(); 
          return 1;
      }
    }
  }
  
  return 0;
}