#ifndef NIF_H
#define NIF_H

#include <iostream>
#include <string>

class nif{
  public:
    nif() : value_(std::rand() % 100000000) {}
    nif(long value) : value_(value) {
      if (value < 0 || value > 99999999) {
        throw std::invalid_argument("NIF no válido");
      }
    }
    bool operator==(const nif& other) const;
    bool operator!=(const nif& other) const;
    operator long() const { return value_; }
    friend std::ostream& operator<<(std::ostream& os, const nif& nif);
    friend std::istream& operator>>(std::istream& is, nif& nif);
    nif operator=(const nif& k);

  private:
    long value_;
};

bool nif::operator==(const nif& other) const {
  return value_ == other.value_;
}

bool nif::operator!=(const nif& other) const {
  return value_ != other.value_;
}

std::ostream& operator<<(std::ostream& os, const nif& nif) {
  os << nif.value_;
  return os;
}

std::istream& operator>>(std::istream& is, nif& nif) {
  is >> nif.value_;
  return is;
}

nif nif::operator=(const nif& k) {
  value_ = k.value_;
  return *this;
}



#endif