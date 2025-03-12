#pragma once

#ifndef BIG_UNSIGNED
#define BIG_UNSIGNED


#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>

#include "BigNumber.h"

template <unsigned char Base>
class BigUnsigned : public BigNumber<Base> {
  public:
  BigUnsigned(unsigned n = 0);
  BigUnsigned(const char*);
  BigUnsigned(const BigUnsigned<Base>&);

  BigUnsigned& operator=(const BigUnsigned<Base>&);
  template<unsigned char B>
  friend std::ostream& operator<<(std::ostream&, const BigUnsigned<B>&);
  template<unsigned char B>
  friend std::istream& operator>>(std::istream&, BigUnsigned<B>&);
  bool operator==(const BigUnsigned<Base>&) const;

  template<unsigned char B>
  friend bool operator<(const BigUnsigned<B>&, const BigUnsigned<B>&);

  template<unsigned char B>
  friend bool operator>= (const BigUnsigned<B>&, const BigUnsigned<B>&);

  BigUnsigned<Base>& operator++(); // Pre-incremento
  BigUnsigned<Base> operator++(int); // Post-incremento
  BigUnsigned<Base>& operator--(); // Pre-decremento
  BigUnsigned<Base> operator--(int); // Post-decremento

  template<unsigned char B>
  friend BigUnsigned<B> operator+(const BigUnsigned<B>&, const BigUnsigned<B>&);
  BigUnsigned<Base> operator-(const BigUnsigned<Base>&) const;
  BigUnsigned<Base> operator*(const BigUnsigned<Base>&) const;

  template<unsigned char B>
  friend BigUnsigned<B> operator/(const BigUnsigned<B>&, const BigUnsigned<B>&);
  BigUnsigned<Base> operator%(const BigUnsigned<Base>&) const;

  BigNumber<Base>& add(const BigNumber<Base>&) const override;
  BigNumber<Base>& subtract(const BigNumber<Base>&) const override;
  BigNumber<Base>& multiply(const BigNumber<Base>&) const override;
  BigNumber<Base>& divide(const BigNumber<Base>&) const override;

  operator BigInteger<Base>() const override;
  operator BigRational<Base>() const override;
  operator BigUnsigned<Base>() const override;

  protected:
  std::ostream& write(std::ostream&) const override;
  //std::istream& read(std::istream&) override;

  
  private:
  std::vector<unsigned char> digits;

};

template <unsigned char Base>
BigNumber<Base>& BigUnsigned<Base>::divide(const BigNumber<Base>& a) const{
  BigUnsigned<Base> temp = dynamic_cast<const BigUnsigned<Base>&>(a);
  BigUnsigned<Base> *result = new BigUnsigned<Base>(*this / temp);
  return *result;
}

template <unsigned char Base>
BigNumber<Base>& BigUnsigned<Base>::multiply(const BigNumber<Base>& a) const{
  BigUnsigned<Base> temp = dynamic_cast<const BigUnsigned<Base>&>(a);
  BigUnsigned<Base> *result = new BigUnsigned<Base>(*this * temp);
  return *result;
}

template <unsigned char Base>
BigNumber<Base>& BigUnsigned<Base>::subtract(const BigNumber<Base>& a) const{
  BigUnsigned<Base> temp = dynamic_cast<const BigUnsigned<Base>&>(a);
  BigUnsigned<Base> *result = new BigUnsigned<Base>(*this - temp);
  return *result;
}

template <unsigned char Base>
BigNumber<Base>& BigUnsigned<Base>::add(const BigNumber<Base>& a) const{
  BigUnsigned<Base> temp = dynamic_cast<const BigUnsigned<Base>&>(a);
  BigUnsigned<Base> *result = new BigUnsigned<Base>(*this + temp);
  return *result;
}

//write
template <unsigned char Base>
std::ostream& BigUnsigned<Base>::write(std::ostream& os) const{
  for(int i = 0; i < digits.size(); i++){
    os << digits[i];
  }
  return os;
}

template <unsigned char Base>
BigUnsigned<Base>::operator BigInteger<Base>() const{
  BigInteger<Base> temp(*this);
  return temp;
}

template <unsigned char Base>
BigUnsigned<Base>::operator BigRational<Base>() const{
  BigInteger<Base> temp(*this);
  BigRational<Base> temp2(temp);
  return temp2;  
}

