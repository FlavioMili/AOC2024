#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <utility>
#include <vector>
#include <algorithm>

int main() {
    std::ifstream file("input.txt");
    std::vector<std::pair<int, int>> pagesOrder;
    std::vector<std::vector<int>> outputPages;
    std::vector<std::pair<int, int>>* currentSection = &pagesOrder;
    std::string line;
    int res = 0;

    // Parse the input file
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
      } else {
        std::vector<int> nums;
        while (std::getline(ss, token, ',')) nums.push_back(std::stoi(token));
        outputPages.push_back(nums);
      }
    }
    file.close();

    auto isOrdered = [&](const std::vector<int>& sequence) {
      for (size_t i = 1; i < sequence.size(); i++) {
      std::pair<int, int> target = {sequence[i - 1], sequence[i]};
      if (std::find(pagesOrder.begin(), pagesOrder.end(), target) == pagesOrder.end()) return false;
      }
      return true;
    };

    for (int i = 0; i < outputPages.size(); i++) {
      bool fixed = false;
      while (!isOrdered(outputPages[i])) {
        for (int j = 1; j < outputPages[i].size(); j++) {
          std::pair<int, int> target = {outputPages[i][j - 1], outputPages[i][j]};
            if (std::find(pagesOrder.begin(), pagesOrder.end(), target) == pagesOrder.end()) {
              std::swap(outputPages[i][j - 1], outputPages[i][j]);
              fixed = true;
              break;
            }
        }
      }
      if (fixed) res += outputPages[i][outputPages[i].size() / 2];
    }

    std::cout << res << std::endl;
    return 0;
}
