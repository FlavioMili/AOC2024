#include <fstream>
#include <functional>
#include <iostream>
#include <string>
#include <vector>

const std::vector<std::pair<int, int>> directions = {{0,1}, {0,-1}, {1,0}, {-1,0}};

int main() {
   long long res = 0;
   std::string line;
   std::ifstream file("input.txt");
   std::vector<std::vector<char>> grid;
   while (file >> line)  grid.push_back(std::vector<char>(line.begin(), line.end()));

   int n = grid.size();
   int m = grid[0].size();
   auto isValid = [&](int x, int y) { return x >= 0 && y >= 0 && x < n && y < m; };
   std::vector<std::vector<int>> visited(n, std::vector<int>(m));
   std::function<std::pair<int,int>(int, int)> DFS = [&] (int x, int y) -> std::pair<int, int> {
      int area = 1, perimeter = 0;
      for (auto [dx, dy] : directions) {
         int nx = x + dx, ny = y + dy;

         if (isValid(nx, ny) && grid[nx][ny] == grid[x][y]) {
            if (!visited[nx][ny]) {
               visited[nx][ny] = true;
               auto [ar, peri] = DFS(nx, ny);
               area += ar;
               perimeter += peri;
            }
         }
         else ++perimeter;
      }
      return {area, perimeter};
   };

   for (int i = 0; i < n; i++){
      for (int j = 0; j < m; j++){
         if (!visited[i][j]) {
            visited[i][j] = 1;
            auto [area, perimeter] = DFS(i, j);
            res += area * perimeter;
         }
      }
   }
   std::cout << res << "\n";
   return 0;
}
