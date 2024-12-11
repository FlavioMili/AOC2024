#include <cstdint>
#include <iostream>
#include <fstream>
#include <cmath>

// Now the code runs basically instantly, using unordered map instead and just a lambda function inside the main.
// Even tho I could remove the version of part 1 I want to show how the code evolved for performance and not just
// the first attempt that worked in order to make a early submission.

constexpr int NUM_BLINKS = 75;
typedef long long ll;

int main() {
   std::ifstream file("input.txt");
   ll curr, res = 0;
   std::unordered_map<uint64_t, size_t> stoneCounts;
   while (file >> curr) stoneCounts[curr]++;
   std::unordered_map<uint64_t, size_t> newCounts;

   auto Blink = [&] {for (auto [stone, count] : stoneCounts) {
      if (stone == 0) newCounts[1] += count;
      else if (ll digits = static_cast<ll>(std::log10(stone) + 1); digits % 2 == 0) {
         uint64_t tens = 1;
         for (int i = 0; i < digits / 2; i++) tens *= 10;
         uint64_t left = stone / tens;
         uint64_t right = stone - (left * tens);
         newCounts[left] += count;
         newCounts[right] += count;
      }
      else newCounts[stone * 2024] += count;
   }
      std::swap(stoneCounts, newCounts);
      newCounts.clear();
   };

   for (int i = 0; i < NUM_BLINKS; i++) Blink(); 
   for (auto [stone , count] : stoneCounts) res += count;
   std::cout << res << "\n";
   return 0;
}
