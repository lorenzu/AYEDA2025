#ifndef BIGINT_H
#define BIGINT_H
#include "BigU.h"

class BigInteger {
  public:
  BigInteger(int n = 0);
  BigInteger(const BigUnsigned&);

  BigInteger& operator=(const BigInteger&);
  friend std::ostream& operator<<(std::ostream&, const BigInteger&);
  friend std::istream& operator>>(std::istream&, BigInteger&);

  bool operator==(const BigInteger&) const;
  friend bool operator<(const BigInteger&, const BigInteger&);

  BigInteger& operator++(); // Pre-incremento
  BigInteger operator++(int); // Post-incremento
  BigInteger& operator--(); // Pre-decremento
  BigInteger operator--(int); // Post-decremento

  friend BigInteger operator+(const BigInteger&, const BigInteger&);
  BigInteger operator-(const BigInteger&) const;
  BigInteger operator*(const BigInteger&) const;
  friend BigInteger operator/(const BigInteger&, const BigInteger&);
  BigInteger operator%(const BigInteger&) const;

  private:
  BigUnsigned num;
  bool IsNegative = false;

};

#endif