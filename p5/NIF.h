#include<iostream>
#include<vector>
#include<string>
#include<fstream>
#include<algorithm>

//clase NIF que contiene lo necesario para almacenar un NIF y poder usar los métodos de ordenación anteriores.
class NIF {
public:
//los NIF son de 8 digitos

  NIF() : number(0) {}
  NIF(long int n) : number(n) {
    /*
    if (n < 10000000 || n > 99999999) {
      throw std::invalid_argument("NIF must be an 8-digit number");
    } else {
      number = n;
    }
    */
  }
  bool operator<(const NIF& nif) const {
    return number < nif.number;
  }
  //sobrecarga del operador/ para dividir un nif con un int
  NIF operator/(int n) const {
    return NIF(number / n);
  }
  //sobrecarga del operador% para obtener el resto de la division de un nif con un int
  int operator%(int n) const {
    return number % n;
  }

  //sobrecarga el operador=
  NIF& operator=(const NIF& nif) {
    number = nif.number;
    return *this;
  }
  friend std::ostream& operator<<(std::ostream& os, const NIF& nif) {
    os << nif.number;
    return os;
  }
  friend std::istream& operator>>(std::istream& is, NIF& nif) {
    is >> nif.number;
    //comprobar que el numero tiene 8 digitos
    if (nif.number < 10000000 || nif.number > 99999999) {
      throw std::invalid_argument("NIF must be an 8-digit number");
    } else {
      nif.number = nif.number;
    }
    return is;
  }
  //sobrecarga del operador >
  bool operator>(const NIF& nif) const {
    return number > nif.number;
  }
private:
  long int number;
};