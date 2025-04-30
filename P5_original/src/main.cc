/**
 * @file main.cc
 * @author ALBA PÉREZ RODRÍGUEZ
 * @version 0.1
 * @date 2024-03-25
 * @brief Programa principal donde se hace uso de las funciones auxiliares.
 * Se encarga de ordenar una secuencia de elementos utilizando diferentes métodos de ordenación.
 * Se hace uso de las funciones auxiliares para el manejo de la línea de comandos.
 */

 #include <iostream>
 #include <string>
 #include <iomanip>
 #include <sstream>
 #include <fstream>
 
 #include "Sequence.h"
 #include "SortMethod.h"
 #include "NIF.h"
 
 // macros de colores
 #define RED "\033[31m"
 #define GREEN "\033[32m"
 #define RESET "\033[0m"
 
 struct Options {
  unsigned int sequenceSize;
  std::string ordenationType;
  std::string introducingData;
  bool trace = false;
  std::string fileName;
};

/**
 * @brief Funcion que imprime un mensaje rodeado de 
 * asteriscos en forma de caja. La utilizaremos para mostrar
 * mensajes de error o información.
 * @param message mensaje que se quiere mostrar en la caja.
 */
void PrintBox(const std::string& message) {
  int length = message.length();
  std::cout << std::string(length + 4, '*') << std::endl;
  std::cout << "* " << message << " *" << std::endl;
  std::cout << std::string(length + 4, '*') << std::endl;
}

/**
 * @brief Funcion que muestra el uso del programa.
 * Si no se han introducido argumentos, se muestra un mensaje de error. Las opciones -h y --help
 * muestran el modo de uso del programa.
 * 1. La opcion  -size <s> : Tamaño de la secuencia (s) obligatorio
 * 2. La opcion  -ord <m> : Código que identifica un método de ordenación (m) obligatorio
 * 3. La opcion  -init <i> : Forma de introducir los datos de la secuencia
 * 4. La opcion  -trace <y|n> : Indica si se muestra o no la traza durante la ejecución
 * @param argc número de argumentos pasados por línea de comandos.
 * @param argv nombre del programa y argumentos pasados por línea de comandos.
 */
void Usage(int argc, char* argv[]) {
  if (argc == 1) {
    PrintBox("No se han introducido argumentos. Pruebe con '" + std::string(argv[0]) + " --help' para más información");
    exit(EXIT_FAILURE);
  }
  if ((argc == 2 && (std::string(argv[1]) == "--help" || std::string(argv[1]) == "-h"))) {
    PrintBox("Funcionalidades del programa:");
    std::cout << "  Este programa se encarga de ordenar una secuencia de elementos utilizando diferentes métodos de ordenación." << std::endl;
    std::cout << std::endl;
    PrintBox("Modo de empleo:");
    std::cout << "  " << argv[0] << " -size <s> -ord <m> -init <i> [f] -trace <y|n>" << std::endl;
    std::cout << "Donde:" << std::endl;
    std::cout << "  -size <s>   : Tamaño de la secuencia (s) obligatorio" << std::endl;
    std::cout << "  -ord <m>    : Código que identifica un método de ordenación (m) obligatorio" << std::endl;
    std::cout << "  -init <i>   : Forma de introducir los datos de la secuencia" << std::endl;
    std::cout << "                i=manual" << std::endl;
    std::cout << "                i=random" << std::endl;
    std::cout << "                i=file f=nombre del fichero de entrada" << std::endl;
    std::cout << "  -trace <y|n>: Indica si se muestra o no la traza durante la ejecución" << std::endl;
    std::cout << std::endl;
    PrintBox("Ejemplos de uso:");
    std::cout << "  " << argv[0] << " -size 100 -ord 1 -init manual -trace y" << std::endl;
    std::cout << "  " << argv[0] << " -size 100 -ord 1 -init file fichero.txt -trace n" << std::endl;
    std::cout << "  " << argv[0] << " -size 100 -ord 1 -init random -trace y" << std::endl;
    exit(EXIT_FAILURE);
  }
}

/**
 * @brief Función que comprueba los argumentos pasados por línea de comandos.
 * Se comprueba que se han pasado los argumentos obligatorios. 
 * Si no se han pasado, se muestra el modo de uso del programa.
 * @param argc Número de argumentos pasados por línea de comandos.
 * @param argv nombre del programa y argumentos pasados por línea de comandos.
 * @return Options retorna una estructura Options que contiene las opciones que se pueden pasar por línea de comandos.
 */
