#ifndef ALUMNO_H
#define ALUMNO_H

#include <iostream>
#include <string>
#include "NIF.h"

class Alumno{

  public:
    Alumno() = default;
    Alumno(const std::string& nombre, const std::string& apellidos, std::string clave) {
      nombre_ = nombre;
      apellidos_ = apellidos;
      clave_ = clave;
    };
    bool operator==(const Alumno& other) const;
    bool operator!=(const Alumno& other) const;
    friend std::ostream& operator<<(std::ostream& os, const Alumno& alumno);
    friend std::istream& operator>>(std::istream& is, Alumno& alumno);
    Alumno operator=(const Alumno& k);
    std::string getClave() const { return clave_; }
    std::string getNombre() const { return nombre_; }
    std::string getApellidos() const { return apellidos_; }
    operator unsigned int() const {
      int suma = 0;
      for (char c : clave_) {
        suma += c;
      }
      return suma;
    }


    private:
      std::string nombre_;
      std::string apellidos_;
      std::string clave_;
};

bool Alumno::operator==(const Alumno& other) const {
  return nombre_ == other.nombre_ && apellidos_ == other.apellidos_ && clave_ == other.clave_;
}

bool Alumno::operator!=(const Alumno& other) const {
  return !(*this == other);
}

std::ostream& operator<<(std::ostream& os, const Alumno& alumno) {
  os << alumno.clave_;
  return os;
}

std::istream& operator>>(std::istream& is, Alumno& alumno) {
  is >> alumno.nombre_;
  is >> alumno.apellidos_;
  is >> alumno.clave_;
  return is;
}

Alumno Alumno::operator=(const Alumno& k) {
  if (this != &k) {
    nombre_ = k.nombre_;
    apellidos_ = k.apellidos_;
    clave_ = k.clave_;
  }
  return *this;
}





#endif // ALUMNO_H