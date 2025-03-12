#ifndef BIG_NUMBER_H
#define BIG_NUMBER_H

#include <iostream>
#include <exception>

// **Forward declarations** para evitar dependencias circulares
template <unsigned char Base>
class BigInteger;

template <unsigned char Base>
class BigRational;

template <unsigned char Base>
class BigUnsigned;

// **Clase base para todos los números grandes**
template <unsigned char Base>
class BigNumber {
public:
    // Métodos virtuales puros (deben ser implementados por las subclases)
   virtual BigNumber<Base>& add(const BigNumber<Base>&) const = 0;
   virtual BigNumber<Base>& subtract(const BigNumber<Base>&) const = 0;
   virtual BigNumber<Base>& multiply(const BigNumber<Base>&) const = 0;
   virtual BigNumber<Base>& divide(const BigNumber<Base>&) const = 0;

    virtual operator BigInteger<Base>() const = 0;
    virtual operator BigRational<Base>() const = 0;
    virtual operator BigUnsigned<Base>() const = 0;

    static BigNumber<Base>* create(const char*);  // Factory method

protected:
    virtual std::ostream& write(std::ostream&) const = 0;
    virtual std::istream& read(std::istream&) = 0;

    template <unsigned char B>
    friend std::ostream& operator<<(std::ostream&, const BigNumber<B>&);
};

class BigNumberException : public std::exception {
public:
    explicit BigNumberException(const char* msg) : message(msg) {}
    virtual const char* what() const noexcept override { return message; }

private:
    const char* message;
};

class BigNumberBadDigit : public BigNumberException {
public:
    explicit BigNumberBadDigit(const char* msg) : BigNumberException(msg) {}
};

class BigNumberDivisionByZero : public BigNumberException {
public:
    explicit BigNumberDivisionByZero(const char* msg) : BigNumberException(msg) {}
};


#include "BigI.h"  // Incluir después de la declaración de BigNumber<Base>
#include "BigR.h"  // Incluir después de la declaración de BigNumber<Base>
#include "BigU.h"  // Incluir después de la declaración de BigNumber<Base>

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
      // Si termina en 'u', creamos un BigUnsigned
      if (input.back() == 'u') {
        input.pop_back(); // Eliminar el sufijo 'u'
        return new BigUnsigned<Base>(input.c_str());
    }

  // Si contiene '/', creamos un BigRational
  if (input.find('/') != std::string::npos && input.back() == 'r') {
    input.pop_back(); // Eliminar el sufijo 'r'
    size_t pos = input.find('/');  
    if (pos == std::string::npos) {
        throw BigNumberBadDigit("Error: No se encontró el delimitador '/' en la entrada.");
    }
    std::string numerator = input.substr(0, pos);
    std::string denominator = input.substr(pos + 1);
    return new BigRational<Base>(numerator.c_str(), denominator.c_str());
}


    throw BigNumberBadDigit("Error: No se encontró un sufijo válido en la entrada.");
}

// **Sobrecarga del operador `<<`**
template <unsigned char Base>
std::ostream& operator<<(std::ostream& os, const BigNumber<Base>& num) {
    return num.write(os);
}

#endif  // BIG_NUMBER_H