Options ParseArguments(int argc, char* argv[]) {
  Usage(argc, argv);
  Options options;
  for (int i = 1; i < argc; i++) {
    if (std::string(argv[i]) == "-size") {
      if (i + 1 < argc) {
        options.sequenceSize = std::stoi(argv[i + 1]);
      } else {
        std::cerr << "El tamaño de la secuencia es obligatorio" << std::endl;
        exit(EXIT_FAILURE);
      }
    }
    if (std::string(argv[i]) == "-ord") {
      if (i + 1 < argc) {
        options.ordenationType = std::string(argv[i + 1]);
      } else {
        std::cerr << "El método de ordenación es obligatorio" << std::endl;
        exit(EXIT_FAILURE);
      }
    }
    if (std::string(argv[i]) == "-init") {
      if (i + 1 < argc) {
        options.introducingData = std::string(argv[i + 1]);
        if (options.introducingData == "file") {
          if (i + 2 < argc) {
            options.fileName = std::string(argv[i + 2]);
          } else {
            std::cerr << "El nombre del fichero es obligatorio" << std::endl;
            exit(EXIT_FAILURE);
          }
        }
      } else {
        std::cerr << "La forma de introducir los datos es obligatoria" << std::endl;
        exit(EXIT_FAILURE);
      }
    }
    if (std::string(argv[i]) == "-trace") {
      if (i + 1 < argc) {
        if (std::string(argv[i + 1]) == "y") {
          options.trace = true;
        } else if (std::string(argv[i + 1]) == "n") {
          options.trace = false;
        } else {
          std::cerr << "El valor de trace debe ser 'y' o 'n'" << std::endl;
          exit(EXIT_FAILURE);
        }
      } else {
        std::cerr << "El valor de trace es obligatorio" << std::endl;
        exit(EXIT_FAILURE);
      }
    }
  }
  return options;
}

 /**
  * @brief Función principal del programa.
  * Se encarga de comprobar que se han pasado los argumentos necesarios y de parsearlos.
  * Códigos para cada funcion de ordenación:
  * 0. Inserción
  * 1. Selección
  * 2. Burbuja
  * 3. Shake
  * 4. Heap
  * 5. QuickSort
  * 6. MergeSort
  * 7. ShellSort
  * 8. Timsort
  * 9. RadixSort
  * @param argc Número de argumentos pasados por línea de comandos.
  * @param argv nombre del programa y argumentos pasados por línea de comandos.
  * @return int retorna 0 si el programa se ha ejecutado correctamente.
  */
 int main(int argc, char* argv[]) {
   // Comprobamos que se han pasado los argumentos necesarios
   Usage(argc, argv);
   Options options;
   try {
     options = ParseArguments(argc, argv);
   } catch (const std::invalid_argument& e) {
     std::cerr << "Error: " << e.what() << std::endl;
     return EXIT_FAILURE;
   }
   // Mostramos los argumentos pasados por línea de comandos
   std::string border = "\033[1;31m+----------------------------------------+\033[0m"; // Red
   std::cout << border << std::endl;
   std::cout << "\033[1;31m|\033[0m\033[1;32mArgumentos pasados por línea de comandos\033[0m\033[1;31m|\033[0m" << std::endl; // Green text, Red bars
   std::cout << border << std::endl;
   std::cout << "\033[1;31m|\033[0m\033[1;32m Tamaño de la secuencia: \033[0m" << std::setw(14) << std::right << options.sequenceSize << "\033[1;31m |\033[0m" << std::endl; // Green text, Red bars
   std::cout << "\033[1;31m|\033[0m\033[1;32m Tipo de ordenación:     \033[0m" << std::setw(14) << std::right << options.ordenationType << "\033[1;31m |\033[0m" << std::endl; // Green text, Red bars
   std::cout << "\033[1;31m|\033[0m\033[1;32m Introducción de datos:  \033[0m" << std::setw(14) << std::right << options.introducingData << "\033[1;31m |\033[0m" << std::endl; // Green text, Red bars
   std::cout << "\033[1;31m|\033[0m\033[1;32m Mostrar traza:          \033[0m" << std::setw(14) << std::right << options.trace << "\033[1;31m |\033[0m" << std::endl; // Green text, Red bars
   std::cout << "\033[1;31m|\033[0m\033[1;32m Nombre del fichero:     \033[0m" << std::setw(14) << std::right << options.fileName << "\033[1;31m |\033[0m" << std::endl; // Green text, Red bars
   std::cout << border << std::endl;
       
   // dependiendo si es manual, random o fichero se crea la secuencia
   std::fstream file;
   if (options.introducingData == "file") {
     file.open(options.fileName);
     if (!file) {
       std::cerr << "Error: no se pudo abrir el archivo" << std::endl;
       return EXIT_FAILURE;
     }
   }
   // se crea la secuencia a ordenar
   StaticSequence<nif>* sequencia_a_ordenar;
   if (options.introducingData == "manual") {
     std::cout << RED << "\n========================================\n";
     std::cout << "  Se introducen los datos manualmente";
     std::cout << "\n========================================\n\n" << RESET;
     sequencia_a_ordenar = new StaticSequence<nif>(options.sequenceSize, std::string("manual"));
   } else if (options.introducingData == "random") {
     std::cout << RED << "\n========================================\n";
     std::cout << "  Se generan los datos aleatoriamente";
     std::cout << "\n========================================\n\n" << RESET;
     sequencia_a_ordenar = new StaticSequence<nif>(options.sequenceSize, std::string("random"));
   } else if (options.introducingData == "file") {
     std::cout << RED << "\n========================================\n";
     std::cout << "  Se leen los datos del fichero";
     std::cout << "\n========================================\n\n" << RESET;
     sequencia_a_ordenar = new StaticSequence<nif>(options.sequenceSize, file);
   } else {
     std::cerr << "Error: introducción de datos no válida" << std::endl;
     return EXIT_FAILURE;
   }
 
   // dependiendo del tipo de ordenación se llama a la función correspondiente 
   SortMethod<nif>* metodo_ordenacion;
   switch (std::stoi(options.ordenationType)) {
     case 0:
       std::cout << GREEN << "\n========================================================\n";
       std::cout << "Se ha seleccionado el método de ordenación por inserción";
       std::cout << "\n========================================================\n\n" << RESET;
       metodo_ordenacion = new InsertionSortMethod<nif>(options.sequenceSize, sequencia_a_ordenar, options.trace);
       metodo_ordenacion->Sort();
       break;
     case 1:
       std::cout << GREEN << "\n========================================================\n";
       std::cout << "Se ha seleccionado el método de ordenación por shake";
       std::cout << "\n========================================================\n\n" << RESET;
       metodo_ordenacion = new ShakeSortMethod<nif>(options.sequenceSize, sequencia_a_ordenar, options.trace);
       metodo_ordenacion->Sort();
       break;
     case 2:
       std::cout << GREEN << "\n========================================================\n";
       std::cout << "Se ha seleccionado el método de ordenación por heapsort";
       std::cout << "\n========================================================\n\n" << RESET;
       metodo_ordenacion = new HeapSortMethod<nif>(options.sequenceSize, sequencia_a_ordenar, options.trace);
       metodo_ordenacion->Sort();
       break;
     case 3:
       std::cout << GREEN << "\n========================================================\n";
       std::cout << "Se ha seleccionado el método de ordenación por quicksort";
       std::cout << "\n========================================================\n\n" << RESET;
       metodo_ordenacion = new QuickSortMethod<nif>(options.sequenceSize, sequencia_a_ordenar, options.trace);
       metodo_ordenacion->Sort();
       break;
     case 4:
       std::cout << GREEN << "\n========================================================\n";
       std::cout << "Se ha seleccionado el método de ordenación por shellsort";
       std::cout << "\n========================================================\n\n" << RESET;
       metodo_ordenacion = new ShellSortMethod<nif>(options.sequenceSize, sequencia_a_ordenar, options.trace);
       metodo_ordenacion->Sort();
       break;
     default:
       std::cerr << "Error: método de ordenación no válido" << std::endl;
       return EXIT_FAILURE;
   }
   // liberamos la memoria
   delete sequencia_a_ordenar;
   delete metodo_ordenacion;
   return 0;
 }