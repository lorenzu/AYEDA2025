#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <stack>
#include <string>
#include <memory>
#include "BigNumber.h"  // Incluye BigInteger, BigUnsigned, BigRational

using namespace std;

template <unsigned char Base>
class RPNCalculator {
private:
    map<string, unique_ptr<BigNumber<Base>>> board;

    // **Evalúa la expresión en notación polaca inversa**
    BigNumber<Base>* evaluateRPN(const string& expression) {
        stack<BigNumber<Base>*> operands;
        istringstream iss(expression);
        string token;

        while (iss >> token) {
            if (board.find(token) != board.end()) {
                operands.push(board[token].get());  // Usa el puntero almacenado
            } else if (isOperator(token)) {
                if (operands.size() < 2) {
                    cerr << "Error: Expresión inválida." << endl;
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
                } catch (exception& e) {
                    cerr << "Error en operación: " << e.what() << endl;
                    result = new BigInteger<Base>("0");
                }

                operands.push(result);
            } else {
                cerr << "Error: Token desconocido -> " << token << endl;
                return new BigInteger<Base>("0");
            }
        }

        if (operands.size() != 1) {
            cerr << "Error: Expresión inválida." << endl;
            return new BigInteger<Base>("0");
        }

        return operands.top();
    }

    bool isOperator(const string& token) {
        return (token == "+" || token == "-" || token == "*" || token == "/");
    }

public:
    void processFile(const string& inputFile, const string& outputFile) {
        ifstream in(inputFile);
        ofstream out(outputFile);

        if (!in || !out) {
            cerr << "Error al abrir los archivos." << endl;
            return;
        }

        string line;
        std::string base;

        while (getline(in, line)) {
            istringstream iss(line);
            string label, op, value;
            iss >> label >> op;

            if (label == "Base" && op == "=") {
                iss >> base;
            } else if (op == "=") {
                iss >> value;
                board[label] = unique_ptr<BigNumber<Base>>(BigNumber<Base>::create(value.c_str()));
                out << label << " = " << *board[label] << endl;
            } else if (op == "?") {
                getline(iss, value);
                BigNumber<Base>* result = evaluateRPN(value);
                board[label] = unique_ptr<BigNumber<Base>>(result);
                out << label << " = " << *board[label] << endl;
            }
        }

        in.close();
        out.close();
    }
};

int main(int argc, char* argv[]) {

    RPNCalculator<10> calculator;
    //calculator.processFile("./src/ex.txt", "ex_out.txt");
    calculator.processFile("ex.txt", "ex_out.txt");

    return 0;
}
