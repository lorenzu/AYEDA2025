#ifndef BIG_NUMBER_H
#define BIG_NUMBER_H

#include <iostream>
#include <exception>

// **Forward declarations** para evitar dependencias circulares
template <unsigned char Base>
class BigInteger;

template <unsigned char Base>
class BigRational;

// **Clase base para todos los números grandes**
template <unsigned char Base>
class BigNumber {
public:
    // Métodos virtuales puros (deben ser implementados por las subclases)
   // virtual BigNumber<Base>& add(const BigNumber<Base>&) const = 0;
   // virtual BigNumber<Base>& subtract(const BigNumber<Base>&) const = 0;
   // virtual BigNumber<Base>& multiply(const BigNumber<Base>&) const = 0;
   // virtual BigNumber<Base>& divide(const BigNumber<Base>&) const = 0;

    virtual operator BigInteger<Base>() const = 0;
    //virtual operator BigRational<Base>() const = 0;

    static BigNumber<Base>* create(const char*);  // Factory method

protected:
    virtual std::ostream& write(std::ostream&) const = 0;

    template <unsigned char B>
    friend std::ostream& operator<<(std::ostream&, const BigNumber<B>&);
};

// **Excepciones específicas para la jerarquía de BigNumber**
class BigNumberBaseNotImplemented : public std::exception {};
class BigNumberBadDigit : public std::exception {};
class BigNumberDivisionByZero : public std::exception {};

#include "BigI.h"  // Incluir después de la declaración de BigNumber<Base>

// **Implementación de `create`**
template <unsigned char Base>
BigNumber<Base>* BigNumber<Base>::create(const char* str) {
  std::string input(str);
    
  if (input.empty()) {
      std::cerr << "Error: La cadena de entrada está vacía." << std::endl;
      return nullptr;
  }

  // Si termina en 'i', creamos un BigInteger
  if (input.back() == 'i') {
      input.pop_back(); // Eliminar el sufijo 'i'
      return new BigInteger<Base>(input.c_str());
  }

  std::cerr << "Error: Tipo de número grande no reconocido." << std::endl;
  return nullptr;
}

// **Sobrecarga del operador `<<`**
template <unsigned char Base>
std::ostream& operator<<(std::ostream& os, const BigNumber<Base>& num) {
    return num.write(os);
}

#endif  // BIG_NUMBER_H
