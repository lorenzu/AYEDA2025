#include <fstream>
#include <sstream>
#include <unordered_map>
#include <vector>

#include "BigInt.h"
#include "Number.h"
#include "RPN.h"
#include "functions.h"

int main(int argc, char* argv[]) {
  if (argc < 2) {
    std::cerr << "Faltan argumentos" << std::endl;
    return 1;
  }

  std::ifstream ifile(argv[1]);
  std::string line;

  std::unordered_map<std::string, Number*> board;
  std::string out_buff;

  while (getline(ifile, line)) {
    auto spl = split(line);
    std::stringstream ss;
    if (spl.size() == 0) continue;

    if (spl[1][0] == '=') {
      size_t base = stoi(spl[2].substr(0, spl[2].size() - 1));
      board[spl[0]] = Number::create(base, spl[3]);

      ss << spl[0] << " = " << board[spl[0]]->base() << ", " << *board[spl[0]]
         << '\n';
    } else if (spl[1][0] == '?') {
      std::string statement;

      for (int i = 2; i < spl.size(); i++) {
        statement += spl[i];
        if (i + 1 < spl.size()) {
          statement += ' ';
        }
      }

      auto res = RPN(statement, board).operate();
      board[spl[0]] = res;

      ss << spl[0] << " = " << res->base() << ", " << *res << '\n';
    } else
      throw BigIntBadDigit();

    out_buff += ss.str();
    std::cout << ss.str();
  }
  ifile.close();

  std::ofstream ofile(strcat(argv[1], ".out"));
  ofile << out_buff;
  ofile.close();

  for (auto& [key, value] : board) {
    delete value;
  }

  return 0;
}
