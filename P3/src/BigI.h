#ifndef BIGINT_H
#define BIGINT_H
#include "BigU.h"
#include "BigNumber.h"
#include "BigR.h"

template <unsigned char Base>
class BigInteger : public BigNumber<Base> { 
  public:
  BigInteger(int n = 0);
  BigInteger(const BigUnsigned<Base>&);
  BigInteger(const char*);

  BigInteger& operator=(const BigInteger&);

  template <unsigned char B>
  friend std::ostream& operator<<(std::ostream&, const BigInteger<B>&);

  template <unsigned char B>
  friend std::istream& operator>>(std::istream&, BigInteger<B>&);

  bool operator==(const BigInteger<Base>&) const;

  template <unsigned char B>
  friend bool operator<(const BigInteger<B>&, const BigInteger<B>&);

  BigInteger<Base>& operator++(); // Pre-incremento
  BigInteger<Base> operator++(int); // Post-incremento
  BigInteger<Base>& operator--(); // Pre-decremento
  BigInteger<Base> operator--(int); // Post-decremento

  template <unsigned char B>
  friend BigInteger<B> operator+(const BigInteger<B>&, const BigInteger<B>&);
  BigInteger<Base> operator-(const BigInteger<Base>&) const;
  BigInteger<Base> operator*(const BigInteger<Base>&) const;

  template <unsigned char B>
  friend BigInteger<B> operator/(const BigInteger<B>&, const BigInteger<B>&);
  BigInteger<Base> operator%(const BigInteger<Base>&) const;

  BigNumber<Base>& add(const BigNumber<Base>&) const override;
  BigNumber<Base>& subtract(const BigNumber<Base>&) const override;
  BigNumber<Base>& multiply(const BigNumber<Base>&) const override;
  BigNumber<Base>& divide(const BigNumber<Base>&) const override;

  operator BigInteger<Base>() const override;
  operator BigRational<Base>() const override;
  operator BigUnsigned<Base>() const override;


  protected:
  std::ostream& write(std::ostream&) const override;
  std::istream& read(std::istream&) override;

  private:
  BigUnsigned<Base> num;
  bool IsNegative = false;
};




template<>
class BigInteger<2>{
  public:
  BigInteger(int n = 0);
  BigInteger(const BigUnsigned<2>&);

  BigInteger& operator=(const BigInteger<2>&);
  friend std::ostream& operator<<(std::ostream&, const BigInteger<2>&);
  friend std::istream& operator>>(std::istream&, BigInteger<2>&);
  bool operator==(const BigInteger<2>&) const;
  void complement_2();
  friend bool operator<(const BigInteger<2>&, const BigInteger<2>&);

  BigInteger<2>& operator++(); // Pre-incremento
  BigInteger<2> operator++(int); // Post-incremento
  BigInteger<2>& operator--(); // Pre-decremento
  BigInteger<2> operator--(int); // Post-decremento

  friend BigInteger<2> operator+(const BigInteger<2>&, const BigInteger<2>&);
  BigInteger<2> operator-(const BigInteger<2>&) const;
  BigInteger<2> operator*(const BigInteger<2>&) const;

  friend BigInteger<2> operator/(const BigInteger<2>&, const BigInteger<2>&);
  BigInteger<2> operator%(const BigInteger<2>&) const;

  private:
  BigUnsigned<2> num;
  bool IsNegative = false;
};

BigInteger<2>::BigInteger(const BigUnsigned<2>& a) {
  // Si el primer bit es 1, interpretamos que el número es negativo en complemento a 2
  if (a.bits[0] == 1) {
      IsNegative = true;
      num = a;  // Convertimos a su valor absoluto (positivo)
  } else {
      num = a;
      IsNegative = false;  // Si el primer bit es 0, es un número positivo
  }
}

BigInteger<2>::BigInteger(int n) {
  if (n < 0) {
      IsNegative = true;
      n = -n;
  } else {
      IsNegative = false;
  }
  num = BigUnsigned<2>(n);
}

