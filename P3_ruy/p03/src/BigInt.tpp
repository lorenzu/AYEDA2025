#include <string.h>

template <size_t Base>
BigInt<Base>::BigInt(long n) {
  if (n < 0) {
    sign_ = true;
  }

  if (n == 0) {
    big_int_.push_back('0');
  }

  for (int num = std::abs(n); num > 0; num /= 10) {
    int curr = num % 10;
    if (curr > Base) throw BigIntBadDigit();        //Numero sea mayor que la base
    big_int_.push_back(cconvert(curr));             //Convierte a char y lo envia al final del BigInt
  }
}

template <size_t Base>
BigInt<Base>::BigInt(const std::string& num) {     //Recibimos cadena de texto
  for (int i = num.size() - 1; i >= 0; i--) {      //Leemos de atras alante de menor a mayor valor
    if (i == 0 && num[i] == '-') {
      sign_ = true;
      return;
    }

    if (iconvert(num[i]) > Base) throw BigIntBadDigit(); //Recibe char y devuelve numero

    big_int_.push_back(num[i]);
  }
}

template <size_t Base>
BigInt<Base>::BigInt(const char* num) {         //Trabajamos con el char en este caso de mayor a menor valor 
  for (int i = 0; num[i] != 0; i++) {           //Para convertir de char a num
    if (i == 0 && num[i] == '-') {
      sign_ = true;
      continue;
    }

    if (iconvert(num[i]) > Base) throw BigIntBadDigit();      //Recibe char y devuelve numero

    big_int_.insert(big_int_.begin(), num[i]);
  }
}

template <size_t Base>
BigInt<Base>::BigInt(const BigInt<Base>& other) {             //Copia basicamente sin remordimiento
  *this = other;
}

template <size_t Base>
BigInt<Base>::BigInt(std::vector<char> number, bool sign)     //
    : big_int_{number}, sign_{sign} {}

template <size_t Base>
BigInt<Base>& BigInt<Base>::operator=(const BigInt<Base>& other) {      //Llama a la funcion de copia de arriba
  sign_ = other.sign_;                                                  
  big_int_.resize(other.big_int_.size());
  memcpy(big_int_.data(), other.big_int_.data(),                        //Funcion utilizada para copiar el contenido
         big_int_.size() * sizeof(char));                               //de donde a donde y el tamaño multiplicado 
                                                                        //por el tamaño que de cada elmento que es un char
  return *this;
};

template <size_t Base>
std::ostream& operator<<(std::ostream& os, const BigInt<Base>& num) {   //Lo utilizamos para imprimir por pantalla signo y dijito a digito
  if (num.sign_) {                                                      //de alante atras
    os << '-';
  }
  for (int i = num.big_int_.size() - 1; i >= 0; i--) {
    os << num[i];
  }

  return os;
}

template <size_t Base>
std::istream& operator>>(std::istream& is, BigInt<Base>& num) {       //Operacion de insección que es cadena de texto y se lo pasamos 
  std::string temp;                                                   //al constructor que nos lo pasa de string a int
  is >> temp;
  num = BigInt<Base>(temp);
  return is;
}

//Getters

template <size_t Base>
inline bool BigInt<Base>::sign() const {            //Saber el signo de un numero 
  return sign_;
}

template <size_t Base>
inline size_t BigInt<Base>::base() const {          //Retorno del tipo de base mayor
  return Base;
}
template <size_t Base>    
inline size_t BigInt<Base>::size() const {          //Tamaño del vector 
  return big_int_.size();
}

template <size_t Base>
inline char BigInt<Base>::operator[](int pos) const {     //Operaor de posición corchetes
  return big_int_[pos];
}

template <size_t Base>
bool operator==(const BigInt<Base>& lhs, const BigInt<Base>& rhs) {     //std::equal compara basicamente si son totalmente igual
  return std::equal(lhs.big_int_.begin(), lhs.big_int_.end(),
                    rhs.big_int_.begin()) &&
         lhs.sign_ == rhs.sign_;
}

template <size_t Base>
bool BigInt<Base>::operator!=(const BigInt<Base>& other) const {        //utilzando el negado de la funcion de arriba si el signo o el numero
  return !std::equal(big_int_.begin(), big_int_.end(),                  //distinto. Descartamos
                     other.big_int_.begin()) ||
         sign_ != other.sign_;
}

