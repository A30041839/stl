#include "DoubleLinklist.hpp"
#include <iostream>
using namespace std;

int main(){
  DoubleLinklist<int> dlist;
  dlist.insert_first(1);
  dlist.print();
  dlist.append_last(2);
  dlist.print();
  dlist.insert(0, 3);
  dlist.print();
  dlist.delete_first();
  dlist.print();
  dlist.delete_last();
  dlist.print();
  dlist.delete_node(0);
  dlist.print();
  
  for(int i = 1; i < 20; ++i)
    dlist.append_last(i);
  dlist.print();
  cout << dlist.get_first() << endl;
  cout << dlist.get_last() << endl;
  cout << dlist.get(3) << endl;
  
  //test for iterators
  cout << "test for iterators..." << endl;
  DoubleLinklist<int>::const_iterator iter = dlist.begin();
  while (iter != dlist.end()){
    cout << *iter << ",";
    ++iter;
  }
  cout << endl;
  for (auto& x : dlist)
    cout << x << ",";
  cout << endl;

  dlist.clear();
  dlist.print();
}
