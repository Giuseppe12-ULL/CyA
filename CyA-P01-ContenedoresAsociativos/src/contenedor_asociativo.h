// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 1: Contenedores Asociativos
// Autor: Giuseppe Fuentes Moreno
// Correo: alu0101644080@ull.edu.es
// Fecha: 08/09/2026
// Archivo: contenedor_asociativo.h
// Descripción: Contiene la definición de las clases Calificaciones y 
//              CalificacionesMultiples, incluyendo sus atributos y las 
//              declaraciones de sus métodos.

#ifndef CONTENEDOR_ASOCIATIVO_H
#define CONTENEDOR_ASOCIATIVO_H

#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include <stdexcept>
#include <sstream>
#include <vector>
#include <utility>

void MostrarEmpleo();

void MostrarAyuda();

class Calificaciones{
    public:
      Calificaciones() : calificaciones{} {};
      ~Calificaciones(){};
      float getter_calificacion(const std::string& usuario) const;
      void AgregarCalificacion(const std::string& usuario, float calificacion);
      void FiltrarNotaCorte(const float nota_corte) const;
      void MejorEstudiante() const;
      void EliminarEstudiante(const std::string& usuario);
      friend std::ifstream& operator>>(std::ifstream& input, Calificaciones& notas);
      friend std::ostream& operator<<(std::ostream& out, const Calificaciones& notas);
    private:
      std::map<std::string,float> calificaciones;
};

class CalificacionesMultiples{
    public:
      CalificacionesMultiples() : calificaciones_multiples{} {};
      ~CalificacionesMultiples(){};
      std::vector<float> getter_calificaciones(const std::string& usuario) const;
      void AgregarCalificacion(const std::string& usuario, float calificacion);
      float MediaEstudiante(const std::string& usuario) const;
      void ContadorConvocatorias() const;
      void EliminarEstudiante(const std::string& usuario);
      friend std::ifstream& operator>>(std::ifstream& input, CalificacionesMultiples& notas_multiples);
      friend std::ostream& operator<<(std::ostream& out, const CalificacionesMultiples& notas_multiples);
    private:
      std::multimap<std::string,float> calificaciones_multiples;
      
};

#endif