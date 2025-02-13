#include "tools.h"

BigInteger gcd(const BigInteger &a, const BigInteger &b)
{
  if(a == 0){
    return b;
  }
  return gcd(b % a, a);
}

BigUnsigned mean(std::vector<BigUnsigned> bu_v){
  int size = bu_v.size();
  BigUnsigned sum;
  for(int i = 0; i < size; i++){
    sum = bu_v[i] + sum;
  }
  BigUnsigned bu_size(size);
  std::cout << "promedio: ";
  BigUnsigned mean;
  mean = sum / bu_size;
  std::cout << mean << std::endl;
  return mean;
}