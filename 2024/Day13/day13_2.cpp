#include <fstream>
#include <iostream>
#include <string>

// x1 and y1 cost 3, x2 and y2 cost 1
// find the minimum amount of tokens
typedef int64_t ll;

ll calculateTokens(ll a, ll d, ll b, ll e, ll c, ll f) {
   ll denominator = (a * e - b * d);
   ll x = (c * e - b * f) / denominator;
   ll y = (a * f - c * d) / denominator;
   if(x>=0 && y>=0 && a*x+b*y == c && d*x+e*y == f)
      return 3*x+y;
   return 0;
}

int main() {
   ll res = 0;
   std::ifstream file("input.txt");
   std::string line;

   ll x1, y1, x2, y2, t1, t2;
   while (!file.eof()) {
      if (std::getline(file, line) && line.find("Button A") != std::string::npos) {
         sscanf(line.c_str(), "Button A: X+%lld, Y+%lld", &x1, &y1);
         if (std::getline(file, line) && line.find("Button B") != std::string::npos) {
            sscanf(line.c_str(), "Button B: X+%lld, Y+%lld", &x2, &y2);
            if (std::getline(file, line) && line.find("Prize") != std::string::npos) {
               sscanf(line.c_str(), "Prize: X=%lld, Y=%lld", &t1, &t2);
               t1+=10000000000000;
               t2+=10000000000000;
               ll cost = calculateTokens(x1, y1, x2, y2, t1, t2);
               res += cost;
            }
         }
      }
   }
   std::cout << res << "\n";
   return 0;
}
