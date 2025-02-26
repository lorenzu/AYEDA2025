#pragma once
#include "BigU.h"
#include "BigI.h"

template <unsigned char Base>
class BigRational{
  public:
  BigRational(const BigInteger<Base>& numerador=0, const BigUnsigned<Base>& denominador=1);
  BigRational(const BigRational<Base>& a) : numerador(a.numerador), denominador(a.denominador) {}

  BigRational& operator=(const BigRational&);

  bool operator==(const BigRational<Base>&) const;

  template <unsigned char B>
  friend bool operator<(const BigRational<B>& a, BigRational<B>& b);

  template <unsigned char B>
  friend std::ostream& operator<<(std::ostream&, const BigRational<B>&);

  template <unsigned char B>
  friend std::istream& operator>>(std::istream&, BigRational<B>&);

  template <unsigned char B>
  friend BigRational<B> operator+(const BigRational<B>&, const BigRational<B>&);
  BigRational<Base> operator-(const BigRational<Base>&) const;
  BigRational<Base> operator*(const BigRational<Base>&) const;

  private:
  BigInteger<Base> numerador;
  BigUnsigned<Base> denominador;
};


template <unsigned char Base>
BigRational<Base>::BigRational(const BigInteger<Base>& numerador, const BigUnsigned<Base>& denominador){
  this->numerador = numerador;
  this->denominador = denominador;
}

template <unsigned char Base>
bool operator<(const BigRational<Base>& a, BigRational<Base>& b){
  BigUnsigned<Base> temp1 = a.numerador * b.denominador;
  BigUnsigned<Base> temp2 = b.numerador * a.denominador;
  return temp1 < temp2;
}

template <unsigned char Base>
std::ostream& operator<<(std::ostream& os, const BigRational<Base>& a){
  os << a.numerador << "/" << a.denominador;
  return os;
}

template <unsigned char Base>
std::istream& operator>>(std::istream& is, BigRational<Base>& a){
  std::string temp;
  is >> temp;
  std::string delimiter = "/";
  size_t pos = 0;
  std::string token;
  pos = temp.find(delimiter);
  token = temp.substr(0, pos);
  a.numerador = BigInteger<Base>(token);
  temp.erase(0, pos + delimiter.length());
  a.denominador = BigUnsigned<Base>(temp);
  return is;
}

template <unsigned char Base>
BigRational<Base> operator+(const BigRational<Base>& a, const BigRational<Base>& b){
  BigRational<Base> temp;
  temp.denominador = a.denominador * b.denominador;
  BigInteger<Base> temp1 = a.numerador * b.denominador;
  BigInteger<Base> temp2 = b.numerador * a.denominador;
  temp.numerador = temp1 + temp2;
  return temp;
}

template <unsigned char Base>
BigRational<Base> BigRational<Base>::operator-(const BigRational<Base>& a) const{
  BigRational<Base> temp;
  temp.denominador = this->denominador * a.denominador;
  BigInteger<Base> temp1 = this->numerador * a.denominador;
  BigInteger<Base> temp2 = a.numerador * this->denominador;
  temp.numerador = temp1 - temp2;
  return temp;
}

template <unsigned char Base>
BigRational<Base> BigRational<Base>::operator*(const BigRational<Base>& a) const{
  BigRational<Base> temp;
  temp.numerador = this->numerador * a.numerador;
  temp.denominador = this->denominador * a.denominador;
  return temp;
}

template <unsigned char Base>
BigRational<Base>& BigRational<Base>::operator=(const BigRational<Base>& a){
  this->numerador = a.numerador;
  this->denominador = a.denominador;
  return *this;
}

template <unsigned char Base>
bool BigRational<Base>::operator==(const BigRational<Base>& a) const{
  BigRational<Base> temp(a);
  return *this == temp;
}