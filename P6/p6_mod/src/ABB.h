#include "AB.h"
#include "NodoB.h"
#include <queue>
#include <iostream>
#ifndef ABB_H
#define ABB_H
//implementa la clase ABB<Key> que hereda de AB<Key> y representa el arbol binario de búsqueda
template <typename Key>
class ABB : public AB<Key> {
public:
  // Constructor de la clase ABB<Key>
  ABB() : AB<Key>() {}

  // Método para insertar un dato en el árbol
  bool insertar(const Key& valor) override {
    NodoB<Key>* nuevo = new NodoB<Key>(valor);
    NodoB<Key>* actual = this->raiz;
    NodoB<Key>* anterior = nullptr;

    while (actual != nullptr) {
      anterior = actual;
      if (valor < actual->getDato()) {
        actual = actual->getIzdo();
      } else if (valor > actual->getDato()) {
        actual = actual->getDcho();
      } else {
        delete nuevo;
        return false;
      }
    }

    if (anterior == nullptr) {
      this->raiz = nuevo;
    } else if (valor < anterior->getDato()) {
      anterior->setIzdo(nuevo);
    } else {
      anterior->setDcho(nuevo);
    }

    return true;
  }

  // Método para buscar un dato en el árbol
  bool buscar(const Key& valor) const override {
    NodoB<Key>* actual = this->raiz;

    while (actual != nullptr) {
      if (valor < actual->getDato()) {
        actual = actual->getIzdo();
      } else if (valor > actual->getDato()) {
        actual = actual->getDcho();
      } else {
        return true;
      }
    }

    return false;
  }

  // Método para recorrer el árbol en inorden
  void inorden() const override {
    inorden(this->raiz);
  }

  // Método para recorrer el árbol por niveles
  void niveles() const override {
    // Para recorrer el árbol por niveles necesitamos una cola y se recorren los nodos en orde creciente desde la raíz y dentro de cada nivel de izquierda a derecha
    std::queue<NodoB<Key>*> cola;
    NodoB<Key>* actual = this->raiz;
    int nivel = 0;
    //ahora hay que recorrrer desde la raiz, se va mostrando en que nivel estamos por pantalla
    //se va metiendo en la cola los nodos de cada nivel
    //se va mostrando por pantalla los nodos de cada nivel
    //si en ese nivel se encuentran nodos vacíos se imprime [.]
    //cuando se termina de recorrer un nivel se imprime un salto de línea
    cola.push(actual);
    while (!cola.empty()) {
      int n = cola.size();
      std::cout << "Nivel " << nivel << ": ";
      for (int i = 0; i < n; ++i) {
        actual = cola.front();
        cola.pop();
        if (actual != nullptr) {
          std::cout << actual->getDato() << " ";
          cola.push(actual->getIzdo());
          cola.push(actual->getDcho());
        } else {
          std::cout << "[.] ";
        }
      }
      std::cout << std::endl;
      ++nivel;
    }
  }

private:
  // Método privado para recorrer el árbol en inorden
  void inorden(NodoB<Key>* nodo) const {
    if (nodo != nullptr) {
      inorden(nodo->getIzdo());
      std::cout << nodo->getDato() << " ";
      inorden(nodo->getDcho());
    }
  }
};
  // Método para recorr

#endif