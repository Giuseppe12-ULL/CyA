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