template <size_t Base>
bool operator>(const BigInt<Base>& lhs, const BigInt<Base>& rhs) {      //Saber si es mayor 
  if (lhs.sign_ && !rhs.sign_) {
    return false;
  } else if (!lhs.sign_ && rhs.sign_) {                                 //si el signo de la izquierda - y derecha + false
    return true;
  }

  if (lhs.big_int_.size() > rhs.big_int_.size()) {
    return true;
  } else if (lhs.big_int_.size() < rhs.big_int_.size()) {               //si el signo de la izquierda + y derecha - true
    return false;
  }

  for (int i = lhs.big_int_.size() - 1; i >= 0; i--) {                 //mismo signo, miramos ambos numeros y recorremos de mayor valor a menor
    if (lhs.big_int_[i] < rhs[i]) { 
      return false;
    } else if (lhs.big_int_[i] > rhs[i]) {
      return true;
    }
  }

  return false;
}

template <size_t Base>
bool operator<(const BigInt<Base>& lhs, const BigInt<Base>& rhs) {              //Se recorre manera contraria
  if (!lhs.sign_ && rhs.sign_) {
    return false;
  } else if (lhs.sign_ && !rhs.sign_) {
    return true;
  }

  if (lhs.big_int_.size() < rhs.big_int_.size()) {
    return true;
  } else if (lhs.big_int_.size() > rhs.big_int_.size()) {
    return false;
  }

  for (int i = lhs.big_int_.size() - 1; i >= 0; i--) {
    if (lhs.big_int_[i] > rhs[i]) {
      return false;
    } else if (lhs.big_int_[i] < rhs[i]) {
      return true;
    }
  }

  return false;
}

template <size_t Base>
bool BigInt<Base>::operator>=(const BigInt<Base>& other) const {
  if (!sign_ && other.sign_) {
    return true;
  } else if (sign_ && !other.sign_) {
    return false;
  }

  if (big_int_.size() > other.big_int_.size()) {
    return true;
  } else if (big_int_.size() < other.big_int_.size()) {
    return false;
  }

  for (int i = big_int_.size() - 1; i >= 0; i--) {
    if (big_int_[i] < other[i]) {
      return false;
    } else if (big_int_[i] > other[i]) {
      return true;
    }
  }

  return true;
}

template <size_t Base>
bool BigInt<Base>::operator<=(const BigInt<Base>& other) const {
  if (!sign_ && other.sign_) {
    return true;
  } else if (sign_ && !other.sign_) {
    return false;
  }

  if (big_int_.size() < other.big_int_.size()) {
    return true;
  } else if (big_int_.size() > other.big_int_.size()) {
    return false;
  }

  for (int i = big_int_.size() - 1; i >= 0; i--) {
    if (big_int_[i] > other[i]) {
      return false;
    } else if (big_int_ < other[i]) {
      return true;
    }
  }

  return true;
}

template <size_t Base>
BigInt<Base>& BigInt<Base>::operator++() {
  *this = *this + BigInt<Base>(1);                    //Ponemos el operador a la dercha con parentesis ++i

  return *this;
}

template <size_t Base>
BigInt<Base> BigInt<Base>::operator++(int) {        //Ponemos el operador a la dercha con parentesis i++
  auto copy = *this;
  ++(*this);
  return copy;
}

template <size_t Base>
BigInt<Base>& BigInt<Base>::operator--() {          //Ponemos el operador a la dercha con parentesis --i
  *this = *this - BigInt<Base>(1);
  return *this;
}

template <size_t Base>
BigInt<Base> BigInt<Base>::operator--(int) {        //Ponemos el operador a la dercha con parentesis i--
  auto copy = *this;
  --(*this);
  return copy;
}

template <size_t Base>
BigInt<Base> operator+(const BigInt<Base>& lhs, const BigInt<Base>& rhs) {
  // Resta
  if (lhs.sign() && !rhs.sign()) return rhs - (-lhs);                     //En alguno de estos dos casos se convierte en una resta
  if (rhs.sign() && !lhs.sign()) return lhs - (-rhs);

  BigInt<Base> out;
  out.big_int_.resize(0);
  int carry = 0;
  for (int i = 0, j = 0, lsize = lhs.big_int_.size(),
           rsize = rhs.big_int_.size();
       i < lsize || j < rsize || carry != 0; i++, j++) {
    int sum = carry;
    sum += (i < lhs.big_int_.size() ? BigInt<Base>::iconvert(lhs[i]) : 0);        //Lo utilizamos para añadir la cifra de i o j si se puede
    sum += (j < rhs.big_int_.size() ? BigInt<Base>::iconvert(rhs[j]) : 0);

    if (sum >= Base) {
      carry = 1;
      sum = sum % Base;
    } else {
      carry = 0;
    }

    out.big_int_.push_back(BigInt<Base>::cconvert(sum));                          //Añadimos el valor en ese sitio de la suma
  }

  if (carry) {
    out.big_int_.push_back(BigInt<Base>::cconvert(carry));                        
  }

  if (lhs.sign_) {                                                                //Si los dos son negativos suma y se añade signo al final
    out.sign_ = true;
  }

  return out;
}

