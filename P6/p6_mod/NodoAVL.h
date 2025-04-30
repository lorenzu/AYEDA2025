#include "NodoB.h"
#ifndef NODOAVL_H
#define NODOAVL_H
template <typename Key>
class NodoAVL: public NodoB<Key>{
  public:
  NodoAVL(Key key, NodoAVL<Key>* izq = nullptr, NodoAVL<Key>* der = nullptr)
      : NodoB<Key>(key, izq, der) {}
    NodoAVL<Key>* getIzdo() const{
      return static_cast<NodoAVL<Key>*>(this -> getIzdo());
    }
    NodoAVL<Key>* getDcho() const{
      return static_cast<NodoAVL<Key>*>(this -> getDcho());
    }
    NodoAVL<Key>*& getIzdo(){
      return  reinterpret_cast<NodoAVL<Key>*&>(this -> izdo );
    }
    NodoAVL<Key>*& getDcho(){
      return reinterpret_cast<NodoAVL<Key>*&>(this -> dcho);
    }
    void SetIzdo(NodoAVL<Key>* nodo){
      this -> setIzdo(reinterpret_cast<NodoB<Key>*>(nodo));
    }
    void SetDcho(NodoAVL<Key>* nodo){
      this -> setDcho(reinterpret_cast<NodoB<Key>*>(nodo));
    }
    int getBal() const{
      return bal;
    }
    void setBal(int valor){
      bal = valor;
    }
    
  private:
    int bal;
};
#endif