// Método para convertir el número a complemento a 2 (si es negativo)
void BigInteger<2>::complement_2() {
  if (IsNegative) {
      num = num.complement_2();  // Convertimos a valor absoluto en complemento a 2
      IsNegative = false;
  } else {
      // Si el número ya es positivo, no necesitamos hacer nada
  }
}

//operador =
BigInteger<2>& BigInteger<2>::operator=(const BigInteger<2>& a){
  if(this != &a){
    num = a.num;
    IsNegative = a.IsNegative;
  }
  return *this;
}

//operador <
bool operator<(const BigInteger<2>& a, const BigInteger<2>& b){
  if(a.IsNegative && !b.IsNegative){
    return true;
  } else if(!a.IsNegative && b.IsNegative){
    return false;
  } else if(a.IsNegative && b.IsNegative){
    if(b.num < a.num){
      return true;
    }
    return false;
  } else {
    if(a.num < b.num){
      return true;
    }
    return false;
  }
}

BigInteger<2> operator+(const BigInteger<2>& a, const BigInteger<2>& b) {
  BigInteger<2> result = a.num + b.num;
  if(a.IsNegative && !b.IsNegative){
    if(a.num < b.num){
      result.IsNegative = false;
      if(result.num.bits[0] == 1){
        result.num.bits.insert(result.num.bits.begin(), false);
      }
    } else {
      result.IsNegative = true;
    }
  } else if(!a.IsNegative && b.IsNegative){
    if(a.num < b.num){
      result.IsNegative = true;
    } else {
      result.IsNegative = false;
      if(result.num.bits[0] == 1){
        result.num.bits.insert(result.num.bits.begin(), false);
      }
    }
  } else if(a.IsNegative && b.IsNegative){
    result.IsNegative = true;
  } else {
    //si el primer bit es 1 se inserta un 0 al principio
    if(result.num.bits[0] == 1){
      result.num.bits.insert(result.num.bits.begin(), false);
    }
    result.IsNegative = false;
  }
  return result;
}

BigInteger<2> BigInteger<2>::operator-(const BigInteger<2> &a) const {
  BigInteger<2> result = this->num + a.num.complement_2();
  if(this->IsNegative && !a.IsNegative){
    result.IsNegative = true;
  } else if(!this->IsNegative && a.IsNegative){
    result.IsNegative = false;
  } else if(this->IsNegative && a.IsNegative){
    if(a.num < this->num){
      result.IsNegative = false;
      if(result.num.bits[0] == 1){
        result.num.bits.insert(result.num.bits.begin(), false);
      }
    } else {
      result.IsNegative = true;
    }
  } else {
    if(this->num < a.num){
      result.IsNegative = true;
    } else {
      if(result.num.bits[0] == 1){
        result.num.bits.insert(result.num.bits.begin(), false);
      }
      result.IsNegative = false;
    }
  }
  return result;

} 

//operador *
BigInteger<2> BigInteger<2>::operator*(const BigInteger<2>& a) const {
  BigUnsigned<2> temp = this->num * a.num;
  if(this->IsNegative && !a.IsNegative){
    BigInteger<2> temp2 = temp;
    temp2.IsNegative = true;
    return temp2;
  } else if(!this->IsNegative && a.IsNegative){
    BigInteger<2> temp2 = temp;
    temp2.IsNegative = true;
    return temp2;
  } else if(this->IsNegative && a.IsNegative){
    return temp;
  } else {
    return temp;
  }
}


//operador de inserción
std::ostream& operator<<(std::ostream& os, const BigInteger<2>& a){
  if(a.IsNegative){
    os << "-";
  }
  os << a.num;
  return os;
}

template <unsigned char Base>
BigInteger<Base> BigInteger<Base>::operator%(const BigInteger<Base>& a) const {
  if(a == 0){
    std::cerr << "Division by zero" << std::endl;
    exit(1);
  }
  if(*this < a){
    return *this;
  }
  BigInteger<Base> temp = this->num % a.num;
  return temp;
}

