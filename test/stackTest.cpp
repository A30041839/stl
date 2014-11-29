#include "../header/stack.hpp"
#include <iostream>

using namespace std;

int main(){
  stack<int> s;
  for (int i = 0; i < 1000; ++i)
    s.push(i);
  cout << s.size() << endl;
  cout << s.top() << endl;
  while (!s.empty()){
    cout << s.top() << ",";
    s.pop();
  }
  
  return 0;
}
