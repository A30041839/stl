#include "../header/trie.hpp"
#include <iostream>
using namespace std;

struct Hasher{
  size_t operator()(const char c) const{
    return c - 97;
  }
};

int main(){
  const char* words[10] = {"china",
                     "microsoft",
                     "youtube",
                     "young",
                     "microprocessor",
                     "facebook",
                     "facemask",
                     "face",
                     "chinese",
                     "chinatown"};
  Trie<Hasher> trie;
  for (const char* word : words)
    trie.insert(word);
  cout << "trie has " << trie.size() << " items." << endl;
  if (trie.find("facebook"))
    cout << "trie contains facebook." << endl;
  if (trie.find("face"))
    cout << "trie contains face." << endl;
  trie.remove("chinese");
  if (!trie.find("chinese"))
    cout << "trie doesn't contain chinese." << endl;
  trie.insert("chinese");
  if (trie.find("chinese"))
    cout << "trie contains chinese." << endl;
  trie.clear();
  if (trie.find("chinatown"))
    cout << "trie contains chinatown." << endl;
  cout << "trie has " << trie.size() << " items." << endl;
  return 0;
}