template <unsigned char Base>
BigUnsigned<Base>::operator BigUnsigned<Base>() const{
  return *this;
}



template <unsigned char Base>
BigUnsigned<Base> BigUnsigned<Base>::operator%(const BigUnsigned<Base>& a) const{
  BigUnsigned<Base> lhs = *this;
  BigUnsigned<Base> rhs = a;
  BigUnsigned<Base> temp;
  temp.digits.erase(temp.digits.begin());
  int i = 0;
  while(i < lhs.digits.size()){
    temp.digits.push_back(lhs.digits[i]);
    if(temp < rhs){
      i++;
    } else {
      int count = 0;
      while(temp >= rhs){
        temp = temp - rhs;
        count++;
      }
      i++;
    }
  }
  return temp;
}

template <unsigned char Base>
BigUnsigned<Base>operator/(const BigUnsigned<Base>& a, const BigUnsigned<Base>& b){
  BigUnsigned<Base> lhs = a;
  BigUnsigned<Base> rhs = b;
  BigUnsigned<Base> temp;
  temp.digits.erase(temp.digits.begin());
  BigUnsigned<Base> temp2;
  temp2.digits.erase(temp2.digits.begin());
  int i = 0;
  while(i < lhs.digits.size()){
    temp2.digits.push_back(lhs.digits[i]);
    if(temp2 < rhs){
      if(temp.digits.size() > 0){
        unsigned char temp_c = '0';
        temp.digits.push_back(temp_c);
      }
      i++;
    } else {
      int count = 0;
      while(temp2 >= rhs){
        temp2 = temp2 - rhs;
        count++;
      }
      unsigned char temp_c = count + '0';
      temp.digits.push_back(temp_c);
      i++;
    }
  }
  return temp;
}

template <unsigned char Base>
BigUnsigned<Base> BigUnsigned<Base>::operator*(const BigUnsigned<Base>&a) const{
  BigUnsigned<Base> lhs = *this;
  BigUnsigned<Base> rhs = a;
  BigUnsigned<Base> temp;
  temp.digits.erase(temp.digits.begin());
  int carry = 0;
  int i = lhs.digits.size() - 1;
  int j = rhs.digits.size() - 1;
  int k = 0;
  while(i >= 0){
    BigUnsigned<Base> temp2;
    temp2.digits.erase(temp2.digits.begin());
    for(int l = 0; l < k; l++){
      unsigned char temp_c = '0';
      temp2.digits.push_back(temp_c);
    }
    carry = 0;
    j = rhs.digits.size() - 1;
    while(j >= 0){
      int temp_i = lhs.digits[i] - '0';
      int temp_j = rhs.digits[j] - '0';
      int temp_x = temp_i * temp_j + carry;
      if(temp_x > 9){
        carry = temp_x / 10;
        temp_x = temp_x % 10;
      } else {
        carry = 0;
      }
      unsigned char temp_c = temp_x + '0';
      temp2.digits.insert(temp2.digits.begin(), temp_c);
      j--;
    }
    if(carry > 0){
      unsigned char temp_c = carry + '0';
      temp2.digits.insert(temp2.digits.begin(), temp_c);
    }
    temp = temp + temp2;
    i--;
    k++;
  }
  return temp;

}

template <unsigned char Base>
BigUnsigned<Base>BigUnsigned<Base>::operator-(const BigUnsigned<Base>& a) const{
  BigUnsigned<Base> lhs = *this;
  BigUnsigned<Base> rhs = a;
  BigUnsigned<Base> temp;
  if(lhs < rhs){
    std::cerr << "Invalid operation < 0 in unsigned" << std::endl;
    exit(1);
  }
  temp.digits.erase(temp.digits.begin());
  int carry = 0;
  int i = lhs.digits.size() - 1;
  int j = rhs.digits.size() - 1;
  while(i >= 0 && j >= 0){
    int temp_i = lhs.digits[i] - '0';
    int temp_j = rhs.digits[j] - '0';
    int temp_x = temp_i - temp_j - carry;
    if(temp_x < 0){
      carry = 1;
      temp_x = 10 + temp_x;
    } else {
      carry = 0;
    }
    unsigned char temp_c = temp_x + '0';
    temp.digits.insert(temp.digits.begin(), temp_c);
    i--;
    j--;
  }
  while(i >= 0){
    int temp_i = lhs.digits[i] - '0';
    int temp_x = temp_i - carry;
    if(temp_x < 0){
      carry = 1;
      temp_x = 10 + temp_x;
    } else {
      carry = 0;
    }
    unsigned char temp_c = temp_x + '0';
    temp.digits.insert(temp.digits.begin(), temp_c);
    i--;
  }
  while(j >= 0){
    int temp_j = rhs.digits[j] - '0';
    int temp_x = temp_j - carry;
    if(temp_x < 0){
      carry = 1;
      temp_x = 10 + temp_x;
    } else {
      carry = 0;
    }
    unsigned char temp_c = temp_x + '0';
    temp.digits.insert(temp.digits.begin(), temp_c);
    j--;
  }
  //eliminar ceros a la izquierda
  while(temp.digits.size() > 1 && temp.digits[0] == '0'){
    temp.digits.erase(temp.digits.begin());
  }
  return temp;
}

