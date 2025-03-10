#ifndef NUMBER_H_
#define NUMBER_H_
#include <iostream>

template <size_t Base>
class BigInt;

class Number {
 public:
  virtual Number* add(const Number*) const = 0;
  virtual Number* subtract(const Number*) const = 0;
  virtual Number* multiply(const Number*) const = 0;
  virtual Number* divide(const Number*) const = 0;
  virtual Number* module(const Number*) const = 0;
  virtual Number* pow(const Number*) const = 0;

  virtual operator BigInt<2>() const = 0;
  virtual operator BigInt<8>() const = 0;
  virtual operator BigInt<10>() const = 0;
  virtual operator BigInt<16>() const = 0;

  static Number* create(size_t base, const std::string& s);

  virtual size_t base() const = 0;

 protected:
  virtual std::ostream& write(std::ostream&) const = 0;
  virtual std::istream& read(std::istream&) = 0;
  friend std::ostream& operator<<(std::ostream&, const Number&);
  friend std::istream& operator>>(std::istream&, Number&);
};

//Clases utilizadas para dar errores determinados
class BigIntBaseNotImplemented : public std::exception {};
class BigIntBadDigit : public std::exception {};
class BigIntDivisionByZero : public std::exception {};

#endif
