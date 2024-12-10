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
  
auto isSafe = [](std::vector<int>& levels) {
  bool isIncreasing = true, isDecreasing = true;
  for (int i = 1; i < levels.size(); i++) {
  if (levels[i] <= levels[i - 1] || std::abs(levels[i] - levels[i - 1]) > 3) { 
    std::vector<int> temp1 = levels;
    temp1.erase(temp1.begin() + i);
    std::vector<int> temp2 = levels;
    temp2.erase(temp2.begin() + i - 1);

    std::function<bool(std::vector<int>&)> checkSafety = [&checkSafety](std::vector<int>& vec) -> bool {
      bool inc = true, dec = true;
      for (int j = 1; j < vec.size(); j++) {
        if (vec[j] <= vec[j - 1] || std::abs(vec[j] - vec[j - 1]) > 3) inc = false;
        if (vec[j] >= vec[j - 1] || std::abs(vec[j] - vec[j - 1]) > 3) dec = false;
      }
      return (inc || dec);
    };
    if (checkSafety(temp1) || checkSafety(temp2)) continue;
    isIncreasing = false;
  }
  if (levels[i] >= levels[i - 1] || std::abs(levels[i] - levels[i - 1]) > 3) {
    std::vector<int> temp1 = levels;
    temp1.erase(temp1.begin() + i);
    std::vector<int> temp2 = levels;
    temp2.erase(temp2.begin() + i - 1);

    std::function<bool(std::vector<int>&)> checkSafety = [&checkSafety](std::vector<int>& vec) -> bool {
      bool inc = true, dec = true;
      for (int j = 1; j < vec.size(); j++) {
        if (vec[j] <= vec[j - 1] || std::abs(vec[j] - vec[j - 1]) > 3) inc = false;
        if (vec[j] >= vec[j - 1] || std::abs(vec[j] - vec[j - 1]) > 3) dec = false;
      }
      return (inc || dec);
    };
    if (checkSafety(temp1) || checkSafety(temp2)) continue;
    isDecreasing = false;
    }
  }
  return (isIncreasing || isDecreasing);
};

  for(int i = 0; i < input.size(); i++) if (isSafe(input[i])) safeCounter++;
  std::cout << safeCounter << std::endl;
  return 0;
}

