#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <set>
#include <tuple>

bool isValidMove(int y, int x, int height, int width, 
                 const std::vector<std::vector<bool>>& visited) {
   return y >= 0 && y < height && x >= 0 && x < width && !visited[y][x];
}

int findDistinctTrails(int startY, int startX, const 
                       std::vector<std::string>& input, int height, int width) {
   std::set<std::vector<std::pair<int, int>>> distinctTrails;
   std::vector<std::pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
   std::queue<std::tuple<int, int, std::vector<std::vector<bool>>, std::vector<std::pair<int, int>>>> queue;

   std::vector<std::vector<bool>> initialVisited(height, std::vector<bool>(width, false));
   initialVisited[startY][startX] = true;
   queue.push({startY, startX, initialVisited, {{startY, startX}}});

   while (!queue.empty()) {
      auto [currY, currX, visited, currentTrail] = queue.front();
      queue.pop();

      if (input[currY][currX] == '9') {
         distinctTrails.insert(currentTrail);
         continue;
      }

      for (const auto& [dy, dx] : directions) {
         int newY = currY + dy;
         int newX = currX + dx;

         if (isValidMove(newY, newX, height, width, visited) && 
            input[newY][newX] == input[currY][currX] + 1) {
            visited[newY][newX] = true;
            auto newTrail = currentTrail;
            newTrail.push_back({newY, newX});
            queue.push({newY, newX, visited, newTrail});
         }
      }
   }

   return distinctTrails.size();
}

int main() {
   int res = 0;
   std::ifstream file("input.txt");
   std::vector<std::string> input;
   std::string line;
   while (std::getline(file, line)) input.push_back(line);
   int height = input.size();
   int width = input[0].size();

   for (int y = 0; y < height; ++y) {
      for (int x = 0; x < width; ++x) {
         if (input[y][x] == '0') res += findDistinctTrails(y, x, input, height, width);
      }
   }
   std::cout << res << std::endl;
   return 0;
}
