#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <stack>
#include <string>
#include <memory>
#include "BigNumber.h"  // Incluye BigInteger, BigUnsigned, BigRational

// **Clase RPNCalculator**
template <unsigned char Base>
class RPNCalculator {
private:
    std::map<std::string, std::unique_ptr<BigNumber<Base>>> board;

    // **Evalúa la expresión en notación polaca inversa**
    BigNumber<Base>* evaluateRPN(const std::string& expression) {
        std::stack<BigNumber<Base>*> operands;
        std::istringstream iss(expression);
        std::string token;

        while (iss >> token) {
            if (board.find(token) != board.end()) {
                operands.push(board[token].get());  // Usa el puntero almacenado
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

// **Función para procesar el archivo**
void processFile(const std::string& inputFile, const std::string& outputFile) {
    std::ifstream in(inputFile);
    std::ofstream out(outputFile);

    if (!in || !out) {
        std::cerr << "Error al abrir los archivos." << std::endl;
        return;
    }

    std::string line;
    int base = 10;  // Base predeterminada en caso de que no se especifique en el archivo

    // **Leer la base del archivo**
    while (std::getline(in, line)) {
        std::istringstream iss(line);
        std::string label, op, value;
        iss >> label >> op;

        if (label == "Base" && op == "=") {
            iss >> base;
            break;  // Se encontró la base, salir del bucle
        }
    }

    if (base < 2 || base > 36) {
        std::cerr << "Error: Base no válida (" << base << "). Debe estar entre 2 y 36." << std::endl;
        return;
    }

    // **Crear la calculadora con la base leída**
    if (base == 10) {
        auto calculator = std::make_unique<RPNCalculator<10>>();
        processFileWithCalculator(in, out, *calculator);
    } else if (base == 16) {
        auto calculator = std::make_unique<RPNCalculator<16>>();
        processFileWithCalculator(in, out, *calculator);
    } else if (base == 8) {
        auto calculator = std::make_unique<RPNCalculator<8>>();
        processFileWithCalculator(in, out, *calculator);
    } else {
        std::cerr << "Error: Base no soportada." << std::endl;
    }

    in.close();
    out.close();
}

// **Función auxiliar para procesar el archivo con la calculadora correcta**
template <unsigned char Base>
void processFileWithCalculator(std::ifstream& in, std::ofstream& out, RPNCalculator<Base>& calculator) {
    std::map<std::string, std::unique_ptr<BigNumber<Base>>>& board = calculator.getBoard();
    std::string line;

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


