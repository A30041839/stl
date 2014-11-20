#include "HashSet.hpp"
#include <iostream>
#include <string>

using namespace std;

int main(){
  HashSet<string> hashset1;
  cout << "hashset1" << endl;
  //insert and delete
  hashset1.insert("china");
  hashset1.insert("microsoft");
  hashset1.insert("Google");
  hashset1.insert("facebook");
  cout << hashset1.size() << endl;
  hashset1.remove("ok");
  hashset1.remove("facebook");
  cout << hashset1.size() << endl;

  //iterate
  HashSet<string>::const_iterator iter = hashset1.cbegin();
  while (iter != hashset1.cend()){
    cout << *iter << ",";
    iter++;
  }
	cout << endl;

	hashset1.insert("hello");
	hashset1.insert("hello");
	cout << *hashset1.begin() << endl;
  if (hashset1.containsKey("cool"))
		cout << "has cool" << endl;
	if (hashset1.containsKey("hello"))
		cout << "has hello" <<endl;
 
	HashSet<string> hashset2(hashset1);
	cout << "hashset2" << endl;
	cout << *hashset2.begin() << "," << hashset2.size() << endl;
  
	if (hashset1 == hashset2)
		cout << "hashset1 and hashset2 are equal." << endl;
  
	HashSet<string> hashset3(hashset1.begin(), hashset1.end());
  cout << "hashset3" << endl;	
  HashSet<string>::iterator iter2 = hashset3.begin();
  while (iter2 != hashset3.end()){
    cout << *iter2 << ",";
    iter2++;
  }
	cout << endl;
  
  cout << "rehash test" << endl;
  HashSet<int> hashset4;
  for (int i = 0; i <= 10000; i++)
    hashset4.insert(i);
  cout << hashset4.size() << endl;
  hashset4.clear();
  hashset4.clear();
  return 0;
}
