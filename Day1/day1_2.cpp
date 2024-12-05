#include <fstream>
#include <iostream>
#include <vector>
#include <unordered_set>
int main(int argc, char* argv[]){
  long long res = 0;
  int a, b;
  std::unordered_set<int> nums;
  std::vector<int> vecB;
  std::ifstream file(argv[1]);
  while(file >> a >> b){
    nums.insert(a);
    vecB.push_back(b);
  }
  for (int i = 0; i < vecB.size(); i++) 
    if(nums.find(vecB[i]) != nums.end()) res += vecB[i];

  std::cout << res << std::endl;
  return res;
}

