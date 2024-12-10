#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

int main(int argc, char* argv[]){
  int safeCounter = 0;
  std::ifstream file(argv[1]);
  std::string line;
  std::vector<std::vector<int> > input;
  while (std::getline(file, line)){
    std::vector<int> local;
    std::istringstream stream(line);
    int a;
    while(stream >> a) local.push_back(a);
    input.push_back(local);
  }
  
  auto isSafe = [](std::vector<int>& levels){
    bool isIncreasing = true, isDecreasing = true;
    for (int i = 1; i < levels.size(); i++) {
      if (levels[i] <= levels[i - 1] || abs(levels[i] - levels[i - 1]) > 3) isIncreasing = false;
      if (levels[i] >= levels[i - 1] || abs(levels[i] - levels[i - 1]) > 3) isDecreasing = false; 
    }
    return (isIncreasing || isDecreasing);
  };

  for(int i = 0; i < input.size(); i++) if (isSafe(input[i])) safeCounter++;
  std::cout << safeCounter << std::endl;
  return 0;
}

