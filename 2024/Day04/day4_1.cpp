#include <fstream>
#include <iostream>
#include <string>
#include <vector>
int main(){
  // Reading input and accessing it as a matrix
  std::ifstream file("input.txt");
  std::vector<std::vector<char> > input;
  std::string line;
  while(std::getline(file, line)){
    std::vector<char> lines(line.begin(), line.end());
    input.push_back(lines);
  }
  file.close();

  int rows = input.size(), cols = input[0].size();
  int res = 0;
  std::string word = "XMAS";
  int wordLength = word.size();

  const int directions[8][2] = {
    {0, 1},   // Right
    {0, -1},  // Left
    {1, 0},   // Down
    {-1, 0},  // Up
    {1, 1},   // Down-Right
    {-1, -1}, // Up-Left
    {1, -1},  // Down-Left
    {-1, 1}   // Up-Right
  };

  auto isWordFound = [&](int x, int y, int dx, int dy) {
    for (int i = 0; i < wordLength; ++i) {
      int nx = x + i * dx, ny = y + i * dy;
      if (nx < 0 || nx >= rows || ny < 0 || ny >= cols || input[nx][ny] != word[i]) return false;
    }
    return true;
  };

  for (int i = 0; i < rows; ++i) 
    for (int j = 0; j < cols; ++j)
      for (const auto& dir : directions) 
        if (isWordFound(i, j, dir[0], dir[1])) res++;

  std::cout << res << std::endl;
  return 0;
}
