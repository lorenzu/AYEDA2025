#include "functions.h"

std::vector<std::string> split(std::string line) {
  if (line.size() == 0) return {};

  std::stringstream ss(line);
  std::vector<std::string> out;
  std::string temp;

  while (!ss.eof()) {
    ss >> temp;
    out.push_back(temp);
  }

  return out;
}