template <unsigned char Base>
BigUnsigned<Base> operator+(const BigUnsigned<Base>& a, const BigUnsigned<Base>& b){
  BigUnsigned<Base> temp;
  temp.digits.erase(temp.digits.begin());
  int carry = 0;
  int i = a.digits.size() - 1;
  int j = b.digits.size() - 1;
  while(i >= 0 && j >= 0){
    int temp_i = a.digits[i] - '0';
    int temp_j = b.digits[j] - '0';
    int temp_x = temp_i + temp_j + carry;
    if(temp_x > 9){
      carry = 1;
      temp_x = temp_x % 10;
    } else {
      carry = 0;
    }
    unsigned char temp_c = temp_x + '0';
    temp.digits.insert(temp.digits.begin(), temp_c);
    i--;
    j--;
  }
  while(i >= 0){
    int temp_i = a.digits[i] - '0';
    int temp_x = temp_i + carry;
    if(temp_x > 9){
      carry = 1;
      temp_x = temp_x % 10;
    } else {
      carry = 0;
    }
    unsigned char temp_c = temp_x + '0';
    temp.digits.insert(temp.digits.begin(), temp_c);
    i--;
  }
  while(j >= 0){
    int temp_j = b.digits[j] - '0';
    int temp_x = temp_j + carry;
    if(temp_x > 9){
      carry = 1;
      temp_x = temp_x % 10;
    } else {
      carry = 0;
    }
    unsigned char temp_c = temp_x + '0';
    temp.digits.insert(temp.digits.begin(), temp_c);
    j--;
  }
  if(carry == 1){
    unsigned char temp_c = '1';
    temp.digits.insert(temp.digits.begin(), temp_c);
  }
  return temp; 
}

template <unsigned char Base>
BigUnsigned<Base>& BigUnsigned<Base>::operator++(){
  int carry = 1;
  for(int i = digits.size() - 1; i >= 0; i--){
    int temp = digits[i] - '0' + carry;
    if(temp > 9){
      carry = 1;
      temp = temp % 10;
    } else {
      carry = 0;
    }
    digits[i] = temp + '0';
  }
  if(carry == 1){
    unsigned char temp = '1';
    digits.insert(digits.begin(), temp);
  }
  return *this;
}

template <unsigned char Base>
BigUnsigned<Base>BigUnsigned<Base>::operator++(int){
  BigUnsigned<Base> temp = *this;
  ++(*this);
  return temp;
}

template <unsigned char Base>
BigUnsigned<Base>& BigUnsigned<Base>::operator--(){
  int carry = 1;
  for(int i = digits.size() - 1; i >= 0; i--){
    int temp = digits[i] - '0' - carry;
    if(temp < 0){
      carry = 1;
      temp = 10 + temp;
    } else {
      carry = 0;
    }
    digits[i] = temp + '0';
  }
  //eliminar ceros a la izquierda
  while(digits.size() > 1 && digits[0] == '0'){
    digits.erase(digits.begin());
  }
  if(carry == 1){
    std::cerr << "Invalid operation < 0 in unsigned" << std::endl;
    exit(1);
  }
  return *this;
}

template <unsigned char Base>
BigUnsigned<Base> BigUnsigned<Base>::operator--(int){
  BigUnsigned<Base> temp = *this;
  --(*this);
  return temp;
}

