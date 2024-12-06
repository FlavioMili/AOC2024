#include <fstream>
#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>
#include <functional>
int main(){
   std::vector<std::string> grid;
   std::ifstream file("input.txt");
   std::string line;
   int c = 0;
   int x;
   int y;
   while(std::getline(file, line)){
      size_t pos = line.find('^');
      if (pos != std::string::npos){
         y = pos;
         x = c;
      }
      c++;
      grid.push_back(line);
   }
   int max_row = grid.size() - 1;
   int max_col = grid[0].size() - 1;
   const int directions[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
   int rotation = 0;
   auto pair_hash = [](const std::pair<int, int>& p) {
      return std::hash<int>{}(p.first) ^ (std::hash<int>{}(p.second) << 1);
   };

   std::unordered_set<std::pair<int, int>, decltype(pair_hash)> visited(4520, pair_hash);

   while(y != 0 && x != 0 && x < max_row && y < max_col){
      int dx = x + directions[rotation % 4][0];
      int dy = y + directions[rotation % 4][1]; 
      if (grid[dx][dy] == '#') rotation++;
      else{
         x = dx;
         y = dy;
         std::pair<int, int> coord = {x, y};
         if (visited.find(coord) == visited.end()) 
            visited.insert(coord);
      }
   }

   std::cout << visited.size() << "\n";
   return 0;
}
