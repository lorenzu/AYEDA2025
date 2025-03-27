#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <stack>
#include <string>
#include <memory>
#include "BigNumber.h"  // Incluye BigInteger, BigUnsigned, BigRational


// comparar dos bignumber y devolver el mayor menos el menor

template <unsigned char Base>
BigNumber<Base>* bign_compare(BigNumber<Base>* a, BigNumber<Base>* b) {
    if (a > b) {
        return &a->subtract(*b);
    } else {
        return &b->subtract(*a);
    }
}

template <unsigned char Base>
class RPNCalculator {
private:
    std::map<std::string, std::unique_ptr<BigNumber<Base>>> board;

    BigNumber<Base>* evaluateRPN(const std::string& expression) {
        std::stack<BigNumber<Base>*> operands;
        std::istringstream iss(expression);
        std::string token;

        while (iss >> token) {
            if (board.find(token) != board.end()) {
                operands.push(board[token].get());
            } else if (isOperator(token)) {
                if (operands.size() < 2) {
                    std::cerr << "Error: Expresión inválida." << std::endl;
                    return new BigInteger<Base>("0");
                }
                BigNumber<Base>* b = operands.top(); operands.pop();
                BigNumber<Base>* a = operands.top(); operands.pop();

                BigNumber<Base>* result = nullptr;
                try {
                    if (token == "+") result = &(a->add(*b));
                    else if (token == "-") result = &(a->subtract(*b));
                    else if (token == "*") result = &(a->multiply(*b));
                    else if (token == "/") result = &(a->divide(*b));
                } catch (std::exception& e) {
                    std::cerr << "Error en operación: " << e.what() << std::endl;
                    result = new BigInteger<Base>("0");
                }

                operands.push(result);
            } else {
                std::cerr << "Error: Token desconocido -> " << token << std::endl;
                return new BigInteger<Base>("0");
            }
        }

        if (operands.size() != 1) {
            std::cerr << "Error: Expresión inválida." << std::endl;
            return new BigInteger<Base>("0");
        }

        return operands.top();
    }

    bool isOperator(const std::string& token) {
        return (token == "+" || token == "-" || token == "*" || token == "/");
    }

public:
    std::map<std::string, std::unique_ptr<BigNumber<Base>>>& getBoard() {
        return board;
    }

    BigNumber<Base>* evaluateExpression(const std::string& expression) {
        return evaluateRPN(expression);
    }
};

// **Declaración de la función antes de su uso**
template <unsigned char Base>
void processFileWithCalculator(std::ifstream& in, std::ofstream& out, RPNCalculator<Base>& calculator);

void processFile(const std::string& inputFile, const std::string& outputFile) {
    std::ifstream in(inputFile);
    std::ofstream out(outputFile);

    if (!in || !out) {
        std::cerr << "Error al abrir los archivos." << std::endl;
        return;
    }

    std::string line;
    int base = 10;

    // **Buscar la base en el archivo**
    while (std::getline(in, line)) {
        std::istringstream iss(line);
        std::string label, op, value;
        iss >> label >> op;

        if (label == "Base" && op == "=") {
            iss >> base;
            break;
        }
    }

    if (base < 2 || base > 36) {
        std::cerr << "Error: Base no válida (" << base << "). Debe estar entre 2 y 36." << std::endl;
        return;
    }

    RPNCalculator<10>* calculator10 = nullptr;
    RPNCalculator<16>* calculator16 = nullptr;
    RPNCalculator<8>* calculator8 = nullptr;

    if (base == 10) {
        calculator10 = new RPNCalculator<10>();
        processFileWithCalculator(in, out, *calculator10);
        delete calculator10;
    } else if (base == 16) {
        calculator16 = new RPNCalculator<16>();
        processFileWithCalculator(in, out, *calculator16);
        delete calculator16;
    } else if (base == 8) {
        calculator8 = new RPNCalculator<8>();
        processFileWithCalculator(in, out, *calculator8);
        delete calculator8;
    } else {
        std::cerr << "Error: Base no soportada." << std::endl;
    }
}

// **Procesar el archivo con la calculadora ya creada**
template <unsigned char Base>
void processFileWithCalculator(std::ifstream& in, std::ofstream& out, RPNCalculator<Base>& calculator) {
    std::map<std::string, std::unique_ptr<BigNumber<Base>>>& board = calculator.getBoard();
    std::string line;
    out << "Base = " << static_cast<int>(Base) << std::endl;

    while (std::getline(in, line)) {
        std::istringstream iss(line);
        std::string label, op, value;
        iss >> label >> op;

        if (op == "=") {
            iss >> value;
            board[label] = std::unique_ptr<BigNumber<Base>>(BigNumber<Base>::create(value.c_str()));
            out << label << " = " << *board[label] << std::endl;
        } else if (op == "?") {
            std::getline(iss, value);
            BigNumber<Base>* result = calculator.evaluateExpression(value);
            board[label] = std::unique_ptr<BigNumber<Base>>(result);
            out << label << " = " << *board[label] << std::endl;
        }
    }
}

int main(int argc, char* argv[]) {
    processFile("./src/ex.txt", "ex_out.txt");
    //processFile("ex.txt", "ex_out.txt");
    //bignumber es la clase base
    /*
    BigNumber<10> *a = new BigInteger<10>("123");
    BigNumber<10> *b = new BigRational<10>("456", "789");
    BigNumber<10> *c = new BigUnsigned<10>("789");

    std::cout << *a << std::endl;
    std::cout << *b << std::endl;

    //como puedo sumar a y b
    BigNumber<10> *d = &a->add(*b);
    BigNumber<10> *f = &a->add(*b);
    BigNumber<10> *e = &a->add(*c);

    std::cout << *d << std::endl;
    std::cout << *f << std::endl; 
    std::cout << *e << std::endl;
    */

    /// TO DO COMPROBAR LOS DYNAMIC CASTING EN BIG INT MAS QUE SEA



    return 0;
}
