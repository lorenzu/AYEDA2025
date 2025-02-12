#ifndef BIGU_H
#define BIGU_H

#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>

class BigUnsigned {
  public:
  BigUnsigned(unsigned n = 0);
  BigUnsigned(const char*);
  BigUnsigned(const BigUnsigned&);

  BigUnsigned& operator=(const BigUnsigned&);
  friend std::ostream& operator<<(std::ostream&, const BigUnsigned&);
  friend std::istream& operator>>(std::istream&, BigUnsigned&);
  bool operator==(const BigUnsigned&) const;
  friend bool operator<(const BigUnsigned&, const BigUnsigned&);
  friend bool operator>= (const BigUnsigned&, const BigUnsigned&);

  BigUnsigned& operator++(); // Pre-incremento
  BigUnsigned operator++(int); // Post-incremento
  BigUnsigned& operator--(); // Pre-decremento
  BigUnsigned operator--(int); // Post-decremento

  friend BigUnsigned operator+(const BigUnsigned&, const BigUnsigned&);
  BigUnsigned operator-(const BigUnsigned&) const;
  BigUnsigned operator*(const BigUnsigned&) const;
  friend BigUnsigned operator/(const BigUnsigned&, const BigUnsigned&);
  BigUnsigned operator%(const BigUnsigned&) const;
  
  private:
  std::vector<unsigned char> digits;
};

#endif