template <unsigned char Base>
std::ostream& operator<<(std::ostream& os, const BigUnsigned<Base>& num) {
  if (Base == 16) {
    BigUnsigned<Base> zero;
    BigUnsigned<Base> temp = num;
    BigUnsigned<Base> mod;
    BigUnsigned<Base> sixteen(16);
    std::string hexStr;  // Almacena los dígitos en orden correcto

    while (zero < temp) {  // Usamos el operador < sobrecargado
      mod = temp % sixteen;

      // DEPURACIÓN: Ver qué valores se están obteniendo
      
      int digitValue = 0;
      for (int i = 0; i < mod.digits.size(); i++) {
        // Convertimos el carácter a su valor numérico (por ejemplo, '0' a 0, '1' a 1, etc.)
        digitValue = digitValue * 10 + (mod.digits[i] - '0');
      }  // Convertimos el primer carácter a su valor numérico

      // DEPURACIÓN: Ver qué valores se están obteniendo

      if (digitValue >= 0 && digitValue <= 9) {
        hexStr += static_cast<char>(digitValue + '0');  // Dígitos 0-9
      } else if (digitValue >= 10 && digitValue <= 15) {
        hexStr += static_cast<char>(digitValue - 10 + 'A');  // Letras A-F
      } else {
        std::cerr << "ERROR: valor inesperado en digit = " << digitValue << std::endl;
        return os;  // Evita imprimir caracteres no válidos
      }

      temp = temp / sixteen;
    }

    std::reverse(hexStr.begin(), hexStr.end());  // Invertimos el orden de los caracteres
    os << hexStr;
  } else if(Base == 8){
    BigUnsigned<Base> zero;
    BigUnsigned<Base> temp = num;
    BigUnsigned<Base> mod;
    BigUnsigned<Base> eight(8);
    std::string octStr;  // Almacena los dígitos en orden correcto

    while (zero < temp) {  // Usamos el operador < sobrecargado
      mod = temp % eight;

      // Convertimos el dígito a su valor numérico
      int digitValue = 0;
      for (int i = 0; i < mod.digits.size(); i++) {
        digitValue = digitValue * 10 + (mod.digits[i] - '0');
      }

      // Añadimos el valor al string octStr
      if (digitValue >= 0 && digitValue <= 7) {
        octStr += static_cast<char>(digitValue + '0');  // Dígitos 0-7 para octal
      } else {
        std::cerr << "ERROR: valor inesperado en digit = " << digitValue << std::endl;
        return os;  // Evita imprimir caracteres no válidos
      }

      temp = temp / eight;
    }

    std::reverse(octStr.begin(), octStr.end());  // Invertimos el orden de los caracteres
    os << octStr;



  } else {
    for (int i = 0; i < num.digits.size(); i++) {
      os << static_cast<char>(num.digits[i]);
    }
  }
  return os;
}


template <unsigned char Base>
std::istream& operator>>(std::istream& is, BigUnsigned<Base>& num){
  std::string temp;
  is >> temp;
  for (int i = 0; i < temp.size(); i++){
    if(!isdigit(temp[i])){
      std::cerr << "Invalid input" << std::endl;
      exit(1);
    }
  }
  num = BigUnsigned<Base>(temp.c_str());
  return is;
}

template <unsigned char Base>
bool BigUnsigned<Base>::operator==(const BigUnsigned<Base>& other) const{
  if(digits.size() != other.digits.size()){
    return false;
  }
  for(int i = 0; i < digits.size(); i++){
    if(digits[i] != other.digits[i]){
      return false;
    }
  }
  return true;
}

template <unsigned char Base>
bool operator<(const BigUnsigned<Base>& a, const BigUnsigned<Base>& b){
  if(a.digits.size() < b.digits.size()){
    return true;
  } else if(a.digits.size() > b.digits.size()){
    return false;
  } else {
    for(int i = 0; i < a.digits.size(); i++){
      if(a.digits[i] < b.digits[i]){
        return true;
      } else if(a.digits[i] > b.digits[i]){
        return false;
      }
    }
  }
  return false;
}

template <unsigned char Base>
bool operator>=(const BigUnsigned<Base>& a, const BigUnsigned<Base>& b){
  return !(a < b);
}

