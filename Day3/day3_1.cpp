#include <_stdio.h>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <ostream>
#include <regex>
#include <string>
int main(int argc, char* argv[]){
  std::string input;
  std::ifstream file(argv[1]);
  long long res = 0;

  std::regex pattern(R"(mul\((\d{1,3}),(\d{1,3})\))");

  while(getline(file, input)){
    auto it = input.cbegin();
    std::smatch match;
    while(std::regex_search(it, input.cend(), match, pattern)){
      int x = std::stoi(match[1].str());
      int y = std::stoi(match[2].str());
      res += x*y;
      it = match.suffix().first;
    }
  }
  std::cout << res << std::endl;
  return 0;
}