template <unsigned char Base>
BigInteger<Base> operator/(const BigInteger<Base>& a, const BigInteger<Base>& b) {
  if(b == 0){
    std::cerr << "Division by zero" << std::endl;
    exit(1);
  }
  if(a < b){
    return BigInteger<Base>(0);
  }
  BigInteger<Base> temp = a.num / b.num;
  if(a.IsNegative && !b.IsNegative){
    temp.IsNegative = true;
  } else if(!a.IsNegative && b.IsNegative){
    temp.IsNegative = true;
  } else if(a.IsNegative && b.IsNegative){
    temp.IsNegative = false;
  }
  return temp;
}

template <unsigned char Base>
BigInteger<Base> BigInteger<Base>::operator*(const BigInteger<Base>& a) const {
  BigUnsigned<Base> temp = this->num * a.num;
  if(this->IsNegative && !a.IsNegative){
    BigInteger<Base> temp2 = temp;
    temp2.IsNegative = true;
    return temp2;
  } else if(!this->IsNegative && a.IsNegative){
    BigInteger<Base> temp2 = temp;
    temp2.IsNegative = true;
    return temp2;
  } else if(this->IsNegative && a.IsNegative){
    return temp;
  } else {
    return temp;
  }
}

template <unsigned char Base>
BigInteger<Base> BigInteger<Base>::operator-(const BigInteger<Base>& a) const {
 // Caso: (-A) - (B) = -(A + B)
 if (this->IsNegative && !a.IsNegative) {
  BigInteger<Base> temp = *this;
  temp.IsNegative = false;  // Convertimos a positivo
  BigInteger<Base> result = temp + a;
  result.IsNegative = true; // Negamos el resultado
  return result;
}

// Caso: (A) - (-B) = A + B
if (!this->IsNegative && a.IsNegative) {
  return *this + BigInteger<Base>(a.num);
}

// Caso: (-A) - (-B) = B - A
if (this->IsNegative && a.IsNegative) {
  return BigInteger<Base>(a.num) - BigInteger<Base>(this->num);
}

// Caso: A - B (ambos positivos)
if (*this < a) {
  BigInteger<Base> temp = a - *this;
  temp.IsNegative = true; // Si A < B, el resultado es negativo
  return temp;
}

// Resta normal de positivos
BigUnsigned<Base> temp = this->num - a.num;
return BigInteger<Base>(temp);
}

template <unsigned char Base>
BigInteger<Base> operator+(const BigInteger<Base>& a, const BigInteger<Base>& b){
  if(a.IsNegative && !b.IsNegative){
    BigInteger<Base> temp = b;
    temp.IsNegative = false;
    return b - a;
  } else if(!a.IsNegative && b.IsNegative){
    BigInteger<Base> temp = a;
    temp.IsNegative = false;
    return a - b;
  } else if(a.IsNegative && b.IsNegative){
    BigInteger<Base> temp = a;
    temp.IsNegative = true;
    return temp + b;
  } else {
    BigUnsigned<Base> temp = a.num + b.num;
    return BigInteger<Base>(temp);
  }
}

template <unsigned char Base>
bool operator<(const BigInteger<Base>& a, const BigInteger<Base>& b){
  if(a.IsNegative && !b.IsNegative){
    return true;
  } else if(!a.IsNegative && b.IsNegative){
    return false;
  } else if(a.IsNegative && b.IsNegative){
    if(b.num < a.num){
      return true;
    }
    return false;
  } else {
    if(a.num < b.num){
      return true;
    }
    return false;
  }
}

template <unsigned char Base>
bool BigInteger<Base>::operator==(const BigInteger<Base>& a) const{
  if(this->num == a.num && this->IsNegative == a.IsNegative){
    return true;
  }
  return false;
}

