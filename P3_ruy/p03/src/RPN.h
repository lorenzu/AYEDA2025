#ifndef RPN_H_
#define RPN_H_

#include <iostream>
#include <set>
#include <sstream>
#include <stack>
#include <unordered_map>
#include <vector>

#include "Number.h"

class RPN {
 public:
  RPN(std::string, std::unordered_map<std::string, Number*>&);
  Number* operate();

  bool is_operator(char operato);

 private:
  std::unordered_map<std::string, Number*>& numbers_;
  std::string statement_;
  std::set<char> operators_ = {'+', '-', '*', '%', '/', '^'};
};

#endif
