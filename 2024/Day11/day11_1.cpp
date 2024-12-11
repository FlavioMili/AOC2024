#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

constexpr int NUM_BLINKS = 25;
typedef long long ll;

int numAfterBlinking(ll input) {
   std::vector<ll> copy = {input};
   for (int i = 0; i < NUM_BLINKS; i++) {
      std::vector<ll> newCopy;
      for (int n = 0; n < copy.size(); n++) {
         if (copy[n] == 0) newCopy.push_back(1); 
         else {
            int numDigits = static_cast<ll>(std::log10(copy[n]) + 1);
            if (numDigits % 2 == 0) {
               int divisor = 1;
               for (int j = 0; j < numDigits / 2; ++j) divisor *= 10;
               newCopy.push_back(copy[n] / divisor);
               newCopy.push_back(copy[n] % divisor);
            }
            else newCopy.push_back(copy[n] * 2024);
         }
      }
      copy = newCopy;
   }
   return copy.size();
}

int main() {
   std::ifstream file("input.txt");
   int curr, res = 0;
   while (file >> curr) res += numAfterBlinking(curr);
   std::cout << res << "\n";
   return 0;
}