template <unsigned char Base>
BigUnsigned<Base>::BigUnsigned(unsigned n){
  if(n <= 9){
    unsigned char temp = n + '0';
    digits.push_back(temp);
  } else {
    unsigned int temp_i = n % 10;
    unsigned char temp = temp_i + '0';
    digits.insert(digits.begin(), temp);
    n = n / 10;
    while(n > 0){
      temp_i = n % 10;
      temp = temp_i + '0';
      digits.insert(digits.begin(), temp);
      n = n / 10;
    }
  }
}

template <unsigned char Base>
BigUnsigned<Base>::BigUnsigned(const char* a) {
    // Limpiar cualquier dato anterior en digits
    digits.clear();
    if(Base == 8){
      while (*a != '\0') {
          unsigned char c = *a;
          unsigned char digitValue = 0;

          // Convertir el carácter octal a su valor decimal
          if (isdigit(c)) {
              digitValue = c - '0';  // '0' a '7' -> 0 a 7
          } else {
              std::cerr << "Invalid character in octal number: " << c << std::endl;
              exit(1);  // Si encontramos un carácter no válido en octal
          }

          // Procesar el valor octal y almacenarlo en el vector digits
          unsigned char carry = digitValue;  // El acarreo es inicialmente el valor del dígito

          // Iteramos sobre los dígitos existentes y los multiplicamos por 8
          size_t digitsSize = digits.size();
          for (size_t j = 0; j < digitsSize; ++j) {
              unsigned char currentDigit = digits[digits.size() - j - 1] - '0';  // Convertir el char a valor numérico
              unsigned char result = currentDigit * 8 + carry;  // Multiplicamos por 8 y sumamos el acarreo
              digits[digits.size() - j - 1] = (result % 10) + '0';  // El dígito actual
              carry = result / 10;  // El acarreo será el valor que excede el valor de la base 10
          }

          // Si hay acarreo, insertamos al principio
          while (carry > 0) {
              digits.insert(digits.begin(), (carry % 10) + '0');
              carry /= 10;
          }

          ++a;  // Avanzamos al siguiente carácter
      }
    } else if (Base == 16) {
        // Convertir el número hexadecimal a decimal manualmente, sin usar long long
        for (int i = 0; a[i] != '\0'; ++i) {
            unsigned char c = a[i];
            unsigned char digitValue = 0;

            // Convertir el caracter hexadecimal a su valor decimal
            if (isdigit(c)) {
                digitValue = c - '0';  // '0' a '9' -> 0 a 9
            } else if (isupper(c)) {
                digitValue = c - 'A' + 10;  // 'A' a 'F' -> 10 a 15
            } else if (islower(c)) {
                digitValue = c - 'a' + 10;  // 'a' a 'f' -> 10 a 15
            }

            // Procesar el valor hexadecimal y almacenarlo en el vector digits
            unsigned char carry = digitValue;  // El acarreo es inicialmente el valor del dígito

            // Iteramos sobre los dígitos existentes y los multiplicamos por 16
            size_t digitsSize = digits.size();
            for (size_t j = 0; j < digitsSize; ++j) {
                unsigned char currentDigit = digits[digits.size() - j - 1] - '0';  // Convertir el char a valor numérico
                unsigned char result = currentDigit * 16 + carry;  // Multiplicamos por 16 y sumamos el acarreo
                digits[digits.size() - j - 1] = (result % 10) + '0';  // El dígito actual
                carry = result / 10;  // El acarreo será el valor que excede el valor de la base 10
            }

            // Si hay acarreo, insertamos al principio
            while (carry > 0) {
                digits.insert(digits.begin(), (carry % 10) + '0');
                carry /= 10;
            }
        }
    } else {
        // Si el valor es decimal, simplemente lo almacenamos directamente
        while (*a != '\0') {
            if (isdigit(*a)) {
                digits.push_back(*a);  // Si es un dígito decimal, lo añadimos directamente
            } else {
                std::cerr << "Invalid input" << std::endl;
                exit(1);
            }
            a++;  // Avanzamos al siguiente caracter
        }
    }
}


template <unsigned char Base>
BigUnsigned<Base>::BigUnsigned(const BigUnsigned<Base>& other){
  digits = other.digits;
}

template <unsigned char Base>
BigUnsigned<Base>& BigUnsigned<Base>::operator=(const BigUnsigned<Base>& other){
  if(this != &other){
    digits = other.digits;
  }
  return *this;
}

