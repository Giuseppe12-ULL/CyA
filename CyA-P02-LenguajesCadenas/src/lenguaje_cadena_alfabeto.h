// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 1: Lenguaje y Cadenas
// Autor: Giuseppe Fuentes Moreno
// Correo: alu0101644080@ull.edu.es
// Fecha: 15/09/2026
// Archivo: lenguaje_cadena.h
// Descripción: Contiene la definición de las clases Alfabeto, Cadenas y Lenguaje, 
//              incluyendo sus atributos y las declaraciones de sus métodos.


#ifndef LENGUAJE_CADENA_ALFABETO_H
#define LENGUAJE_CADENA_ALFABETO_H

#include <iostream>
#include <map>
#include <set>
#include <string>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <iostream>

void MostrarUso();

void MostrarAyuda();

class Alfabeto{
  public:
    ~Alfabeto(){}
    Alfabeto(const std::string& simbolos = "");
    friend std::ostream& operator<<(std::ostream& out, const Alfabeto& alfabeto);
    friend std::istream& operator>>(std::istream& input, Alfabeto& alfabeto);
    std::set<char> getter_alfabeto() const {return alfabeto_;};
    void AgregarSimbolo(const char simbolo);
    void EliminarSimbolo(const char simbolo);
  private:
    std::set<char> alfabeto_{};
};

class Cadena; 

class Lenguaje{
  public:
    ~Lenguaje(){};
    Lenguaje(){};
    const std::set<Cadena>& getter_lenguaje() const {return lenguaje_;};
    Lenguaje Inversa() const;
    Lenguaje Union(const Lenguaje& lenguaje) const;
    Lenguaje Interseccion(const Lenguaje& lenguaje) const;
    Lenguaje Diferencia(const Lenguaje& lenguaje) const;
    Lenguaje CierreKleene(int max_potencia) const;
    Lenguaje CierrePositivo(int max_potencia) const;
    bool EsSublenguaje(const Lenguaje& lenguaje) const;
    void AgregarCadena(const Cadena& cadena);
    void EliminarCadena(const Cadena& cadena);
    friend bool operator==(const Lenguaje& lenguaje_1, const Lenguaje& lenguaje_2);
    friend std::ostream& operator<<(std::ostream& out,const Lenguaje& lenguaje);
    friend Lenguaje operator+(const Lenguaje& lenguaje_1, const Lenguaje& lenguaje_2);
    friend Lenguaje operator^(const Lenguaje& lenguaje, int n);
  private:
    std::set<Cadena> lenguaje_;
};

class Cadena{
  public:
    ~Cadena(){}
    Cadena(const std::string& cadena = "") : cadena_{cadena}{}
    int Longitud() const;
    Cadena Inversa() const;
    Lenguaje Prefijos() const;
    Lenguaje Sufijos() const;
    bool Validacion(const Alfabeto& alfabeto) const;
    bool EsSubcadena(const Cadena& subcadena) const;
    Cadena PrefijoComun(const Cadena& cadena) const;
    Cadena SufijoComun(const Cadena& cadena) const;
    Lenguaje Subsecuencias() const;
    friend Cadena operator+(const Cadena& cadena_1, const Cadena& cadena_2);
    friend bool operator==(const Cadena& cadena_1, const Cadena& cadena_2);
    friend Cadena operator^(const Cadena& cadena_1, const int n);
    friend std::ostream& operator<<(std::ostream& out, const Cadena& cadena);
    friend std::istream& operator>>(std::istream& input, Cadena& cadena);
    friend bool operator<(const Cadena& cadena_1, const Cadena& cadena_2);
    std::string getter_cadena() const {return cadena_;};
    void setter_cadena(const std::string& cadena_nueva){cadena_ = cadena_nueva;};
  private:
    std::string cadena_{""};
};



#endif