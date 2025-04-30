#include "NodoB.h"
#ifndef AB_H
#define AB_H
template <typename Key>
class AB {
  // Esta clase tiene el atributo raiz que es un puntero a un nodo de tipo NodoB<Key> y toma el valor nullptr si el árbol está vacío
protected:
  NodoB<Key>* raiz;

public:
  // Método virtual puro para insertar un dato en el árbol
  virtual bool insertar(const Key& valor) = 0;

  // Método virtual puro para buscar un dato en el árbol
  virtual bool buscar(const Key& valor) const = 0;

  // Método virtual puro para recorrer el árbol en inorden
  virtual void inorden() const = 0;

  //Merodo virtual recorrer por niveles
  virtual void niveles() const = 0;

  friend std::ostream& operator<<(std::ostream& os, const AB<Key>& arbol) {
    arbol.niveles();
    return os;
  }

};
#endif