#ifndef DISPERSIONFUNCTION_H
#define DISPERSIONFUNCTION_H

#include <iostream>



template<class Key>
class DispersionFunction {
 public: 
  virtual unsigned operator()(const Key& k) const = 0;
};

template<class Key>
class ModuleDispersion: public DispersionFunction<Key> {
 public:
  ModuleDispersion(const unsigned n) : tableSize_(n) {}
  ~ModuleDispersion() {}
  unsigned operator()(const Key& k) const;

 private:
  unsigned tableSize_;
};

template<class Key>
unsigned ModuleDispersion<Key>::operator()(const Key& k) const {
  return k % tableSize_;
}


template<class Key>
class SumDispersion: public DispersionFunction<Key> {
 public:
  SumDispersion(const unsigned n) : tableSize_(n) {}
  ~SumDispersion() {}
  unsigned operator()(const Key& k) const;

 private:
  unsigned tableSize_;
};

template <class Key>
unsigned SumDispersion<Key>::operator()(const Key& k) const {
  //sumar los valores de la clave y devolver el modula del tamañano con la suma
  unsigned sum{0};
  long aux{k};
  while (aux > 0) {
    sum += aux % 10;
    aux /= 10;
  }

  return (sum % tableSize_);
}


template<class Key>
class PseudoRandomDispersion: public DispersionFunction<Key> {
 public:
  PseudoRandomDispersion(const unsigned n) : tableSize_(n) {}
  ~PseudoRandomDispersion() {}
  unsigned operator()(const Key& k) const;

 private:
  unsigned tableSize_;
};

template<class Key>
unsigned PseudoRandomDispersion<Key>::operator()(const Key& k) const {
  srand(k);
  return rand() % tableSize_;
}


#endif 