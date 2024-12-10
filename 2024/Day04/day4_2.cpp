#include <fstream>
#include <iostream>
#include <string>
#include <vector>
int main(){
  std::ifstream file("input.txt");
  std::vector<std::string> input;
  std::string line;
  while(std::getline(file, line)) input.push_back(line);
  file.close();

  int rows = input.size(), cols = input[0].size();
  int res = 0;

  for (int x = 1; x < rows-1; x++) {
    for (int y = 1; y < cols-1; y++) {
      if (input[x][y] == 'A' && 
        input[x-1][y-1] + input[x+1][y+1] == 160 &&
        input[x-1][y+1] + input[x+1][y-1] == 160) res++;
    }
  }
  std::cout << res << std::endl;
  return 0;
}
