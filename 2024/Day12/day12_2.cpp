#include <fstream>
#include <functional>
#include <iostream>
#include <string>
#include <vector>

const std::vector<std::pair<int, int>> directions{ {-1, 0 }, {0,  1 }, {1,  0 }, {0,  -1} };


int main() {
   long long res = 0;
   std::string line;
   std::ifstream file("input.txt");
   std::vector<std::string> grid;
   while (file >> line)  grid.push_back(line);

   int n = grid.size();
   int m = grid[0].size();
   auto isValid = [&](int x, int y) { return x >= 0 && y >= 0 && x < n && y < m; };

   std::vector<std::vector<int>> visited(n, std::vector<int>(m));

   std::function<std::pair<int,int>(int, int)> DFS = [&] (int x, int y) -> std::pair<int, int> {
      int area = 1, corners = 0;

      for (int i = 0; i < 4; i++) {
         int nx1 = x + directions[i].first,
         ny1 = y + directions[i].second;
         int nx2 = x + directions[(i + 1) % 4].first,
         ny2 = y + directions[(i + 1) % 4].second;

         int nxdiagonal = x + directions[i].first + directions[(i + 1) % 4].first,
         nydiagonal = y + directions[i].second + directions[(i + 1) % 4].second;

         if (((!isValid(nx1, ny1) || grid[nx1][ny1] != grid[x][y]) &&
            (!isValid(nx2, ny2) || grid[nx2][ny2] != grid[x][y])) ||
            (isValid(nx1, ny1) && grid[nx1][ny1] == grid[x][y] && isValid(nx2, ny2) &&
            grid[nx2][ny2] == grid[x][y] &&
            grid[nxdiagonal][nydiagonal] != grid[x][y])) {
            ++corners;
         }
      }

      for (auto [dx, dy] : directions) {
         int nx = x + dx, ny = y + dy;

         if (nx >= 0 && ny >= 0 && nx < n && ny < m &&
            grid[nx][ny] == grid[x][y]) {
            if (!visited[nx][ny]) {
               visited[nx][ny] = true;
               auto [ar, cor] = DFS(nx, ny);
               area += ar;
               corners += cor;
            }
         }
      }
      return {area, corners};
   };

   for (int i = 0; i < n; i++){
      for (int j = 0; j < m; j++){
         if (!visited[i][j]) {
            visited[i][j] = 1;
            auto [area, corners] = DFS(i, j);
            res += area * corners;
         }
      }
   }
   std::cout << res << "\n";
   return 0;
}
