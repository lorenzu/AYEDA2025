#include <iostream>
#include <iomanip>
#include "Sequence.h"
#include "ExplorationFunctions.h"
#include "DispersionFunctions.h"
#include "Hash.h"
#include "NIF.h"

struct Parameters {
  unsigned tableSize;
  std::string dispersionFunction;
  std::string hashType;
  unsigned blockSize = 0;
  std::string explorationFunction;
};

Parameters ParseArguments(int argc, char* argv[]){
  Parameters parameters;
  bool hasTableSize = false;
  bool hasDispersionFunction = false;
  bool hasHashType = false;
  bool hasBlockSize = false;
  bool hasExplorationFunction = false;

  if(argc < 4){
    std::cerr << "Faltan argumentos obligatorios.\n";
    throw std::invalid_argument("Faltan argumentos obligatorios.");
  }

  for (int i = 1; i < argc; i++){
    std::string arg = argv[i];
    if (arg == "-ts"){
      if (i + 1 < argc){
        parameters.tableSize = std::stoi(argv[i + 1]);
        hasTableSize = true;
        ++i;
      } else {
        throw std::invalid_argument("Falta el argumento para la opción -ts");
      }
    } else if (arg == "-fd"){
      if (i + 1 < argc){
        parameters.dispersionFunction = argv[i + 1];
        hasDispersionFunction = true;
        ++i;
      } else {
        throw std::invalid_argument("Falta el argumento para la opción -fd");
      }
    } else if (arg == "-hash"){
      if (i + 1 < argc){
        parameters.hashType = argv[i + 1];
        hasHashType = true;
        ++i;
      } else {
        throw std::invalid_argument("Falta el argumento para la opción -hash");
      }
    } else if (arg == "-bs"){
      if (i + 1 < argc){
        parameters.blockSize = std::stoi(argv[i + 1]);
        hasBlockSize = true;
        ++i;
      } else {
        throw std::invalid_argument("Falta el argumento para la opción -bs");
      }
    } else if (arg == "-fe"){
      if (i + 1 < argc){
        parameters.explorationFunction = argv[i + 1];
        hasExplorationFunction = true;
        ++i;
      } else {
        throw std::invalid_argument("Falta el argumento para la opción " + arg);
      }
    } else {
      throw std::invalid_argument("Opción desconocida");
    }
  }
  return parameters;
}


int main(int argc, char* argv[]) {
  Parameters parameters;
  try {
    parameters = ParseArguments(argc, argv);
  } catch (const std::invalid_argument& e) {
    std::cerr << "Error: " << e.what() << std::endl;
    return EXIT_FAILURE;
  }
  std::cout << "->  Tipo de hash:              " << parameters.hashType;
  std::cout << "->  Función de dispersión:     " << parameters.dispersionFunction;
  std::cout << "->  Función de exploración:    " << parameters.explorationFunction;
  std::cout << "->  Tamaño del bloque:         " << parameters.blockSize;
  std::cout << "-> Tamaño de la tabla:        " << parameters.tableSize;
  
  // punteros a las clases de dispersion y exploracion
  DispersionFunction<nif>* dispersion = nullptr;
  ExplorationFunction<nif>* exploration = nullptr;
  HashTable<nif, dynamicSequence<nif>>* dynamichash = nullptr;
  HashTable<nif, staticSequence<nif>>* static_hash = nullptr;
  // Codigo de funcion de dispersión 
  if (parameters.dispersionFunction == "0") {
    std::cout << "Funcion de dispersion Modulo" << std::endl;
    dispersion = new ModuleDispersion<nif>(parameters.tableSize);
  } else if (parameters.dispersionFunction == "1") {
    std::cout << "Funcion de dispersion PseudoRandom" << std::endl;
    dispersion = new PseudoRandomDispersion<nif>(parameters.tableSize);
  } else if (parameters.dispersionFunction == "2") {
    std::cout << "Funcion de dispersion Suma" << std::endl;
    dispersion = new SumDispersion<nif>(parameters.tableSize);
  } else {
    std::cout << "Código de función de dispersión incorrecto" << std::endl;
    std::cout << "Introduce o 0 para Modulo, 1 para PseudoRandom o 2 para Suma" << std::endl;
    exit(EXIT_FAILURE);
  }

  
  // codigo de funcion de exploración
  if (parameters.hashType == "close") {
    if (parameters.explorationFunction == "0") {
      std::cout << "Funcion de exploracion Lineal" << std::endl;
      exploration = new LinearExplorationFunction<nif>();
    } else if (parameters.explorationFunction == "1") {
      std::cout << "Funcion de exploracion Cuadratica" << std::endl;
      exploration = new QuadraticExplorationFunction<nif>();
    } else if (parameters.explorationFunction == "2") {
      std::cout << "Funcion de exploracion Doble dispersión" << std::endl;
      exploration = new DoubleDispersionExplorationFunction<nif>(dispersion);
    } else if (parameters.explorationFunction == "3") {
      std::cout << "Funcion de exploracion Redispersion" << std::endl;
      exploration = new RedispersionExplorationFunction<nif>();
    } else {
      std::cout << "Código de función de exploración incorrecto" << std::endl;
      std::cout << "Introduce o 0 para Lineal, 1 para Cuadrática, 2 para Doble dispersión o 3 para PseudoRandom" << std::endl;
      exit(EXIT_FAILURE);
    }
  }

  if (parameters.hashType == "open") {
    std::cout << "Tabla hash de dispersión abierta" << std::endl;
    dynamichash = new HashTable<nif, dynamicSequence<nif>>(parameters.tableSize, *dispersion, *exploration);
    dynamichash->menu();
  } else if (parameters.hashType == "close") {
    std::cout << "Tabla hash de dispersión cerrada" << std::endl;
    static_hash = new HashTable<nif, staticSequence<nif>>(parameters.tableSize, parameters.blockSize, *dispersion, *exploration);
    static_hash->menu();
  }

  delete dispersion;
  delete exploration;
  delete dynamichash;
  delete static_hash;
  return 0;

}