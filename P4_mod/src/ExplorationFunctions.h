#ifndef EXPLORATIONFUNCTION_H
#define EXPLORATIONFUNCTION_H


#include <iostream>

#include "DispersionFunctions.h"
template <class Key>
class ExplorationFunction {
 public: 
  virtual unsigned operator()(const Key& k, unsigned i) const = 0;
};

template <class Key>
class LinearExplorationFunction : public ExplorationFunction<Key> {
 public:
  unsigned operator()(const Key& k, unsigned i) const;
};

//Exploración lineal, g(k,i) = i
template <class Key>
unsigned LinearExplorationFunction<Key>::operator()(const Key& k, unsigned i) const {
  return ++i;
}


template <class Key>
class QuadraticExplorationFunction : public ExplorationFunction<Key> {
 public:
  unsigned operator()(const Key& k, unsigned i) const;
};

//Exploración cuadrática, g(k,i) = i^2
template <class Key>
unsigned QuadraticExplorationFunction<Key>::operator()(const Key& k, unsigned i) const {
  return i * i;
}


//Exploración doble dispersión, g(k,i) = h(k) * i 
template <class Key>
class DoubleDispersionExplorationFunction : public ExplorationFunction<Key> {
 public:
  DoubleDispersionExplorationFunction(DispersionFunction<Key>* dispersion_function) : df_(dispersion_function) {}
  unsigned operator()(const Key& k, unsigned i) const;

 private:
  DispersionFunction<Key>* df_;
};

template <class Key>
unsigned DoubleDispersionExplorationFunction<Key>::operator()(const Key& k, unsigned i) const {
  return (this->df_->operator()(k) * i);
}

template <class Key>
class RedispersionExplorationFunction : public ExplorationFunction<Key> {
 public:
  unsigned operator()(const Key& k, unsigned i) const;
};

template <class Key>
unsigned RedispersionExplorationFunction<Key>::operator()(const Key& k, unsigned i) const {
  srand(k);
  for (int m = 1; m < i; m++) {
    rand();
  }
  return rand();
}


#endif