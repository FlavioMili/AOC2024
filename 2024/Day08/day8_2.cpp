#include <fstream>
#include <vector>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <iostream>
#include <utility>

int main() {
   std::ifstream file("input.txt");
   std::vector<std::string> grid;
   std::string line;
   int max_y = 0;
   while (std::getline(file, line)) {
      grid.push_back(line);
      max_y++;
   }
   int max_x = grid[0].size();

   std::unordered_map<char, std::vector<std::pair<int, int>>> antennas;
   for (int i = 0; i < max_y; i++) {
      for (int j = 0; j < max_x; j++) {
         if (grid[i][j] != '.') antennas[grid[i][j]].push_back({i, j});
      }
   }

   auto hash_pair = [](const std::pair<int, int>& p) {
      return std::hash<int>()(p.first) ^ (std::hash<int>()(p.second) << 1);
   };
   std::unordered_set<std::pair<int, int>, decltype(hash_pair)> antinodes(0, hash_pair);

   for (auto& freq : antennas) {
      auto& positions = freq.second;
      for (size_t i = 0; i < positions.size(); i++) {
         for (size_t j = i + 1; j < positions.size(); j++) {
            auto [x1, y1] = positions[i];
            auto [x2, y2] = positions[j];
            int dx = x2 - x1, dy = y2 - y1;

            int nx1 = x1, ny1 = y1;
            while (nx1 >= 0 && nx1 < max_y && ny1 >= 0 && ny1 < max_x) {
               antinodes.insert({nx1, ny1});
               nx1 -= dx; ny1 -= dy;
            }

            int nx2 = x2, ny2 = y2;
            while (nx2 >= 0 && nx2 < max_y && ny2 >= 0 && ny2 < max_x) {
               antinodes.insert({nx2, ny2});
               nx2 += dx; ny2 += dy;
            }
         }
      }
   }

   std::cout << antinodes.size() << std::endl;
   return 0;
}