template <unsigned char Base>
BigInteger<Base> &BigInteger<Base>::operator++(){
  if(this->IsNegative){
    this->num = this->num - 1;
  } else {
    this->num = this->num + 1;
  }
  return *this;
}

template <unsigned char Base>
BigInteger<Base> BigInteger<Base>::operator++(int){
  BigInteger temp = *this;
  ++*this;
  return temp;
}

template <unsigned char Base>
BigInteger<Base> &BigInteger<Base>::operator--(){
  if(this->IsNegative){
    this->num = this->num + 1;
  } else {
    this->num = this->num - 1;
  }
  return *this;
}

template <unsigned char Base>
BigInteger<Base> BigInteger<Base>::operator--(int){
  BigInteger temp = *this;
  --*this;
  return temp;
}

template <unsigned char Base>
BigInteger<Base>& BigInteger<Base>::operator=(const BigInteger<Base>& a){
  this->num = a.num;
  this->IsNegative = a.IsNegative;
  return *this;
}

template <unsigned char Base>
std::istream& operator>>(std::istream& is, BigInteger<Base>& a){
  std::string temp;
  is >> temp;
  if(temp[0] == '-'){
    a.IsNegative = true;
    temp = temp.substr(1);
  } else {
    a.IsNegative = false;
  }
  for(int i = 0; i < temp.size(); i++){
    if(!isdigit(temp[i])){
      std::cerr << "Invalid input, only numbers" << std::endl;
      exit(1);
    }
  }
  BigUnsigned<Base> temp2(temp.c_str());
  a.num = temp2;
  return is;
}

template <unsigned char Base>
std::ostream& operator<<(std::ostream& os, const BigInteger<Base>&a ){
  if(a.IsNegative){
    std::cout << "-";
  }
  std::cout << a.num;
  return os;
}

template <unsigned char Base>
BigInteger<Base>::BigInteger(const BigUnsigned<Base>& n){
  this->num = n;
}

template <unsigned char Base>
BigInteger<Base>::BigInteger(int n){
  if(n < 0){
    this->IsNegative = true;
    n = -n;
  } else {
    this->IsNegative = false;
  }
  BigUnsigned<Base> temp(n);
  this->num = temp;
}

template <unsigned char Base>
BigInteger<Base>::BigInteger(const char* a){
  std::string temp(a);
  if(temp[0] == '-'){
    this->IsNegative = true;
    temp = temp.substr(1);
  } else {
    this->IsNegative = false;
  }
  if(Base != 16){
  for(int i = 0; i < temp.size(); i++){
    if(!isdigit(temp[i])){
      std::cerr << "Invalid input" << std::endl;
      exit(1);
    }
  }
  BigUnsigned<Base> temp2(temp.c_str());
  this->num = temp2;
  } else {
    BigUnsigned<Base> temp2(temp.c_str());
    this->num = temp2;
  }
}

//metodo write
template <unsigned char Base>
std::ostream& BigInteger<Base>::write(std::ostream& os) const{
  if(this->IsNegative){
    os << "-";
  }
  os << this->num;
  return os;
}

template <unsigned char Base>
std::istream& BigInteger<Base>::read(std::istream& is){
  return is >> *this;
}

// operator BigInteger<Base>
template <unsigned char Base>
BigInteger<Base>::operator BigInteger<Base>() const{
  return *this;
}

template <unsigned char Base>
BigInteger<Base>::operator BigRational<Base>() const{
  BigInteger<Base> temp1(this->num);
  BigRational<Base> temp2(temp1, 1);
  return temp2;
}

template <unsigned char Base>
BigInteger<Base>::operator BigUnsigned<Base>() const{
  BigUnsigned<Base> temp(this->num);
  return temp;
}

