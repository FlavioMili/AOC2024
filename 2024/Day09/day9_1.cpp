#include <iostream>
#include <fstream>
#include <vector>
#include <string>

int main() {
   std::ifstream file("input.txt");
   std::string partialWorkingString;
   getline(file, partialWorkingString);

   std::vector<int> files;
   std::vector<int> empties;
   std::vector<int> filesystem;

   size_t totalBlocks = 0;

   for (size_t i = 0; i < partialWorkingString.size(); i++) {
      int val = partialWorkingString[i] - '0';
      if (i % 2 == 0) {
         files.push_back(val);
         totalBlocks += val; 
      } 
      else empties.push_back(val);
   }

   int front = 0;
   int frontLeft = files[front];
   int tail = files.size() - 1;
   int tailLeft = files[tail];
   int empty = 0;
   int emptyLeft = empties[empty];
   bool fillingEmpty = false;

   for (size_t i = 0; i < totalBlocks; i++) {
      if (fillingEmpty) {
         if (emptyLeft > 0) {
            filesystem.push_back(tail);
            tailLeft--;

            if (tailLeft <= 0 && tail > front) {
               tail--;
               tailLeft = files[tail];
            }
         }
         else --i;

         emptyLeft--;
         if (emptyLeft <= 0) {
            empty++;
            if (empty < empties.size()) emptyLeft = empties[empty];
            fillingEmpty = false;
         }
      } else {
         filesystem.push_back(front);
         frontLeft--;

         if (frontLeft <= 0 && front < tail) {
            ++front;
            frontLeft = files[front];
            fillingEmpty = true;
         }
      }
   }

   uint64_t checksum = 0;
   for (uint64_t pos = 0; pos < filesystem.size(); ++pos) 
      checksum += pos * static_cast<uint64_t>(filesystem[pos]);

   std::cout << checksum << "\n";
   return 0;
}
