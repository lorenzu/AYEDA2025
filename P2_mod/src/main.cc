#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include "BigR.h" // Incluye la cabecera de BigRational

//sum de bigrational entero es decir que /1
template <unsigned char Base>
BigRational<Base> sum(std::vector<BigRational<Base>> vec){
  BigRational<Base> sum(0);
  for(auto i : vec){
    if (i.GetDen() == 1){
      sum = sum + i;
    }
  }
  return sum;
  
}

void readAndProcessFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file" << std::endl;
        return;
    }

    std::string line;
    int base = 10;
    std::string n1_str, n2_str;

    while (std::getline(file, line)) {
        if (line.find("Base") != std::string::npos) {
            base = std::stoi(line.substr(line.find('=') + 1));
        } else if (line.find("N1") != std::string::npos) {
            n1_str = line.substr(line.find('=') + 1);
        } else if (line.find("N2") != std::string::npos) {
            n2_str = line.substr(line.find('=') + 1);
        }
    }

    file.close();

    // **Paso 1: Extraer numerador y denominador**
    std::string n1_num_str, n1_den_str, n2_num_str, n2_den_str;
    std::istringstream n1_stream(n1_str);
    std::istringstream n2_stream(n2_str);

    std::getline(n1_stream, n1_num_str, '/');
    std::getline(n1_stream, n1_den_str);
    
    std::getline(n2_stream, n2_num_str, '/');
    std::getline(n2_stream, n2_den_str);

    if(base == 10){
    // **Paso 2: Convertir a BigInteger y BigUnsigned**
    BigInteger<10> n1_num(n1_num_str.c_str());
    BigUnsigned<10> n1_den(n1_den_str.c_str()); // Puede ser negativo

    BigInteger<10> n2_num(n2_num_str.c_str());
    BigUnsigned<10> n2_den(n2_den_str.c_str()); // Puede ser negativo

    // **Paso 4: Crear BigRational**
    BigRational<10> n1(n1_num, n1_den);
    BigRational<10> n2(n2_num, n2_den);

    // **Paso 5: Operaciones**
    BigRational<10> sum = n1 + n2;
    BigRational<10> diff = n1 - n2;

    std::cout << "N1: " << n1 << std::endl;
    std::cout << "N2: " << n2 << std::endl;
    std::cout << "Sum: " << sum << std::endl;
    std::cout << "Difference: " << diff << std::endl;
    } else if(base == 2){
    // **Paso 2: Convertir a BigInteger y BigUnsigned**
    BigInteger<2> n1_num(n1_num_str.c_str());
    BigUnsigned<2> n1_den(n1_den_str.c_str()); // Puede ser negativo


    BigInteger<2> n2_num(n2_num_str.c_str());
    BigUnsigned<2> n2_den(n2_den_str.c_str()); // Puede ser negativo

    // **Paso 4: Crear BigRational**
    BigRational<2> n1(n1_num, n1_den);
    BigRational<2> n2(n2_num, n2_den);

    // **Paso 5: Operaciones**
    BigRational<2> sum = n1 + n2;
    BigRational<2> diff = n1 - n2;

    std::cout << "N1: " << n1 << std::endl;
    std::cout << "N2: " << n2 << std::endl;
    std::cout << "Sum: " << sum << std::endl;
    std::cout << "Difference: " << diff << std::endl;
  } else if(base == 16){
    // **Paso 2: Convertir a BigInteger y BigUnsigned**
    BigInteger<16> n1_num(n1_num_str.c_str());
    BigUnsigned<16> n1_den(n1_den_str.c_str()); // Puede ser negativo

    BigInteger<16> n2_num(n2_num_str.c_str());
    BigUnsigned<16> n2_den(n2_den_str.c_str()); // Puede ser negativo

    // **Paso 4: Crear BigRational**
    BigRational<16> n1(n1_num, n1_den);
    BigRational<16> n2(n2_num, n2_den);

    // **Paso 5: Operaciones**
    BigRational<16> sum = n1 + n2;
    BigRational<16> diff = n1 - n2;

    std::cout << "N1: " << n1 << std::endl;
    std::cout << "N2: " << n2 << std::endl;
    std::cout << "Sum: " << sum << std::endl;
    std::cout << "Difference: " << diff << std::endl;
  } else if(base == 8){
    // **Paso 2: Convertir a BigInteger y BigUnsigned**
    BigInteger<8> n1_num(n1_num_str.c_str());
    BigUnsigned<8> n1_den(n1_den_str.c_str()); // Puede ser negativo

    BigInteger<8> n2_num(n2_num_str.c_str());
    BigUnsigned<8> n2_den(n2_den_str.c_str()); // Puede ser negativo

    // **Paso 4: Crear BigRational**
    BigRational<8> n1(n1_num, n1_den);
    BigRational<8> n2(n2_num, n2_den);

    // **Paso 5: Operaciones**
    BigRational<8> sum = n1 + n2;
    BigRational<8> diff = n1 - n2;

    std::cout << "N1: " << n1 << std::endl;
    std::cout << "N2: " << n2 << std::endl;
    std::cout << "Sum: " << sum << std::endl;
    std::cout << "Difference: " << diff << std::endl;
  }
 
    
}

int main() {
    //readAndProcessFile("./src/ex.txt");
    //readAndProcessFile("ex.txt");

    std::vector<BigRational<10>> vec;
    BigRational<10> num1 (30);
    BigRational<10> num2 (30);
    BigRational<10> num3 (30);
    BigRational<10> num4 (30, 4);

    vec.push_back(num1);
    vec.push_back(num2);
    vec.push_back(num3);

    
    std::cout << sum(vec) << std::endl;


    return 0;
}
