#include <fstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <utility>
#include <iostream>

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
            int antinode1_x = x1 - dx, antinode1_y = y1 - dy;
            int antinode2_x = x2 + dx, antinode2_y = y2 + dy;
            if (antinode1_x >= 0 && antinode1_x < max_y && antinode1_y >= 0 && antinode1_y < max_x) {
               antinodes.insert({antinode1_x, antinode1_y});
            }
            if (antinode2_x >= 0 && antinode2_x < max_y && antinode2_y >= 0 && antinode2_y < max_x) {
               antinodes.insert({antinode2_x, antinode2_y});
            }
         }
      }
   }

   std::cout << antinodes.size() << std::endl;

   return 0;
}
