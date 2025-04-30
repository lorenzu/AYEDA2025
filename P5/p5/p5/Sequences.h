#include<iostream>
#include<vector>
#include<string>
#include<fstream>
#include<algorithm>
#ifndef SEQUENCES_H
#define SEQUENCES_H
template <typename Key>
class Sequence {
public:
  //sobrecarga del operador de acceso []
  virtual Key& operator[](int i) = 0;
};

template <typename Key>
class StaticSequence : public Sequence<Key> {
public:
  StaticSequence(int size) : data(size) {}
  //implementa la sobrecarga del operador [] para permitir que los métodos de ordenacion accedan a los elementos de la secuencia
  Key& operator[](int i) override {
    // Implementa la lógica de acceso a los elementos de la secuencia estática
    return data[i]; 
  }

  int size() const {
    return data.size();
  }
  //método que llena la secuencia con números aleatorios
  void fillRandom() {
    srand(time(nullptr));
    for (size_t i = 0; i < data.size(); ++i) {
      //haz que el rango de rand sea entre 10000000 y 99999999
      data[i] = rand() % 10000000 + 90000000; // Modifica según el rango de tus datos
    }
  }

  //método que llena la secuencia con números leídos de un archivo
  void fillFromFile(const std::string& filename) {
    std::ifstream file(filename + ".txt");
    if (file.is_open()) {
      for (size_t i = 0; i < data.size(); ++i) {
        file >> data[i];
      }
    }
    file.close();
  }  
  // método para recibir la secuencia por comando
  void fillManual(){
    for (size_t i = 0; i < data.size(); ++i) {
      std::cout << "Introduce el valor " << i << ": ";
      std::cin >> data[i];
    }
  }
  private:
    std::vector<Key> data;
};
#endif