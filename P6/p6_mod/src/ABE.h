#include "AB.h"
#include "NodoB.h"
#include <queue>
#include <iostream>
#ifndef ABE_H
#define ABE_H
//Define la clase ABE<Key> que hereda de AB<Key> y representa el arbol binario equilibrado
template <typename Key>
class ABE : public AB<Key> {
public:
  // Constructor de la clase ABE<Key>
  ABE() : AB<Key>() {}

  // metodo para obtener el tamaño de un árbol
  const int size(){
    return size(this->raiz);
  }

  //metodo para obtener el tamaño de una rama
  const int size(NodoB<Key>* nodo){
    if(nodo == nullptr){
      return 0;
    }else{
      return 1 + size(nodo->getIzdo()) + size(nodo->getDcho());
    }
  }

  //metodo para obtener la altura de un árbol
  const int height(){
    return height(this->raiz);
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

  //metodo para obtener la altura de una rama
  const int height(NodoB<Key>* nodo){
    if(nodo == nullptr){
      return 0;
    } else {
      int alt_izdo = height(nodo->getIzdo());
      int alt_dcho = height(nodo->getDcho());
      if(alt_dcho > alt_izdo){
        return 1 + alt_dcho;
      } else {
        return 1 + alt_izdo;
      }
  }
  }

  const bool Equilibrado(){
    return Equilibrado(this->raiz);
  }

  const bool Equilibrado(NodoB<Key>* nodo){
    if(nodo == nullptr){
      return true;
    } else {
      int eq = size(nodo->getIzdo()) - size(nodo->getDcho());
      switch (eq)
      {
      case -1:
      case 0:
      case 1:
        return Equilibrado(nodo->getIzdo()) && Equilibrado(nodo->getDcho());
        break;
      default: return false;
        break;
      }
    }
  }

  // Método para insertar un dato en el árbol
  bool insertar(const Key& valor){
    if(buscar(valor)){
      return false;
    } else {
    if(this->raiz == nullptr){
      this->raiz = new NodoB<Key>(valor);
    } else {
      InsertarEquilibrado(this->raiz, valor);
    }
    return true;
    }

  }

  void InsertarEquilibrado(NodoB<Key>* nodo, const Key& valor){
    //si el valor ya existe en el árbol no se inserta
    if(size(nodo->getIzdo()) <= size(nodo->getDcho())){
      if(nodo->getIzdo() == nullptr){
        nodo->setIzdo(new NodoB<Key>(valor));
      } else {
        InsertarEquilibrado(nodo->getIzdo(), valor);
      }
    } else {
      if(nodo->getDcho() == nullptr){
        nodo->setDcho(new NodoB<Key>(valor));
      } else {
        InsertarEquilibrado(nodo->getDcho(), valor);
      }
    }
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
#endif