template<>
class BigUnsigned<2>{
  public:
  BigUnsigned(unsigned n = 0);
  BigUnsigned(const char*);
  BigUnsigned(const BigUnsigned<2>&);

  BigUnsigned& operator=(const BigUnsigned<2>&);
  friend std::ostream& operator<<(std::ostream&, const BigUnsigned<2>&);
  friend std::istream& operator>>(std::istream&, BigUnsigned<2>&);
  bool operator==(const BigUnsigned<2>&) const;

  friend bool operator<(const BigUnsigned<2>&, const BigUnsigned<2>&);

  friend bool operator>= (const BigUnsigned<2>&, const BigUnsigned<2>&);
  friend bool operator<= (const BigUnsigned<2>&, const BigUnsigned<2>&);

  BigUnsigned<2> complement_2() const;

  BigUnsigned<2>& operator++(); // Pre-incremento
  BigUnsigned<2> operator++(int); // Post-incremento
  BigUnsigned<2>& operator--(); // Pre-decremento
  BigUnsigned<2> operator--(int); // Post-decremento

  friend BigUnsigned<2> operator+(const BigUnsigned<2>&, const BigUnsigned<2>&);
  BigUnsigned<2> operator-(const BigUnsigned<2>&) const;
  BigUnsigned<2> operator*(const BigUnsigned<2>&) const;

  friend BigUnsigned<2> operator/(const BigUnsigned<2>&, const BigUnsigned<2>&);
  BigUnsigned<2> operator%(const BigUnsigned<2>&) const;
  std::vector<bool> bits;

};

BigUnsigned<2> BigUnsigned<2>::complement_2() const {
  BigUnsigned<2> result = *this;  
  // Invertir todos los bits
  for (size_t i = 0; i < result.bits.size(); ++i) {
      result.bits[i] = ~result.bits[i];
  }
  
  // Sumar 1 al resultado
  bool carry = true;  // Empezamos con el "1" a sumar
  for (size_t i = 0; i < result.bits.size() && carry; ++i) {
      if (result.bits[i] == 0) {
          result.bits[i] = 1;
          carry = false;
      } else {
          result.bits[i] = 0;
      }
  }
  
  return result;
}

std::ostream& operator<<(std::ostream& os, const BigUnsigned<2>& num){
  for(int i = 0; i < num.bits.size(); i++){
    if(num.bits[i]){
      os << '1';
    } else {
      os << '0';
    }
  }
  return os;
}


BigUnsigned<2>::BigUnsigned(unsigned n){
  if(n == 0){
    bits.push_back(false);
  } else {
    while(n > 0){
      if(n % 2 == 0){
        bits.push_back(false);
      } else {
        bits.push_back(true);
      }
      n = n / 2;
    }
  }
}

BigUnsigned<2>::BigUnsigned(const char* a){
  while(*a != '\0'){
    if(*a == '0'){
      bits.push_back(false);
    } else if(*a == '1'){
      bits.push_back(true);
    } else {
      std::cerr << "Invalid input" << std::endl;
      exit(1);
    }
    a++;
  }
}

BigUnsigned<2>::BigUnsigned(const BigUnsigned<2>& other){
  bits = other.bits;
}

BigUnsigned<2>& BigUnsigned<2>::operator=(const BigUnsigned<2>& other){
  if(this != &other){
    bits = other.bits;
  }
  return *this;
}

std::istream& operator>>(std::istream& is, BigUnsigned<2>& num){
  std::string temp;
  is >> temp;
  for (int i = 0; i < temp.size(); i++){
    if(temp[i] != '0' && temp[i] != '1'){
      std::cerr << "Invalid input, only binary numbers" << std::endl;
      exit(1);
    }
  }
  num = BigUnsigned<2>(temp.c_str());
  return is;
}


bool BigUnsigned<2>::operator==(const BigUnsigned<2>& other) const{
  if(bits.size() != other.bits.size()){
    return false;
  }
  for(int i = 0; i < bits.size(); i++){
    if(bits[i] != other.bits[i]){
      return false;
    }
  }
  return true;
}

