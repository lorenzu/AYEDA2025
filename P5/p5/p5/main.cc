

#include<iostream>
#include<vector>
#include<string>
#include<fstream>
#include<algorithm>

#include "Sequences.h"
#include "SortMethod.h"
#include "SortMethodTrace.h"

#include "NIF.h"
// Función para parsear los argumentos de línea de comandos
void parseArguments(int argc, char* argv[], int& size, std::string& method, std::string& initType, std::string& filename, bool& trace) {
  bool random = false;
  bool manual = false;
  if (argc < 2) {
    std::cerr << "Uso: " << argv[0] << " -size <tamaño> -ord <método> -init <tipo> [-trace <y/n>]" << std::endl;
    exit(1);
  }
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "-size" && i + 1 < argc) {
            size = std::stoi(argv[++i]);
        } else if (arg == "-ord" && i + 1 < argc) {
            method = argv[++i];
        } else if (arg == "-init" && i + 1 < argc) {
            initType = argv[++i];
            if (initType == "file" && i + 1 < argc) {
                filename = argv[++i];
            } else if (initType == "random") {
                random = true;
            } else if(initType == "manual"){
                manual = true;
            }
        } else if (arg == "-trace" && i + 1 < argc) {
            trace = (std::string(argv[++i]) == "y");
        }
    }
}

//mod numero comparaciones e iteraciones

//hacer tabla con todos los algoritmos

int main(int argc, char* argv[]) {
  int size = 0;
  std::string method;
  std::string initType = "random";
  std::string filename;
  bool trace = true;
  parseArguments(argc, argv, size, method, initType, filename, trace);
  //debe de crearse un puntero a la clase correspondiente según el método de ordenación que se haya pasado por parámetro
  StaticSequence<NIF>* sequence = new StaticSequence<NIF>(size);
 if (initType == "manual") {
    sequence -> fillManual();
  } else if (initType == "random") {
    sequence -> fillRandom();
  } else if (initType == "file") {
    sequence -> fillFromFile(filename);
  } 
  //debe de crearse un puntero a la clase correspondiente según el método de ordenación que se haya pasado por parámetro
  if(trace == true){
    SortMethodTrace<NIF>* sortMethod;
    if (method == "selection" ) {
      sortMethod = new SelectionSortMethodTrace<NIF>(*sequence);
    } else if (method == "quick") {
      sortMethod = new QuickSortMethodTrace<NIF>(*sequence);
    } else if (method == "heap") {
      sortMethod = new HeapSortMethodTrace<NIF>(*sequence);
    } else if (method == "shell") {
      sortMethod = new ShellSortMethodTrace<NIF>(*sequence, 0.5);
    } else if(method == "radix") {
      sortMethod = new RadixSortMethodTrace<NIF>(*sequence);
    } else {
      std::cerr << "Método de ordenación no válido" << std::endl;
      return 1;
    }

    sortMethod -> SortTrace(true);
  } else {
  SortMethod<NIF>* sortMethod;
  if (method == "selection" ) {
    sortMethod = new SelectionSortMethod<NIF>(*sequence);
  } else if (method == "quick") {
    sortMethod = new QuickSortMethod<NIF>(*sequence);
  } else if (method == "heap") {
    sortMethod = new HeapSortMethod<NIF>(*sequence);
  } else if (method == "shell") {
    sortMethod = new ShellSortMethod<NIF>(*sequence, 0.5);
  } else if(method == "radix") {
    sortMethod = new RadixSortMethod<NIF>(*sequence);
  } else {
    std::cerr << "Método de ordenación no válido" << std::endl;
    return 1;
  }

      sortMethod -> Sort();
  }

  return 0;
}