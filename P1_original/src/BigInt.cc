#include "BigInt.h"

BigInteger BigInteger::operator%(const BigInteger& a) const {
  if(a == 0){
    std::cerr << "Division by zero" << std::endl;
    exit(1);
  }
  if(*this < a){
    return *this;
  }
  BigInteger temp = this->num % a.num;
  return temp;
}

BigInteger operator/(const BigInteger& a, const BigInteger& b) {
  if(b == 0){
    std::cerr << "Division by zero" << std::endl;
    exit(1);
  }
  if(a < b){
    return BigInteger(0);
  }
  BigInteger temp = a.num / b.num;
  if(a.IsNegative && !b.IsNegative){
    temp.IsNegative = true;
  } else if(!a.IsNegative && b.IsNegative){
    temp.IsNegative = true;
  } else if(a.IsNegative && b.IsNegative){
    temp.IsNegative = false;
  }
  return temp;
}


BigInteger BigInteger::operator*(const BigInteger& a) const {
  BigUnsigned temp = this->num * a.num;
  if(this->IsNegative && !a.IsNegative){
    BigInteger temp2 = temp;
    temp2.IsNegative = true;
    return temp2;
  } else if(!this->IsNegative && a.IsNegative){
    BigInteger temp2 = temp;
    temp2.IsNegative = true;
    return temp2;
  } else if(this->IsNegative && a.IsNegative){
    return temp;
  } else {
    return temp;
  }
}


BigInteger BigInteger::operator-(const BigInteger& a) const {
  if(this->IsNegative && !a.IsNegative){
    BigInteger temp = a;
    temp.IsNegative = true;
    return *this + temp;
  } else if(!this->IsNegative && a.IsNegative){
    BigInteger temp = a;
    temp.IsNegative = false;
    return *this + temp;
  } else if(this->IsNegative && a.IsNegative){
    BigInteger temp = a;
    temp.IsNegative = false;
    return temp - *this;
  } else {
    if(*this < a){
      BigInteger temp = a - *this;
      temp.IsNegative = true;
      return temp;
    }
    BigUnsigned temp = this->num - a.num;
    return BigInteger(temp);
  } 
}

BigInteger operator+(const BigInteger& a, const BigInteger& b){
  if(a.IsNegative && !b.IsNegative){
    BigInteger temp = b;
    temp.IsNegative = false;
    return b - a;
  } else if(!a.IsNegative && b.IsNegative){
    BigInteger temp = a;
    temp.IsNegative = false;
    return a - b;
  } else if(a.IsNegative && b.IsNegative){
    BigInteger temp = a;
    temp.IsNegative = true;
    return temp + b;
  } else {
    BigUnsigned temp = a.num + b.num;
    return BigInteger(temp);
  }
}

bool operator<(const BigInteger& a, const BigInteger& b){
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

bool BigInteger::operator==(const BigInteger& a) const{
  if(this->num == a.num && this->IsNegative == a.IsNegative){
    return true;
  }
  return false;
}

BigInteger &BigInteger::operator++(){
  if(this->IsNegative){
    this->num = this->num - 1;
  } else {
    this->num = this->num + 1;
  }
  return *this;
}

BigInteger BigInteger::operator++(int){
  BigInteger temp = *this;
  ++*this;
  return temp;
}

BigInteger &BigInteger::operator--(){
  if(this->IsNegative){
    this->num = this->num + 1;
  } else {
    this->num = this->num - 1;
  }
  return *this;
}

BigInteger BigInteger::operator--(int){
  BigInteger temp = *this;
  --*this;
  return temp;
}

BigInteger& BigInteger::operator=(const BigInteger& a){
  this->num = a.num;
  this->IsNegative = a.IsNegative;
  return *this;
}

std::istream& operator>>(std::istream& is, BigInteger& a){
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
  BigUnsigned temp2(temp.c_str());
  a.num = temp2;
  return is;
}


std::ostream& operator<<(std::ostream& os, const BigInteger&a ){
  if(a.IsNegative){
    std::cout << "-";
  }
  std::cout << a.num;
  return os;
}

BigInteger::BigInteger(const BigUnsigned& n){
  this->num = n;
}

BigInteger::BigInteger(int n){
  if(n < 0){
    this->IsNegative = true;
    n = -n;
  } else {
    this->IsNegative = false;
  }
  BigUnsigned temp(n);
  this->num = temp;
}