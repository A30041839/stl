#include "queue.hpp"
#include <iostream>

using namespace std;

int main(){
  queue<int> s;
  for (int i = 0; i < 1000; ++i)
    s.push(i);
  cout << s.size() << endl;
  cout << s.front() << "," << s.back() << endl;
  while (!s.empty()){
    cout << s.front() << ",";
    s.pop();
  }
  
  return 0;
}
