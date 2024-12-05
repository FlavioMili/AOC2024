#include <fstream>
#include <iostream>
#include <ostream>
#include <sstream>
#include <string>
#include <utility>
#include <vector>
int main(){
  std::ifstream file("input.txt");
  std::vector<std::pair<int, int>> pagesOrder;
  std::vector<std::vector<int>> outputPages;
  std::vector<std::pair<int, int>>* currentSection = &pagesOrder;
  std::string line;
  int res = 0;

  while (std::getline(file, line)) {
    if (line.empty()) {
      currentSection = nullptr;
      continue;
    }
    std::stringstream ss(line);
    std::string token;

    if (currentSection) {
      std::pair<int, int> orderPair;
      std::getline(ss, token, '|');
      orderPair.first = std::stoi(token);
      std::getline(ss, token, '|');
      orderPair.second = std::stoi(token);
      currentSection->push_back(orderPair);
    }
    else {
      std::vector<int> nums;
      while(std::getline(ss, token, ',')) nums.push_back(std::stoi(token));
      outputPages.push_back(nums);
    }
  }
  file.close();

  for (int i = 0; i < outputPages.size(); i++){
    bool check = true;
    for (int j = 1; j < outputPages[i].size(); j++){
      std::pair<int, int> target = {outputPages[i][j-1], outputPages[i][j]};
      if (std::find(pagesOrder.begin(), pagesOrder.end(), target) == pagesOrder.end()){
        check = false;
        break;
      }
    }
    if (check) res += outputPages[i][outputPages[i].size()/2];
  }

  std::cout << res << std::endl;
  return 0;
}
