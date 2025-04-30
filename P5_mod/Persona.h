#ifndef PERSONA_H
#define PERSONA_H
//alumno clave -> letras y numeros

#include <iostream>
#include "NIF.h"
#include <string>

class Persona{

  public:
    Persona() = default;
    Persona(const std::string& nombre, const std::string& apellidos, std::string nif_with_letra) {
      nombre_ = nombre;
      apellidos_ = apellidos;
      //el string de nif se pasa a long
      long numbers = std::stol(nif_with_letra.substr(0, 8));
      nif_ = nif(numbers);
      letra_ = nif_with_letra.substr(8, 1);
    };
    bool operator==(const Persona& other) const;
    bool operator!=(const Persona& other) const;
    friend std::ostream& operator<<(std::ostream& os, const Persona& persona);
    friend std::istream& operator>>(std::istream& is, Persona& persona);
    Persona operator=(const Persona& k);
    //sobrecarga del unsigned int
    operator unsigned int() const {
      return nif_ + letra_[0];
    }

  private:
    std::string nombre_;
    std::string apellidos_;
    nif nif_;
    std::string letra_;

};

bool Persona::operator==(const Persona& other) const {
  return nombre_ == other.nombre_ && apellidos_ == other.apellidos_ && nif_ == other.nif_;
}

bool Persona::operator!=(const Persona& other) const {
  return !(*this == other);
}

std::ostream& operator<<(std::ostream& os, const Persona& persona) {
  os << "Nombre: " << persona.nombre_ << ", Apellidos: " << persona.apellidos_ << ", NIF: " << persona.nif_;
  return os;
}

//operator=
Persona Persona::operator=(const Persona& k) {
  nombre_ = k.nombre_;
  apellidos_ = k.apellidos_;
  nif_ = k.nif_;
  return *this;
}
std::istream& operator>>(std::istream& is, Persona& persona) {
  std::cout << "Introduce el nombre: ";
  is >> persona.nombre_;
  std::cout << "Introduce los apellidos: ";
  is >> persona.apellidos_;
  std::cout << "Introduce el NIF: ";
  is >> persona.nif_;
  return is;
}

#endif // PERSONA_H