#include <iostream>
#include "HashMap.hpp"

void print(HashMap<std::string, int>& x){
  HashMap<std::string, int>::iterator iter = x.begin();
  while (iter != x.end()){
    std::cout << "(" << iter->first << "," << iter->second 
              << ") ";
    iter++;
  }
  std::cout << std::endl;
}

int main(){
  HashMap<std::string, int> m1;
  m1.insert(pair<std::string, int>("hello", 1));
  m1["china"] = 2;
  std::cout << m1.size() << std::endl;
  pair<std::string, int> p("youtube", 3);
  m1.insert(p);
  std::cout << m1.size() << std::endl;
  print(m1);

  HashMap<std::string, int> m2(m1);
  if (m2 == m1)
    std::cout << "m1 == m2" << std::endl;
  std::cout << m2["china"] << std::endl;
  std::cout << m2["fuck"] << std::endl;
  m2.remove("youtube");
  print(m2);
  m2.remove("fucking");
  m2["like"] = 7;
  m2["love"] = 8;
  print(m2);

  HashMap<std::string, int> m3(m1.begin(), m1.end());
  print(m3);
  m3.insert(m2.cbegin(), m2.cend());
  print(m3);
  if (m3.containsKey("love"))
    std::cout << "m3 has key love" << std::endl;
  if (m3.contains(p))
    std::cout << "m3 contains (youtube, 3)" << std::endl;
}
