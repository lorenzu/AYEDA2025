

#include<iostream>
#include<vector>
#include<string>
#include<fstream>
#include<algorithm>

#include "Sequences.h"
#include "SortMethod.h"
#include "SortMethodTrace.h"

#include "Alumno.h"
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
  int size = 8;

  StaticSequence<Alumno>* sequence = new StaticSequence<Alumno>(size);
  //meter 8 nif 
  //sequence -> fillRandom();
  //debe de crearse un puntero a la clase correspondiente según el método de ordenación que se haya pasado por parámetro
  //rellena la secuancia con 8 alumnos sin ser manual
  sequence -> fillFromFile("alumnos"); //rellena la secuencia con 8 alumnos


  //inicializar un vector de 8 personas 
  std::cout << "SORT METHODS" << "          " << "COMPARATIONS" << "          " << "SWAPS" << std::endl;
  std::cout << "---------------------------------------------------------------------" << std::endl;
    SortMethod<Alumno>* sortMethod;
      sortMethod = new SelectionSortMethod<Alumno>(*sequence);
      sortMethod -> Sort();
      std::cout << "SELECTION SORT" << "        " << sortMethod -> GetComparisons() << "                     " << sortMethod -> GetSwaps() << std::endl;
      std::cout << "---------------------------------------------------------------------" << std::endl;
      sequence -> fillFromFile("alumnos"); //rellena la secuencia con 8 alumnos
      sortMethod = new QuickSortMethod<Alumno>(*sequence);
      sortMethod -> Sort();
      std::cout << "QUICK SORT" << "            " << sortMethod -> GetComparisons() << "                     " << sortMethod -> GetSwaps() << std::endl;
      std::cout << "---------------------------------------------------------------------" << std::endl;
      sequence -> fillFromFile("alumnos"); //rellena la secuencia con 8 alumnos

      sortMethod = new HeapSortMethod<Alumno>(*sequence);
      sortMethod -> Sort();
      std::cout << "HEAP SORT" << "            " << sortMethod -> GetComparisons() << "                     " << sortMethod -> GetSwaps() << std::endl;
      std::cout << "---------------------------------------------------------------------" << std::endl;  
  sequence -> fillFromFile("alumnos"); //rellena la secuencia con 8 alumnos
    
      sortMethod = new ShellSortMethod<Alumno>(*sequence, 0.5);
      sortMethod -> Sort();
      std::cout << "SHELL SORT" << "          " << sortMethod -> GetComparisons() << "                     " << sortMethod -> GetSwaps() << std::endl;

  return 0;
}