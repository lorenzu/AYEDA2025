#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include "BigNumber.h" // Incluye la cabecera de BigNumber
#include "BigR.h" // Incluye la cabecera de BigRational

int main() {
    constexpr unsigned char Base = 10;

    // Crear un BigInteger a través de la fábrica
    BigNumber<Base>* bigNumInt = BigNumber<Base>::create("42u");
    std::cout << "BigNumber (BigUnsigned): " << *bigNumInt << std::endl;

    // Liberar memoria
    delete bigNumInt;

    return 0;
}