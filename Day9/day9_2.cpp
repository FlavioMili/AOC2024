#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

int main() {
   std::ifstream file("input.txt");
   std::string partialWorkingString;
   getline(file, partialWorkingString);

   std::vector<std::pair<int, int>> empties;
   std::vector<std::pair<int, int>> files;
   int index = 0;
   for (size_t i = 0; i < partialWorkingString.size(); ++i) {
      int val = partialWorkingString[i] - '0';
      if (i % 2 == 0) files.push_back({val, index});
      else empties.push_back({val, index});
      index += val;
   }

std::sort(empties.begin(), empties.end(), [](const auto& a, const auto& b) { return a.second < b.second; });

   std::vector<std::pair<int, int>> mergedEmpties;
   for (const auto& empty : empties) {
      if (mergedEmpties.empty() || mergedEmpties.back().second + mergedEmpties.back().first != empty.second) {
         mergedEmpties.push_back(empty);
      } 
      else mergedEmpties.back().first += empty.first;
   }

   uint64_t checksum = 0;
   for (size_t i = files.size() - 1; i < files.size(); i--) {
      auto file = files[i];
      int size = file.first;
      int start = file.second;
      for (auto& empty : mergedEmpties) {
         if (empty.second >= start) break;
         if (empty.first >= size) {
        start = empty.second;
empty.first -= size;
            empty.second += size;
            break;
         }
      }
      checksum += i * (uint64_t)size * (uint64_t)(2 * start + size - 1) / 2;
   }

   std::cout << checksum << "\n";
   return 0;
}