template <size_t Base>
BigInt<Base> BigInt<Base>::operator-(const BigInt<Base>& other) const {           
  // a - (-b) = a + b
  if (other.sign_) return *this + (-other);

  // -a - b = (a + b) * -1
  if (sign_ && !other.sign_) return {(-*this + other).big_int_, true};          //Cogemos sumamos porque los dos son negativos

  // -a - (-b) = b - a
  if (sign_ && other.sign_) return -other + *this;

  auto lhs = *this > other ? *this : other;                                     //Comprobamos cual de los dos es el mayor de los dos 
  auto rhs = *this > other ? other : *this;

  int carry = 0;
  BigInt<Base> out;                                                             //Si el signo es tru significa que es negativo entonces se opera
  if (*this < other) out.sign_ = true;

  out.big_int_.resize(0);
  for (int i = 0, j = 0; i < lhs.big_int_.size() || j < rhs.big_int_.size();
       i++, j++) {
    int a = (i < lhs.big_int_.size() ? BigInt<Base>::iconvert(lhs[i]) : 0);
    int b =
        (j < rhs.big_int_.size() ? BigInt<Base>::iconvert(rhs[j]) : 0) + carry;       //Si podemos cargar los digitos lo hacemos 

    if (a - b >= 0) {
      out.big_int_.push_back(BigInt<Base>::cconvert(a - b));
    } else {
      carry = 1;                                                                      //La llevada del carry
      out.big_int_.push_back(BigInt<Base>::cconvert(a - b + Base));
    }
  }

  if (out.big_int_.back() == '0' && out.big_int_.size() > 1) {                        //Lo utilizo para quitar al 0 si queda 00
    out.big_int_.pop_back();
  }

  return out;
}

template <size_t Base>
BigInt<Base> BigInt<Base>::operator-() const {                                      //Utilizado para cambiar le signo devolvemos una copia
  auto out = *this;
  out.sign_ = !sign_;
  return out;
}

template <size_t Base>
BigInt<Base> BigInt<Base>::operator*(const BigInt<Base>& other) const {             //Multiplicación utilizado
  std::vector<char> out;
  int carry = 0;
  for (int i = 0; i < big_int_.size(); i++) {
    for (int j = 0; j < other.big_int_.size(); j++) {
      int mult = BigInt<Base>::iconvert(big_int_[i]) *
                     BigInt<Base>::iconvert(other[j]) +
                 carry;
      carry = mult / Base;

      if (j + i >= out.size()) {
        out.push_back(BigInt<Base>::cconvert(mult % Base));                         //La posición de resultado es dada por la suma de las posiciones de los operandos
      } else {
        out[j + i] = BigInt<Base>::cconvert(BigInt<Base>::iconvert(out[j + i]) +
                                            mult % Base);
      }
    }
  }

  if (carry != 0) {
    out.push_back(BigInt<Base>::cconvert(carry));                                   // Final de operacion y signo respetando las leyes de signos
  }

  return {out, sign_ || other.sign_};
}

template <size_t Base>
BigInt<Base> operator/(const BigInt<Base>& num, const BigInt<Base>& den) {          
  if (den == BigInt<Base>("0")) throw BigIntDivisionByZero();

  BigInt<Base> r = num, q("0");
  while (r >= den) {
    r = r - den;
    q++;
  }
  return q;
}

template <size_t Base>
BigInt<Base> BigInt<Base>::operator%(const BigInt<Base>& other) const {
  if (*this == BigInt<Base>("0")) throw BigIntDivisionByZero();

  BigInt<Base> r = *this, q("0");
  while (r >= other) {
    r = r - other;
    q++;
  }
  return r;
}

// template <size_t Base>
// BigInt<Base> pow(const BigInt<Base>& base, const BigInt<Base>& exp) {
//   if (exp == BigInt<Base>("0")) {
//     return BigInt<Base>(1);
//   }