bool operator<(const BigUnsigned<2>& a, const BigUnsigned<2>& b){
  if(a.bits.size() < b.bits.size()){
    return true;
  } else if(a.bits.size() > b.bits.size()){
    return false;
  } else {
    for(int i = 0; i < a.bits.size(); i++){
      if(a.bits[i] < b.bits[i]){
        return true;
      } else if(a.bits[i] > b.bits[i]){
        return false;
      }
    }
  }
  return false;
}

bool operator>=(const BigUnsigned<2>& a, const BigUnsigned<2>& b){
  return !(a < b);
}

bool operator<=(const BigUnsigned<2>& a, const BigUnsigned<2>& b){
  return a < b || a == b;
}



BigUnsigned<2> operator+(const BigUnsigned<2>& a, const BigUnsigned<2>& b){
  BigUnsigned<2> temp;
  BigUnsigned<2> op1;
  BigUnsigned<2> op2;
  op1.bits = a.bits;
  op2.bits = b.bits;
  temp.bits.clear();
  bool carry = false;

  size_t maxSize = std::max(a.bits.size(), b.bits.size());
  if(a.bits.size() < b.bits.size()){
    for(size_t i = 0; i < b.bits.size() - a.bits.size(); i++){
      op1.bits.insert(op1.bits.begin(), false);
    }
  } else if(b.bits.size() < a.bits.size()){
    for(size_t i = 0; i < a.bits.size() - b.bits.size(); i++){
      op2.bits.insert(op2.bits.begin(), false);
    }
  }
  for(size_t i = maxSize; i > 0; i--){
    bool bit1 = op1.bits[i - 1];
    bool bit2 = op2.bits[i - 1];
    bool sum = bit1 ^ bit2 ^ carry;
    carry = (bit1 && bit2) || (bit1 && carry) || (bit2 && carry);
    temp.bits.insert(temp.bits.begin(), sum);
  }
  if(carry){
    temp.bits.insert(temp.bits.begin(), true);
  }

  while (temp.bits.size() > 1 && temp.bits[0] == false) {
    temp.bits.erase(temp.bits.begin());
  }
  return temp;
}

BigUnsigned<2> BigUnsigned<2>::operator-(const BigUnsigned<2>& a) const{
  BigUnsigned<2> temp;
  BigUnsigned<2> op1 = *this; 
  BigUnsigned<2> op2 = a;     
  temp.bits.clear();
  bool borrow = false;

  size_t maxSize = std::max(op1.bits.size(), op2.bits.size());

  if (op1.bits.size() < maxSize) {
      op1.bits.insert(op1.bits.begin(), maxSize - op1.bits.size(), false);
  }
  if (op2.bits.size() < maxSize) {
      op2.bits.insert(op2.bits.begin(), maxSize - op2.bits.size(), false);
  }

  for (size_t i = maxSize; i > 0; i--) {
      bool bit1 = op1.bits[i - 1];
      bool bit2 = op2.bits[i - 1];
      bool result = bit1 ^ bit2 ^ borrow;
      borrow = (!bit1 && bit2) || (!bit1 && borrow) || (bit2 && borrow);
      temp.bits.insert(temp.bits.begin(), result);
  }

  // Eliminar ceros innecesarios al inicio
  while (temp.bits.size() > 1 && temp.bits[0] == false) {
      temp.bits.erase(temp.bits.begin());
  }

  return temp;
}

BigUnsigned<2> BigUnsigned<2>::operator*(const BigUnsigned<2>& a) const {
  BigUnsigned<2> temp;  // Resultado
  temp.bits = {0};       // Inicializamos en 0

  BigUnsigned<2> op1 = *this; // Multiplicando
  BigUnsigned<2> op2 = a;     // Multiplicador

  // Manejo de ceros iniciales en ambos operandos
  while (op1.bits.size() > 1 && op1.bits[0] == 0) {
      op1.bits.erase(op1.bits.begin());
  }
  while (op2.bits.size() > 1 && op2.bits[0] == 0) {
      op2.bits.erase(op2.bits.begin());
  }

  size_t shift = 0; // Desplazamiento de bits (como en el algoritmo clásico)
  
  // Multiplicación bit a bit (método tradicional de multiplicación binaria)
  for (size_t i = op2.bits.size(); i > 0; i--) {
      if (op2.bits[i - 1] == 1) {
          // Desplazar y sumar (equivalente a la suma de parciales en multiplicación binaria)
          BigUnsigned<2> partial = op1;
          partial.bits.insert(partial.bits.end(), shift, false); // Desplazamiento a la izquierda
          temp = temp + partial; // Suma parcial
      }
      shift++;
  }

  return temp;
}


