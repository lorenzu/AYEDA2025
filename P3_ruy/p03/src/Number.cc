#include "Number.h"

#include "BigInt.h"

Number* Number::create(size_t base, const std::string& s) {
  switch (base) {
    case 2:
      return new BigInt<2>(s);
    case 8:
      return new BigInt<8>(s);
    case 10:
      return new BigInt<10>(s);
    case 16:
      return new BigInt<16>(s);
    default:
      throw BigIntBaseNotImplemented();
  }
}

std::ostream& operator<<(std::ostream& os, const Number& number) {
  return number.write(os);
}
std::istream& operator>>(std::istream& is, Number& number) {
  return number.read(is);
}
