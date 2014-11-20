#include <iostream>
#include "algorithms.hpp"
#include "vector.hpp"

using namespace std;

void print(vector<int>& vec){
  for (int i = 0; i < vec.size(); ++i)
    cout << vec[i] << ",";
  cout << endl;
}

int main(){
  vector<int> vec;
  vec.push_back(8);
  vec.push_back(1);
  vec.push_back(-1);
  vec.push_back(5);
  vec.push_back(6);
  vec.push_back(0);
  vec.push_back(4);
  vec.push_back(10);
  vec.push_back(-8);

  print(vec);
  //heap_sort<int>::sort(vec.begin(), vec.end());
  //merge_sort<int>::sort(vec.begin(), vec.end());
  quick_sort<int>::sort(vec.begin(), vec.end());
  //insertion_sort<int>::sort(vec.begin(), vec.end());
  //select_sort<int>::sort(vec.begin(), vec.end());
  //bubble_sort<int>::sort(vec.begin(), vec.end());
  print(vec);

  return 0;
}
