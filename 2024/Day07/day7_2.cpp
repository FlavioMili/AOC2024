#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
typedef long long ll;

bool isPossible(ll target, const std::vector<ll>& operands, ll index, ll curr_val){
   if (curr_val == target) return true;
   if (index >= operands.size()) return false;
   return isPossible(target, operands, index + 1, curr_val * operands[index]) || 
          isPossible(target, operands, index + 1, curr_val + operands[index]) ||
          isPossible(target, operands, index + 1, 
          std::stoll(std::to_string(curr_val) + std::to_string(operands[index])));
}

int main(){
   std::vector<std::vector<ll>> operands;
   std::vector<ll> possible_res;
   ll res = 0;
   ll num = 0;

   std::ifstream file("input.txt");
   std::string line;

   while (std::getline(file, line)) {
      std::istringstream ss(line);
      ll elem;
      ss >> elem;
      possible_res.push_back(elem);
      ss.ignore(1, ':');
      std::vector<ll> local_operands;
      while (ss >> elem) local_operands.push_back(elem);
      operands.push_back(local_operands);
      num++;
   }
   
   for (ll i = 0; i < num; i++) if (isPossible(possible_res[i], operands[i], 0, 0)) res += possible_res[i];
   
   std::cout << res << "\n";
   return 0;
}

