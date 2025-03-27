#pragma once
#include "BigU.h"
#include "BigI.h"
#include "BigNumber.h"

template <unsigned char Base>
class BigRational: public BigNumber<Base>{ 
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
  BigRational<Base> operator/(const BigRational<Base>&) const;

  BigNumber<Base>& add(const BigNumber<Base>&) const override;
  BigNumber<Base>& subtract(const BigNumber<Base>&) const override;
  BigNumber<Base>& multiply(const BigNumber<Base>&) const override;
  BigNumber<Base>& divide(const BigNumber<Base>&) const override;
  bool compare(const BigNumber<Base>&, const BigNumber<Base>&) const override;

  
  operator BigInteger<Base>() const override;
  operator BigRational<Base>() const override;
  operator BigUnsigned<Base>() const override;

  protected:
  std::ostream& write(std::ostream&) const override;
  std::istream& read(std::istream&) override;

  private:
  BigInteger<Base> numerador;
  BigUnsigned<Base> denominador;
};

template <unsigned char Base>
bool BigRational<Base>::compare(const BigNumber<Base>& a, const BigNumber<Base>& b) const {
    if (const BigRational<Base>* ratOther = dynamic_cast<const BigRational<Base>*>(&a)) {
        return *(new BigRational<Base>(*this < *ratOther));
    } else if (const BigInteger<Base>* intOther = dynamic_cast<const BigInteger<Base>*>(&a)) {
        // Convertimos el BigInteger en una fracción (con denominador 1)
        BigRational<Base> intAsRational(*intOther, "1");
        return *(new BigRational<Base>(*this < intAsRational));
    } else if (const BigUnsigned<Base>* uintOther = dynamic_cast<const BigUnsigned<Base>*>(&a)) {
        // Convertimos el BigUnsigned en una fracción (con denominador 1)
        BigInteger<Base> intConverted(*uintOther); // BigUnsigned → BigInteger
        BigRational<Base> uintAsRational(intConverted, "1");
        return *(new BigRational<Base>(*this < uintAsRational));
    }
    throw std::invalid_argument("Tipo de BigNumber no compatible con add()");
}

template <unsigned char Base>
BigNumber<Base>& BigRational<Base>::divide(const BigNumber<Base>& a) const{
  if (const BigRational<Base>* ratOther = dynamic_cast<const BigRational<Base>*>(&a)) {
    return *(new BigRational<Base>(*this / *ratOther));
} else if (const BigInteger<Base>* intOther = dynamic_cast<const BigInteger<Base>*>(&a)) {
    // Convertimos BigInteger en BigRational con denominador 1
    BigRational<Base> intAsRational(*intOther, "1");
    return *(new BigRational<Base>(*this / intAsRational));
} else if (const BigUnsigned<Base>* uintOther = dynamic_cast<const BigUnsigned<Base>*>(&a)) {
    // Convertimos BigUnsigned en BigInteger y luego en BigRational
    BigInteger<Base> intConverted(*uintOther);
    BigRational<Base> uintAsRational(intConverted, "1");
    return *(new BigRational<Base>(*this / uintAsRational));
}
throw std::invalid_argument("Tipo de BigNumber no compatible con multiply()");
} 

template <unsigned char Base>
BigNumber<Base>& BigRational<Base>::multiply(const BigNumber<Base>& a) const {
    if (const BigRational<Base>* ratOther = dynamic_cast<const BigRational<Base>*>(&a)) {
        return *(new BigRational<Base>(*this * *ratOther));
    } else if (const BigInteger<Base>* intOther = dynamic_cast<const BigInteger<Base>*>(&a)) {
        // Convertimos BigInteger en BigRational con denominador 1
        BigRational<Base> intAsRational(*intOther, "1");
        return *(new BigRational<Base>(*this * intAsRational));
    } else if (const BigUnsigned<Base>* uintOther = dynamic_cast<const BigUnsigned<Base>*>(&a)) {
        // Convertimos BigUnsigned en BigInteger y luego en BigRational
        BigInteger<Base> intConverted(*uintOther);
        BigRational<Base> uintAsRational(intConverted, "1");
        return *(new BigRational<Base>(*this * uintAsRational));
    }
    throw std::invalid_argument("Tipo de BigNumber no compatible con multiply()");
}
template <unsigned char Base>
BigNumber<Base>& BigRational<Base>::subtract(const BigNumber<Base>& a) const{
  if (const BigRational<Base>* ratOther = dynamic_cast<const BigRational<Base>*>(&a)) {
    return *(new BigRational<Base>(*this - *ratOther));
} else if (const BigInteger<Base>* intOther = dynamic_cast<const BigInteger<Base>*>(&a)) {
    // Convertimos el BigInteger en una fracción (con denominador 1)
    BigRational<Base> intAsRational(*intOther, "1");
    return *(new BigRational<Base>(*this - intAsRational));
} else if (const BigUnsigned<Base>* uintOther = dynamic_cast<const BigUnsigned<Base>*>(&a)) {
    // Convertimos el BigUnsigned en una fracción (con denominador 1)
    BigInteger<Base> intConverted(*uintOther); // BigUnsigned → BigInteger
    BigRational<Base> uintAsRational(intConverted, "1");
    return *(new BigRational<Base>(*this - uintAsRational));
}
throw std::invalid_argument("Tipo de BigNumber no compatible con add()");
}

