#include "RPN.h"

#include "functions.h"

RPN::RPN(std::string statement,
         std::unordered_map<std::string, Number*>& numbers)
    : numbers_{numbers}, statement_{statement} {}

Number* RPN::operate() {
  std::stack<Number*> stack;
  auto spl = split(statement_);

  for (const auto el : spl) {
    if (is_operator(el[0])) {
      if (stack.size() < 2) {
        throw std::runtime_error("Missing operands");
      }

      auto op_2 = stack.top();
      stack.pop();
      auto op_1 = stack.top();
      stack.pop();

      switch (el[0]) {
        case '+':
          stack.push(op_1->add(op_2));
          break;
        case '-':
          stack.push(op_1->subtract(op_2));
          break;
        case '/':
          stack.push(op_1->divide(op_2));
          break;
        case '^':
          stack.push(op_1->pow(op_2));
          break;
        case '%':
          stack.push(op_1->module(op_2));
          break;
        case '*':
          stack.push(op_1->multiply(op_2));
          break;
      }
    } else if (numbers_.find(el) != numbers_.end()) {
      stack.push(numbers_[el]);
    } else {
      throw std::runtime_error("Token not recognized");
    }
  }

  if (stack.size() != 1) {
    throw std::runtime_error("Unexpected number of operands");
  }

  return stack.top();
}

bool RPN::is_operator(char operatr) {
  return operators_.find(operatr) != operators_.end();
}
