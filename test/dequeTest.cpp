#include "deque.hpp"
#include <string>
#include <iostream>

using namespace std;

void print(const deque<int>& x){
  deque<int>::const_iterator iter = x.cbegin();
  for (; iter != x.cend(); ++iter)
    cout << *iter << ",";
  cout << endl;
}

void print(const deque<string>& x){
  deque<string>::const_iterator iter = x.cbegin();
  for (; iter != x.cend(); ++iter)
    cout << *iter << ",";
  cout << endl;
}

int main(){
  deque<int> deq;
  if (deq.empty())
    cout << "deque is now empty!" << endl;
  deq.push_back(1);
  cout << "deque's size is " << deq.size() << endl;
	deq.push_front(2);
  print(deq);
  deq.clear();
 
  for (int i = 0; i < 10000; ++i)
    deq.push_back(i);
  cout << "deque's size is " << deq.size() << endl;
	cout << deq.front() << " " << deq.back() << endl;
  deq.pop_front();
  cout << deq.front() << endl;
  deq.pop_back();
  cout << deq.back() << endl;
  for (int i = 0; i < 500; ++i)
    deq.pop_front();
  cout << deq.front() << "," << deq.size() << endl;
  deq.clear();
  deq.insert(deq.begin(), 1);
  print(deq);
  deq.insert(deq.end(), 10, 2);
  print(deq);
  deque<int> deq1 = deq;
	print(deq1);
  deq1.erase(deq1.begin() + 2);
  print(deq1);
  deq1.erase(deq1.begin() + 1, deq1.end());
  print(deq1);
  deque<int>::iterator iter = deq1.begin();
  while (iter != deq1.end()){
    cout << *iter << ",";
    ++iter;
  }
  cout << endl;

  deque<string> deq2(10, "hello");
  deq2.push_back("youtube");
	print(deq2);
  deque<string> deq3;
  deq3 = deq2;
	print(deq3);

	deque<int> deq4;
	for (int i = 0; i < 1000; ++i)
		deq4.push_back(i);
	while (!deq4.empty()){
		deq4.pop_back();
	}
  return 0;
}