//   BigInt<Base> out = base;
//   for (BigInt<Base> i("0"); i < exp - 1; i++) {
//     out = out * base;
//   }

//   return out;
// }

template <size_t Base>
int BigInt<Base>::iconvert(char raw) {
  if (raw >= 'A') {
    return raw + 10 - 'A';
  } else {
    return raw - '0';
  }
}

template <size_t Base>
char BigInt<Base>::cconvert(int raw) {
  if (raw > 9) {
    return 'A' + raw - 10;
  } else {
    return '0' + raw;
  }
}

template <size_t Base>
Number* BigInt<Base>::add(const Number* other) const {
  BigInt<Base> op_2 = *other;                               //Lo utilizamos para convertir el numero de base ramdom en en la base que queremos

  return new BigInt<Base>(*this + op_2);
}

template <size_t Base>
Number* BigInt<Base>::subtract(const Number* other) const {
  BigInt<Base> op_2 = *other;

  return new BigInt<Base>(*this - op_2);
}

template <size_t Base>
Number* BigInt<Base>::multiply(const Number* other) const {
  BigInt<Base> op_2 = *other;

  return new BigInt<Base>(*this * op_2);
}

template <size_t Base>
Number* BigInt<Base>::divide(const Number* other) const {
  BigInt<Base> op_2 = *other;

  return new BigInt<Base>(*this / op_2);
}

template <size_t Base>
Number* BigInt<Base>::module(const Number* other) const {
  BigInt<Base> op_2 = *other;

  return new BigInt<Base>(*this % op_2);
}

template <size_t Base>
Number* BigInt<Base>::pow(const Number* other) const {
  BigInt<Base> exp = *other;
  if (exp == BigInt<Base>("0")) {
    return new BigInt<Base>(1);
  }

  BigInt<Base> out = *this;
  for (BigInt<Base> i("0"); i < exp - 1; i++) {
    out = out * *this;
  }

  return new BigInt<Base>(out);
}

template <size_t Base>
std::ostream& BigInt<Base>::write(std::ostream& os) const {
  return os << *this;
}

template <size_t Base>
std::istream& BigInt<Base>::read(std::istream& is) {
  return is >> *this;
}

template <size_t Base>
BigInt<Base>::operator BigInt<2>() const {
  if (Base < 2) {
    throw BigIntBaseNotImplemented();
  }

  auto big_int = BigInt<Base>::convert_minnor_base(*this, 2);

  return BigInt<2>(big_int, sign());
};

template <size_t Base>
BigInt<Base>::operator BigInt<8>() const {
  if (Base < 8) {
    BigInt<8> out("0");
    for (int i = big_int_.size() - 1; i >= 0; i--) {
      auto digit = BigInt<8>(iconvert(big_int_[i]));
      out = (out * BigInt<8>(Base)) + digit;
    }

    return out;
  } else if (Base > 8) {
    return BigInt<8>(BigInt<Base>::convert_minnor_base(*this, 8), sign());
  }

  return *this;
};

template <size_t Base>
BigInt<Base>::operator BigInt<10>() const {
  if (Base < 10) {
    BigInt<10> out("0");
    for (int i = big_int_.size() - 1; i >= 0; i--) {
      auto digit = BigInt<10>(iconvert(big_int_[i]));
      out = (out * BigInt<10>(Base)) + digit;
    }

    return out;
  } else if (Base > 10) {
    return BigInt<10>(BigInt<Base>::convert_minnor_base(*this, 10), sign());
  }

  return *this;
};

template <size_t Base>
BigInt<Base>::operator BigInt<16>() const {
  if (Base < 16) {
    BigInt<16> out("0");
    for (int i = big_int_.size() - 1; i >= 0; i--) {
      auto digit = BigInt<16>(iconvert(big_int_[i]));
      out = (out * BigInt<16>(Base)) + digit;
    }

    return out;
  } else if (Base > 16) {
    throw BigIntBaseNotImplemented();
  }

  return *this;
};

template <size_t Base>
std::vector<char> BigInt<Base>::convert_minnor_base(BigInt<Base> number,
                                                    int base) {
  std::vector<char> out;
  while (number > BigInt<Base>("0")) {
    int curr = iconvert(number[0]);
    out.push_back(cconvert(curr % base));
    number = number / BigInt<Base>(base);
  }

  return out;
}