template <unsigned char Base>
BigNumber<Base>& BigInteger<Base>::add(const BigNumber<Base>& a) const {
    if (const BigInteger<Base>* intOther = dynamic_cast<const BigInteger<Base>*>(&a)) {
        return *(new BigInteger<Base>(*this + *intOther));
    } else if (const BigUnsigned<Base>* uintOther = dynamic_cast<const BigUnsigned<Base>*>(&a)) {
        // Convertimos el BigUnsigned a un BigInteger y luego sumamos
        BigInteger<Base> otherInt(*uintOther);  // Construcción segura
        return *(new BigInteger<Base>(*this + otherInt)); // SUMA SEGURA
    } else if (const BigRational<Base>* ratOther = dynamic_cast<const BigRational<Base>*>(&a)) {
        // Convertimos this a BigRational y realizamos la suma
        BigRational<Base> thisAsRational(*this, "1");
        return *(new BigRational<Base>(thisAsRational + *ratOther));
    }
    throw std::invalid_argument("Tipo de BigNumber no compatible con add()");
}

template <unsigned char Base>
BigNumber<Base>& BigInteger<Base>::subtract(const BigNumber<Base>& a) const{
  if (const BigInteger<Base>* intOther = dynamic_cast<const BigInteger<Base>*>(&a)) {
    return *(new BigInteger<Base>(*this - *intOther));
} else if (const BigUnsigned<Base>* uintOther = dynamic_cast<const BigUnsigned<Base>*>(&a)) {
    // Convertimos el BigUnsigned a un BigInteger y luego sumamos
    BigInteger<Base> otherInt(*uintOther);  // Construcción segura
    return *(new BigInteger<Base>(*this - otherInt)); // SUMA SEGURA
} else if (const BigRational<Base>* ratOther = dynamic_cast<const BigRational<Base>*>(&a)) {
    // Convertimos this a BigRational y realizamos la suma
    BigRational<Base> thisAsRational(*this, "1");
    return *(new BigRational<Base>(thisAsRational - *ratOther));
}
throw std::invalid_argument("Tipo de BigNumber no compatible con add()");
}

template <unsigned char Base>
BigNumber<Base>& BigInteger<Base>::multiply(const BigNumber<Base>& a) const{
  if (const BigInteger<Base>* intOther = dynamic_cast<const BigInteger<Base>*>(&a)) {
    return *(new BigInteger<Base>(*this * *intOther));
} else if (const BigUnsigned<Base>* uintOther = dynamic_cast<const BigUnsigned<Base>*>(&a)) {
    // Convertimos el BigUnsigned a un BigInteger y luego sumamos
    BigInteger<Base> otherInt(*uintOther);  // Construcción segura
    return *(new BigInteger<Base>(*this * otherInt)); // SUMA SEGURA
} else if (const BigRational<Base>* ratOther = dynamic_cast<const BigRational<Base>*>(&a)) {
    // Convertimos this a BigRational y realizamos la suma
    BigRational<Base> thisAsRational(*this, "1");
    return *(new BigRational<Base>(thisAsRational * *ratOther));
}
throw std::invalid_argument("Tipo de BigNumber no compatible con add()");
}

template <unsigned char Base>
BigNumber<Base>& BigInteger<Base>::divide(const BigNumber<Base>& a) const{
  if (const BigInteger<Base>* intOther = dynamic_cast<const BigInteger<Base>*>(&a)) {
    return *(new BigInteger<Base>(*this / *intOther));
} else if (const BigUnsigned<Base>* uintOther = dynamic_cast<const BigUnsigned<Base>*>(&a)) {
    // Convertimos el BigUnsigned a un BigInteger y luego sumamos
    BigInteger<Base> otherInt(*uintOther);  // Construcción segura
    return *(new BigInteger<Base>(*this / otherInt)); // SUMA SEGURA
} else if (const BigRational<Base>* ratOther = dynamic_cast<const BigRational<Base>*>(&a)) {
    // Convertimos this a BigRational y realizamos la suma
    BigRational<Base> thisAsRational(*this, "1");
    return *(new BigRational<Base>(thisAsRational / *ratOther));
}
throw std::invalid_argument("Tipo de BigNumber no compatible con add()");
}


#endif