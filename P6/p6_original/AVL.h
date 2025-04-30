#include "AB.h"
#include "NodoB.h"
#include "NodoAVL.h"
#include "ABB.h"
#include <queue>
#include <iostream>
#ifndef AVL_H
#define AVL_H

// calse AVL que hereda de ABB
template <typename Key>
class AVL : public ABB<Key> {
public:
  // Constructor de la clase AVL<Key>
  AVL() : ABB<Key>() {}

  void setTrace(bool trace) {
    this->trace = trace;
  }

  NodoAVL<Key>* getRaiz() const {
    return reinterpret_cast<NodoAVL<Key>*>(this->raiz);
  }

  NodoAVL<Key>*& getRaiz() {
    return reinterpret_cast<NodoAVL<Key>*&>(this->raiz);
  }


int alturaN(NodoAVL<Key>* nodo) const {
  if (nodo == nullptr) {
    return 0;
  } else {
    int alturaIzq = alturaN(nodo->getIzdo());
    int alturaDcha = alturaN(nodo->getDcho());

    if (alturaIzq > alturaDcha) {
      return alturaIzq + 1;
    } else {
      return alturaDcha + 1;
    }
  }
}
  
  void rotacion_II(NodoAVL<Key> *&nodo){
  if (this->trace) {
    std::cout << "Rotation II en [" << nodo->getDato() << "(" << alturaN(nodo->getIzdo()) - alturaN(nodo->getDcho()) << ")]" << std::endl;
  }
    NodoAVL<Key>* nodo1 = nodo->getIzdo();
    nodo->setIzdo(nodo1->getDcho());
    nodo1->setDcho(nodo);
    if(nodo1->getBal() == 1){
      nodo->setBal(0); 
      nodo1->setBal(0);
  } else {
    nodo->setBal(1);
    nodo1->setBal(-1);
  }
  nodo = nodo1;
  }

  void rotacion_DD(NodoAVL<Key> *&nodo){
  if (this->trace) {
    std::cout << "Rotation DD en [" << nodo->getDato() << "(" << alturaN(nodo->getIzdo()) - alturaN(nodo->getDcho()) << ")]" << std::endl;
  }
    NodoAVL<Key>* nodo1 = nodo->getDcho();
    nodo->setDcho(nodo1->getIzdo());
    nodo1->setIzdo(nodo);
    if(nodo1->getBal() == -1){
      nodo->setBal(0);
      nodo1->setBal(0);
  } else {
    nodo->setBal(-1);
    nodo1->setBal(1);
  }
  nodo = nodo1;
  }

  void rotacion_ID(NodoAVL<Key> *&nodo){
  if (this->trace) {
    std::cout << "Rotation ID en [" << nodo->getDato() << "(" << alturaN(nodo->getIzdo()) - alturaN(nodo->getDcho()) << ")]" << std::endl;
  }
    NodoAVL<Key>* nodo1 = nodo->getIzdo();
    NodoAVL<Key>* nodo2 = nodo1->getDcho();
    nodo->setIzdo(nodo2->getDcho());
    nodo2->setDcho(nodo);
    nodo1->setDcho(nodo2->getIzdo());
    nodo2->setIzdo(nodo1);
    if(nodo2->getBal() == -1){
      nodo1->setBal(1);
    } else {
      nodo1->setBal(0);
    }
    if(nodo2->getBal() == 1){
      nodo->setBal(-1);
    } else {
      nodo->setBal(0);
    }
    nodo2->setBal(0);
    nodo = nodo2;
  }

  void rotacion_DI(NodoAVL<Key> *&nodo){
  if (this->trace) {
    std::cout << "Rotation DI en [" << nodo->getDato() << "(" << alturaN(nodo->getIzdo()) - alturaN(nodo->getDcho()) << ")]" << std::endl;
  }
    NodoAVL<Key>* nodo1 = nodo->getDcho();
    NodoAVL<Key>* nodo2 = nodo1->getIzdo();
    nodo->setDcho(nodo2->getIzdo());
    nodo2->setIzdo(nodo);
    nodo1->setIzdo(nodo2->getDcho());
    nodo2->setDcho(nodo1);
    if(nodo2->getBal() == 1){
      nodo1->setBal(-1);
    } else {
      nodo1->setBal(0);
    }
    if(nodo2->getBal() == -1){
      nodo->setBal(1);
    } else {
      nodo->setBal(0);
    }
    nodo2->setBal(0);
    nodo = nodo2;
  }

  void insert_re_balancea_izqda(NodoAVL<Key>* &nodo, bool& crece){
    switch(nodo->getBal()){
      case -1:
        nodo->setBal(0);
        crece = false;
        break;
      case 0:
        nodo->setBal(1);
        break;
      case 1:
        if(nodo->getBal() == 1){
          rotacion_II(nodo);
        } else {
          rotacion_ID(nodo);
          crece = false;
        }
    }
  }

  void insert_re_balancea_dcha(NodoAVL<Key>* &nodo, bool& crece){
    switch(nodo->getBal()){
      case 1:
        nodo->setBal(0);
        crece = false;
        break;
      case 0:
        nodo->setBal(-1);
        break;
      case -1:
        if(nodo->getBal() == -1){
          rotacion_DD(nodo);
        } else {
          rotacion_DI(nodo);
          crece = false;
        }
    }
  }


  void insertar_bal(NodoAVL<Key>* &nodo, NodoAVL<Key>* nuevo, bool& crece){
    if(nodo == nullptr){
      nodo = nuevo;
      crece = true;
    } else if(nuevo->getDato() < nodo->getDato()){
      insertar_bal(nodo->getIzdo(), nuevo, crece);
      if(crece){
        insert_re_balancea_izqda(nodo, crece);
        }
    } else {
      insertar_bal(nodo->getDcho(), nuevo, crece);
      if(crece){
        insert_re_balancea_dcha(nodo, crece);
        }
      }
  }

  bool insertar(const Key& valor) override {
    NodoAVL<Key>* nuevo = new NodoAVL<Key>(valor);
    bool crece = false;
    insertar_bal(getRaiz(), nuevo, crece);
    return true;
  }

  void niveles() const override {
    std::queue<NodoAVL<Key>*> cola;
    NodoAVL<Key>* actual = reinterpret_cast<NodoAVL<Key>*>(this->raiz);
    int nivel = 0;
    cola.push(actual);
    while (!cola.empty()) {
      int n = cola.size();
      std::cout << "Nivel " << nivel << ": ";
      for (int i = 0; i < n; ++i) {
        actual = cola.front();
        cola.pop();
        if (actual != nullptr) {
        if (this->trace) {
          std::cout << "[" << actual->getDato() << "(" << alturaN(actual->getIzdo()) - alturaN(actual->getDcho()) << ")" << "] ";
        } else {
          std::cout << "[" << actual->getDato() << "] ";
        }
          cola.push((actual->getIzdo()));
          cola.push((actual->getDcho()));
        } else {
          std::cout << "[.] ";
        }
      }
      std::cout << std::endl;
      ++nivel;
    }
  }

  private:
  bool trace;
    
};
#endif