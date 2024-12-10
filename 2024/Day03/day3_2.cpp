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
  std::regex do_pattern(R"(do\(\))");
  std::regex dont_pattern(R"(don't\(\))");
  bool mul = true;


  while(getline(file, input)){
    auto it = input.cbegin();
    while (it != input.cend()){
      std::smatch match;
      if (mul && std::regex_search(it, input.cend(), match, dont_pattern)) {
        mul = false;
        it = match.suffix().first;
      }
      else if (!mul && std::regex_search(it, input.cend(), match, do_pattern)) {
        it = match.suffix().first;
        mul = true;
      }
      else if (mul && std::regex_search(it, input.cend(), match, pattern)){
            int x = std::stoi(match[1].str());
            int y = std::stoi(match[2].str());
            res += x*y;
            std::cout << res << std::endl;
            it = match.suffix().first;
      } 
      else it++;
    }
  }

  std::cout << res << std::endl;
  return 0;
}
