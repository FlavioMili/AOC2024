#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <stack>

bool isValid(int i, int j, int y, int x, const std::vector<std::string>& input, 
             const std::vector<std::vector<bool>>& visited, char currValue) {
   return i >= 0 && i < y && j >= 0 && j < x && !visited[i][j] && input[i][j] == currValue + 1;
}

void dfs(int startY, int startX, const std::vector<std::string>& input, 
         std::vector<std::vector<bool>>& localVisited, int& nineCount) {
   std::stack<std::pair<int, int>> stack;
   stack.push({startY, startX});
   localVisited[startY][startX] = true;

   while (!stack.empty()) {
      auto [currY, currX] = stack.top();
      stack.pop();
      char currValue = input[currY][currX];

      if (currValue == '9') nineCount++;

      std::vector<std::pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
      for (const auto& [dy, dx] : directions) {
         int newY = currY + dy;
         int newX = currX + dx;

         if (isValid(newY, newX, input.size(), input[0].size(), input, localVisited, currValue)) {
            localVisited[newY][newX] = true;
            stack.push({newY, newX});
         }
      }
   }
}

int main() {
   int res = 0;
   std::ifstream file("input.txt");
   std::vector<std::string> input;
   std::vector<std::pair<int, int>> startCoord;
   std::string line;
   while (std::getline(file, line)) input.push_back(line);

   int y = input.size();
   int x = input[0].size();

   for (int i = 0; i < y; i++) {
      for (int j = 0; j < x; j++) {
         if (input[i][j] == '0') startCoord.push_back({i, j});
      }
   }

   for (auto& zero : startCoord) {
      std::vector<std::vector<bool>> localVisited(y, std::vector<bool>(x, false));
      int nineCount = 0;
      dfs(zero.first, zero.second, input, localVisited, nineCount);
      res += nineCount;
   }

   std::cout << res << "\n";
   return 0;
}
