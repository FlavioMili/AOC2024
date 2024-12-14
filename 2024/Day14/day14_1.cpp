#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>

#define CENTER_X 50
#define CENTER_Y 51
#define WIDTH 101
#define HEIGHT 103

int main() {
   int partial_res[4] = {};
   std::ifstream file("input.txt");
   std::string line;
   int central = 0;
   while (getline(file, line)) {
      std::stringstream ss(line);
      char junk;
      int ix, iy, vx, vy;
      ss >> junk >> junk >> ix >> junk >> iy >> junk >> junk >> vx >> junk >> vy;

      int fpx = ((ix + vx * 100) % WIDTH + WIDTH) % WIDTH;
      int fpy = ((iy + vy * 100) % HEIGHT + HEIGHT) % HEIGHT;

      if (fpx < CENTER_X && fpy < CENTER_Y)  partial_res[0]++;  
      else if (fpx < CENTER_X && fpy > CENTER_Y)  partial_res[1]++;  
      else if (fpx > CENTER_X && fpy < CENTER_Y)  partial_res[2]++;  
      else if (fpx > CENTER_X && fpy > CENTER_Y) partial_res[3]++; 
      else central++;
   }
   long long safety_factor = partial_res[0] * partial_res[1] * partial_res[2] * partial_res[3];
   std::cout << "Safety factor: " << safety_factor << "\n";

   return 0;
}
