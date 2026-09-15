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


#ifndef LENGUAJE_CADENA_H
#define LENGUAJE_CADENA_H

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
  private:
    std::set<char> alfabeto_{};
};

class Cadena; 

class Lenguaje{
  public:
    ~Lenguaje(){};
    Lenguaje(){};
    friend std::ostream& operator<<(std::ostream& out,const Lenguaje& lenguaje);
    std::set<Cadena> getter_lenguaje() const {return lenguaje_;};
    void AgregarCadena(const Cadena& cadena);
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
    friend std::ostream& operator<<(std::ostream& out, const Cadena& cadena);
    friend std::istream& operator>>(std::istream& input, Cadena& cadena);
    friend bool operator<(const Cadena& cadena_1, const Cadena& cadena_2);
    std::string getter_cadena() const {return cadena_;};
    void setter_cadena(const std::string& cadena_nueva){cadena_ = cadena_nueva;};
  private:
    std::string cadena_{""};
};



#endif