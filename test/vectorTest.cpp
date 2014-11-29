#include "../header/vector.hpp"
#include <iostream>

using namespace std;

void print(vector<int>& vec){
  vector<int>::iterator iter = vec.begin();  
  while (iter != vec.end()){
    cout << *iter << ", ";
    iter++;
  }
  cout << endl;
}

int main(){
  vector<int> vec(5, 6);
  print(vec);
  cout << vec.front() << ", " <<  vec.back() << endl;
  for (int i = 1; i < 10; i++)
    vec.push_back(i);
  cout << vec.size() << endl;
  print(vec);
  vec.insert(vec.begin(), 10);
  print(vec);
  vec.insert(vec.begin() + 2, 10);
  print(vec);
  vec.insert(vec.end() - 1, 10);
  print(vec);
  cout << vec[2] << endl;
  vec[2] = 9;
  print(vec);
  vec.pop_back();
  print(vec);
  vec.erase(vec.begin());
  vec.erase(vec.end() - 1);
  print(vec);
  vec.erase(vec.begin() + 1);
  print(vec);
  vec.erase(vec.begin(), vec.begin() + 2);
  print(vec);

  vector<int> vec2 = vec;
  print(vec2);
  vec2 = vec;

  vec.clear();
  cout << vec.size() << endl;
  cout << vec.capacity() << endl;
  if (vec.empty())
    cout << "vector is empty." << endl;

  return 0;
}
