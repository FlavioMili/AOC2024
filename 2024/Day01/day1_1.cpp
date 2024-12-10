#include <algorithm>
#include <fstream>
#include <iostream>
#include <ostream>
#include <vector>
int main(int argc, char* argv[]){
  int res = 0;
  int a, b;
  std::vector<int> vecA, vecB;
  std::ifstream file(argv[1]);
  while(file >> a >> b){
    auto posA = std::lower_bound(vecA.begin(), vecA.end(), a); 
    vecA.insert(posA, a); 
    auto posB = std::lower_bound(vecB.begin(), vecB.end(), b); 
    vecB.insert(posB, b); 
  }
  for (int i = 0; i < vecA.size(); i++) res += abs(vecA[i] - vecB[i]);
  std::cout << res << std::endl;
  file.close();
  return res;
}
