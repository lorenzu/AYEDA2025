#include <iostream>
#include <queue>
#include <string>
#include <fstream>
#include<algorithm>
#include "AB.h"
#include "NIF.h"
#include "ABB.h"
#include "ABE.h"
#include "NodoB.h"
#include "AVL.h"

void parseArguments(int argc, char* argv[], std::string& ab, std::string& init, std::string& filename, std::string& initType, bool &trace, int &size) {
  bool random = false;
  bool manual = false;
  if (argc < 2) {
    std::cerr << "Uso: " << argv[0] << " -ab <avl|abb> -trace <y|n> -init <file [filename]|random [size]|manual>" << std::endl;
    exit(1);
  }
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "-ab" && i + 1 < argc) {
            ab = argv[++i];
          } else if(arg == "-trace"){
                trace = argv[++i];
            } else if (arg == "-init" && i + 1 < argc) {
            initType = argv[++i];
            if (initType == "file" && i + 1 < argc) {
                filename = argv[++i];
            } else if (initType == "random") {
                random = true;
                size = std::stoi(argv[++i]);
                if (size == 0){
                    std::cerr << "Error: Tamaño incorrecto" << std::endl;
                    exit(1);
                }
              
            } else if(initType == "manual"){
                manual = true;
        }
            }
    }
}

void Manual(AB<NIF>* arbol){
      int nif;
      std::cout << "Introduce el valor " << ": ";
      std::cin >> nif;
      arbol->insertar(nif);
}

void Menu(int &option, AB<NIF>* arbol){
  std::cout << "[0] Salir" << std::endl;
  std::cout << "[1] Insertar" << std::endl;
  std::cout << "[2] Buscar" << std::endl;
  std::cout << "[3] Mostrar" << std::endl;
  std::cout << *arbol << std::endl;
  std::cin >> option;
}

int main(int argc, char* argv[]){
  srand(time(nullptr));
  std::string ab;
  std::string init;
  std::string filename;
  std::string initType;
  bool trace = false;
  int size;
  int option = 9;
  parseArguments(argc, argv, ab, init, filename, initType, trace, size);
  std::cout << trace << std::endl;
  // inicializar un puntero AB<Key> a nullptr y según la opción ab se debe instanciar un objeto de la clase correspondiente
  AB<NIF>* arbol = nullptr;
  if(ab == "abe"){
    arbol = new ABE<NIF>();
  } else if(ab == "abb"){
    arbol = new ABB<NIF>();
  } else if(ab == "avl"){
    arbol = new AVL<NIF>();
    //si trace es true entonces se activa el modo traza
    if(trace == true){
      static_cast<AVL<NIF>*>(arbol)->setTrace(true);
    }
  } else {
    std::cerr << "Error: Opción incorrecta" << std::endl;
    exit(1);
  }

  if(initType == "random"){
    for(int i = 0; i < size; i++){
      NIF nif = rand() % 10000000 + 10000000;
      arbol->insertar(nif);
    }
  } else if(initType == "file"){
    std::ifstream file(filename + ".txt");
    if (file.is_open()) {
      int nif;
      while(file >> nif){
        arbol->insertar(nif);
      }
    }
    file.close();
  } else if(initType == "manual"){
      Manual(arbol);
  } else {
    std::cerr << "Error: Opción incorrecta" << std::endl;
    exit(1);
  }

  while(option != 0){
    Menu(option, arbol);
    if(option == 1){
      Manual(arbol);
    } else if(option == 2){
      int nif;
      std::cout << "Introduce el valor a buscar: ";
      std::cin >> nif;
      if(arbol->buscar(nif)){
        std::cout << "El valor " << nif << " se encuentra en el árbol" << std::endl;
      } else {
        std::cout << "El valor " << nif << " no se encuentra en el árbol" << std::endl;
      }
    } else if(option == 3){
      std::cout << *arbol << std::endl;
    }
  }



  return 0;

}









