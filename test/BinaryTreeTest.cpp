#include "../header/BinaryTree.hpp"
using namespace std;

int main(){
  const char* str = "A(B(D,E(G,)),C(,F))";
  BinaryTree<char> t(str);
  t.preOrder();
  t.inOrder();
  t.postOrder();
  t.levelOrder();
  cout << "Tree hight is :" << t.getHight() << endl;
  cout << "Iterator test:" << endl;
  BinaryTree<char>::iterator iter = t.begin();
  while (iter != t.end()){
    cout << *iter << ",";
    ++iter;
  }
  cout << endl;
  cout << "level 2 of tree is:" << endl;
  t.printLevel(2);
  t.preOrderNorecurse1();
  t.preOrderNorecurse2();
  t.inOrderNorecurse1();
  t.inOrderNorecurse2();
  t.postOrderNorecurse1();
  t.postOrderNorecurse2();
}