BigUnsigned<2> operator/(const BigUnsigned<2>& dividee, const BigUnsigned<2>& divisor) {
  if (divisor.bits.empty() || (divisor.bits.size() == 1 && divisor.bits[0] == 0)) {
      throw std::runtime_error("División por cero no permitida.");
  }

  BigUnsigned<2> quotient;  // Cociente
  BigUnsigned<2> remainder = dividee;  // Inicialmente igual a dividee

  // Si el divisor es mayor que el dividendo, el cociente es 0
  if (!(remainder >= divisor)) {
      return BigUnsigned<2>();  // Retorna 0
  }

  BigUnsigned<2> n0 = divisor;  // Inicializamos n0 (el divisor)
  BigUnsigned<2> m0("1");  // Inicializamos m0 (el factor de multiplicación)

  // Encontrar el primer múltiplo de divisor que sea menor o igual a remainder
  while ((n0 + n0) <= remainder) {
      n0 = n0 + n0;  // Doblamos el divisor
      m0 = m0 + m0;  // Doblamos el cociente
  }

  // Ahora comenzamos a restar múltiplos de divisor a remainder
  while (remainder >= divisor) {
      while (remainder >= n0) {
          remainder = remainder - n0;  // Restamos el múltiplo de divisor
          quotient = quotient + m0;  // Sumamos al cociente
      }

      // Reducimos n0 a la mitad y m0 a la mitad
      n0 = n0 - divisor;  // Reducimos el múltiplo de divisor
      m0 = m0 - BigUnsigned<2>("1");  // Reducimos el cociente
  }

  return quotient;  // Retornamos el cociente
}

BigUnsigned<2> BigUnsigned<2>::operator%(const BigUnsigned<2>& divisor) const {
  if (divisor.bits.empty() || (divisor.bits.size() == 1 && divisor.bits[0] == 0)) {
      throw std::runtime_error("División por cero no permitida.");
  }

  BigUnsigned<2> remainder = *this;  // Inicialmente igual a dividee

  // Si el divisor es mayor que el dividendo, el residuo es el dividendo
  if (!(remainder >= divisor)) {
      return remainder;  // Retornamos el dividendo
  }

  BigUnsigned<2> n0 = divisor;  // Inicializamos n0 (el divisor)

  // Encontrar el primer múltiplo de divisor que sea menor o igual a remainder
  while ((n0 + n0) <= remainder) {
      n0 = n0 + n0;  // Doblamos el divisor
  }

  // Ahora comenzamos a restar múltiplos de divisor a remainder
  while (remainder >= divisor) {
      while (remainder >= n0) {
          remainder = remainder - n0;  // Restamos el múltiplo de divisor
      }

      // Reducimos n0 a la mitad
      n0 = n0 - divisor;  // Reducimos el múltiplo de divisor
  }

  return remainder;  // Retornamos el residuo
}

BigUnsigned<2>& BigUnsigned<2>::operator++(){
  bool carry = true;
  for(int i = bits.size() - 1; i >= 0; i--){
    bits[i] = bits[i] ^ carry;
    carry = bits[i] == 0 && carry;
    if(!carry){
      break;
    }
  }
  if(carry){
    bits.insert(bits.begin(), true);
  }
  return *this;
}

BigUnsigned<2> BigUnsigned<2>::operator++(int){
  BigUnsigned<2> temp = *this;
  ++(*this);
  return temp;
}

BigUnsigned<2>& BigUnsigned<2>::operator--(){
  bool borrow = true;
  for(int i = bits.size() - 1; i >= 0; i--){
    bits[i] = bits[i] ^ borrow;
    borrow = bits[i] == 1 && borrow;
    if(!borrow){
      break;
    }
  }
  if(borrow){
    std::cerr << "Invalid operation < 0 in unsigned" << std::endl;
    exit(1);
  }
  while(bits.size() > 1 && bits[0] == false){
    bits.erase(bits.begin());
  }
  return *this;
}

BigUnsigned<2> BigUnsigned<2>::operator--(int){
  BigUnsigned<2> temp = *this;
  --(*this);
  return temp;
}

#endif