template <unsigned char Base>
BigNumber<Base>& BigRational<Base>::add(const BigNumber<Base>& a) const {
    if (const BigRational<Base>* ratOther = dynamic_cast<const BigRational<Base>*>(&a)) {
        return *(new BigRational<Base>(*this + *ratOther));
    } else if (const BigInteger<Base>* intOther = dynamic_cast<const BigInteger<Base>*>(&a)) {
        // Convertimos el BigInteger en una fracción (con denominador 1)
        BigRational<Base> intAsRational(*intOther, "1");
        return *(new BigRational<Base>(*this + intAsRational));
    } else if (const BigUnsigned<Base>* uintOther = dynamic_cast<const BigUnsigned<Base>*>(&a)) {
        // Convertimos el BigUnsigned en una fracción (con denominador 1)
        BigInteger<Base> intConverted(*uintOther); // BigUnsigned → BigInteger
        BigRational<Base> uintAsRational(intConverted, "1");
        return *(new BigRational<Base>(*this + uintAsRational));
    }
    throw std::invalid_argument("Tipo de BigNumber no compatible con add()");
}


//operador BigRational
template <unsigned char Base>
BigRational<Base>::operator BigRational<Base>() const{
  return *this;
}

template <unsigned char Base>
BigRational<Base>::operator BigInteger<Base>() const{
  BigInteger<Base> temp(this->numerador);
  return temp;
}

template <unsigned char Base>
BigRational<Base>::operator BigUnsigned<Base>() const{
  BigUnsigned<Base> temp(this->numerador);
  return temp;
}

template <unsigned char Base>
std::ostream& BigRational<Base>::write(std::ostream& os) const{
  os << this->numerador << "/" << this->denominador;
  return os;
}


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
  a.numerador = BigInteger<Base>(token.c_str());
  temp.erase(0, pos + delimiter.length());
  a.denominador = BigUnsigned<Base>(temp.c_str());
  return is;
}

template <unsigned char Base>
BigRational<Base> operator+(const BigRational<Base>& a, const BigRational<Base>& b){
  BigRational<Base> temp;
  temp.denominador = a.denominador * b.denominador;
  BigInteger<Base> temp1 = BigInteger<Base>(a.numerador) * BigInteger<Base>(b.denominador);
  BigInteger<Base> temp2 = BigInteger<Base>(b.numerador) * BigInteger<Base>(a.denominador);
  temp.numerador = temp1 + temp2;
  return temp;
}

template <unsigned char Base>
BigRational<Base> BigRational<Base>::operator-(const BigRational<Base>& a) const{
  BigRational<Base> temp;
  temp.denominador = this->denominador * a.denominador;
  BigInteger<Base> temp1 = BigInteger<Base>(this->numerador) * BigInteger<Base>(a.denominador);
  BigInteger<Base> temp2 = BigInteger<Base>(a.numerador) * BigInteger<Base>(this->denominador);
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

template <unsigned char Base>
BigRational<Base> BigRational<Base>::operator/(const BigRational<Base>& a) const{
  BigRational<Base> temp;
  temp.numerador = this->numerador * BigInteger<Base>(a.denominador);
  temp.denominador = this->denominador * a.numerador;
  return temp;
}


template <unsigned char Base>
std::istream& BigRational<Base>::read(std::istream& is){
  return is >> *this;
}
