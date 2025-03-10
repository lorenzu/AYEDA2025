#ifndef BIGINT_H_
#define BIGINT_H_

#include <iostream>
#include <vector>

#include "Number.h"

template <size_t Base>
class BigInt : public Number {
 public:
  BigInt(long n = 0);
  BigInt(const std::string&);
  BigInt(const char*);
  BigInt(const BigInt<Base>&);
  BigInt(std::vector<char>, bool sign);
  BigInt<Base>& operator=(const BigInt<Base>&);

  friend std::ostream& operator<< <>(std::ostream&, const BigInt<Base>&);
  friend std::istream& operator>><>(std::istream&, BigInt<Base>&);

  bool sign() const;
  char operator[](int) const;
  size_t base() const;
  size_t size() const;

  friend bool operator==<>(const BigInt<Base>&, const BigInt<Base>&);
  bool operator!=(const BigInt<Base>&) const;
  friend bool operator><>(const BigInt<Base>&, const BigInt<Base>&);
  bool operator>=(const BigInt<Base>&) const;
  friend bool operator< <>(const BigInt<Base>&, const BigInt<Base>&);
  bool operator<=(const BigInt<Base>&) const;

  BigInt<Base>& operator++();
  BigInt<Base> operator++(int);
  BigInt<Base>& operator--();
  BigInt<Base> operator--(int);

  friend BigInt<Base> operator+<>(const BigInt<Base>&, const BigInt<Base>&);
  BigInt<Base> operator-(const BigInt<Base>&) const;
  BigInt<Base> operator-() const;
  BigInt<Base> operator*(const BigInt<Base>&) const;
  friend BigInt<Base> operator/<>(const BigInt<Base>&, const BigInt<Base>&);
  BigInt<Base> operator%(const BigInt<Base>&) const;

  // friend BigInt<Base> pow<Base>(const BigInt<Base>&, const BigInt<Base>&);

  operator BigInt<2>() const override;

  operator BigInt<8>() const override;

  operator BigInt<10>() const override;

  operator BigInt<16>() const override;

  Number* add(const Number*) const override;
  Number* subtract(const Number*) const override;
  Number* multiply(const Number*) const override;
  Number* divide(const Number*) const override;
  Number* module(const Number*) const override;
  Number* pow(const Number*) const override;

 private:
  std::vector<char> big_int_;
  bool sign_ = false;

  std::ostream& write(std::ostream&) const override;
  std::istream& read(std::istream&) override;

  static char cconvert(int raw);
  static int iconvert(char raw);

  static std::vector<char> convert_minnor_base(BigInt<Base>, int);
};

#include "BigInt.tpp"
#endif
