#ifndef NODOB_H
#define NODOB_H
template <typename Key>
class NodoB {
protected:
  Key dato;
  NodoB<Key>* izdo;
  NodoB<Key>* dcho;

public:
  NodoB(Key key, NodoB<Key>* izq = nullptr, NodoB<Key>* der = nullptr)
      : dato{key}, izdo{izq}, dcho{der} {}

  // Métodos para acceder y modificar los atributos
  const Key& getDato() const {
    return dato;
  }

  void setDato(const Key& valor) {
    dato = valor;
  }

  NodoB<Key>* getIzdo() const {
    return izdo;
  }

  NodoB<Key>*& getIzdo() {
    return izdo;
  }

  void setIzdo(NodoB<Key>* nodo) {
    izdo = nodo;
  }

  NodoB<Key>* getDcho() const {
    return dcho;
  }

  NodoB<Key>*& getDcho() {
    return dcho;
  }

  void setDcho(NodoB<Key>* nodo) {
    dcho = nodo;
  }
};

// clase nodoAVL que deriva de la clase nodoB

#endif