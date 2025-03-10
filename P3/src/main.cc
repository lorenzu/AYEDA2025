#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
//#include "BigR.h" // Incluye la cabecera de BigRational
#include "BigNumber.h" // Incluye la cabecera de BigNumber





int main() {
    //readAndProcessFile("./src/ex.txt");
    //readAndProcessFile("ex.txt");
    BigNumber<10>* n1 = BigNumber<10>::create("123i");

    std::cout << *n1 << std::endl;



    return 0;
}
