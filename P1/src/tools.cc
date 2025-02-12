#include "tools.h"

BigInteger gcd(const BigInteger &a, const BigInteger &b)
{
  if(a == 0){
    return b;
  }
  return gcd(b % a, a);
}