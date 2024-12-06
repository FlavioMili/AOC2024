#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <functional>

int main() {
   std::vector<std::string> grid;
   std::ifstream file("input.txt");
   std::string line;
   int c = 0;
   int x, y;

   while (std::getline(file, line)) {
      size_t pos = line.find('^');
      if (pos != std::string::npos) {
         y = pos;
         x = c;
      }
      grid.push_back(line);
      c++;
   }

   int max_row = grid.size() - 1;
   int max_col = grid[0].size() - 1;
   const int directions[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
   int rotation = 0;

   auto hash = [](const std::pair<int, int>& p) {
      return std::hash<int>{}(p.first) ^ (std::hash<int>{}(p.second) << 1);
   };

   size_t loop_count = 0;

   for (int i = 0; i <= max_row; i++) {
      for (int j = 0; j <= max_col; j++) {
         if (grid[i][j] == '.') {
            grid[i][j] = '#';
            int gx = x, gy = y;
            int cur_rotation = rotation;
            std::unordered_map<std::pair<int, int>, int, decltype(hash)> visited(4520, hash);

            bool loop_found = false;

            while (gx >= 0 && gx <= max_row && gy >= 0 && gy <= max_col) {
               int dx = gx + directions[cur_rotation % 4][0];
               int dy = gy + directions[cur_rotation % 4][1];

               if (grid[dx][dy] == '#') cur_rotation++;
               else {
                  gx = dx;
                  gy = dy;
                  std::pair<int, int> coord = {gx, gy};
                  visited[coord]++;
                  if (visited[coord] > 4) {
                     loop_found = true;
                     break;
                  }
               }
            }
            if (loop_found) loop_count++;
            grid[i][j] = '.';
         }
      }
   }

   std::cout << loop_count << "\n";
   return 0;
}
