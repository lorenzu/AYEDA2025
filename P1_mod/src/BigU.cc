
#include "BigU.h"

BigUnsigned BigUnsigned::operator%(const BigUnsigned& a) const{
  BigUnsigned lhs = *this;
  BigUnsigned rhs = a;
  BigUnsigned temp;
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

BigUnsigned operator/(const BigUnsigned& a, const BigUnsigned& b){
  BigUnsigned lhs = a;
  BigUnsigned rhs = b;
  BigUnsigned temp;
  temp.digits.erase(temp.digits.begin());
  BigUnsigned temp2;
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


BigUnsigned BigUnsigned::operator*(const BigUnsigned&a) const{
  BigUnsigned lhs = *this;
  BigUnsigned rhs = a;
  BigUnsigned temp;
  temp.digits.erase(temp.digits.begin());
  int carry = 0;
  int i = lhs.digits.size() - 1;
  int j = rhs.digits.size() - 1;
  int k = 0;
  while(i >= 0){
    BigUnsigned temp2;
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

BigUnsigned BigUnsigned::operator-(const BigUnsigned& a) const{
  BigUnsigned lhs = *this;
  BigUnsigned rhs = a;
  BigUnsigned temp;
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


BigUnsigned operator+(const BigUnsigned& a, const BigUnsigned& b){
  BigUnsigned temp;
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

BigUnsigned& BigUnsigned::operator++(){
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

BigUnsigned BigUnsigned::operator++(int){
  BigUnsigned temp = *this;
  ++(*this);
  return temp;
}


BigUnsigned& BigUnsigned::operator--(){
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

BigUnsigned BigUnsigned::operator--(int){
  BigUnsigned temp = *this;
  --(*this);
  return temp;
}


std::ostream& operator<<(std::ostream& os, const BigUnsigned& num){
  for(int i = 0; i < num.digits.size(); i++){
    os << static_cast<char>(num.digits[i]);
  }
  return os;
}

std::istream& operator>>(std::istream& is, BigUnsigned& num){
  std::string temp;
  is >> temp;
  for (int i = 0; i < temp.size(); i++){
    if(!isdigit(temp[i])){
      std::cerr << "Invalid input" << std::endl;
      exit(1);
    }
  }
  num = BigUnsigned(temp.c_str());
  return is;
}

bool BigUnsigned::operator==(const BigUnsigned& other) const{
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

bool operator<(const BigUnsigned& a, const BigUnsigned& b){
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

bool operator>=(const BigUnsigned& a, const BigUnsigned& b){
  return !(a < b);
}

BigUnsigned::BigUnsigned(unsigned n){
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

BigUnsigned::BigUnsigned(const char* a){
  while(*a != '\0'){
    unsigned char temp = *a;
    digits.push_back(temp);
    a++;
  }
}

BigUnsigned::BigUnsigned(const BigUnsigned& other){
  digits = other.digits;
}

BigUnsigned& BigUnsigned::operator=(const BigUnsigned& other){
  if(this != &other){
    digits = other.digits;
  }
  return *this;
}

