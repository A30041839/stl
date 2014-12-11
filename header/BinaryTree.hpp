#ifndef BINARYTREE_H
#define BINARYTREE_H

#include <iostream>
#include <vector>
#include <queue>
#include <stack>

using namespace std;

template<class T>
struct Tnode{
  T val;
  Tnode<T>* lchild;
  Tnode<T>* rchild;
  Tnode():lchild(0), rchild(0) {}
  Tnode(const T& t): val(t), lchild(0), rchild(0) {}
};

template<class T, class Ref, class Ptr>
class __binarytree_iterator_base{
public:
  typedef Tnode<T>* link_type;
  typedef T value_type;
  typedef Ref reference;
  typedef Ptr pointer;
 
  __binarytree_iterator_base(): current_node(NULL) {}

protected:
  link_type current_node;
  stack<link_type> _stack;
};

template<class T, class Ref, class Ptr>
class __binarytree_preorder_iterator:public __binarytree_iterator_base<T, Ref, Ptr>{
public:
  typedef __binarytree_preorder_iterator<T, Ref, Ptr> self;
  typedef typename __binarytree_iterator_base<T, Ref, Ptr>::link_type link_type;
  typedef typename __binarytree_iterator_base<T, Ref, Ptr>::value_type value_type;
  typedef typename __binarytree_iterator_base<T, Ref, Ptr>::reference reference;
  typedef typename __binarytree_iterator_base<T, Ref, Ptr>::pointer pointer;
  typedef forward_iterator_tag iterator_category;

  //constructor functions
  __binarytree_preorder_iterator() {}
  __binarytree_preorder_iterator(link_type x);
  __binarytree_preorder_iterator(const self& x);

  bool operator==(const self& x) const;
  bool operator!=(const self& x) const;

  reference operator*() const { return this->current_node->val; }
  pointer operator->() const {return &(operator*()); }
  self& operator++();
};

template<class T, class Ref, class Ptr>
__binarytree_preorder_iterator<T, Ref, Ptr>::__binarytree_preorder_iterator(link_type x){
  if (x == NULL){
    this->current_node = NULL;
    return;
  }
  this->current_node = x;
}

template<class T, class Ref, class Ptr>
__binarytree_preorder_iterator<T, Ref, Ptr>::__binarytree_preorder_iterator(const self& x){
  this->current_node = x.current_node;
  this->_stack = x._stack;
}

template<class T, class Ref, class Ptr>
bool __binarytree_preorder_iterator<T, Ref, Ptr>::operator==(const self& x) const{
  return (this->current_node == x.current_node) &&
         (this->_stack == x._stack);
}

template<class T, class Ref, class Ptr>
bool __binarytree_preorder_iterator<T, Ref, Ptr>::operator!=(const self& x) const{
  return !((this->current_node == x.current_node) &&
         (this->_stack == x._stack));
}

template<class T, class Ref, class Ptr>
__binarytree_preorder_iterator<T, Ref, Ptr>& __binarytree_preorder_iterator<T, Ref, Ptr>::operator++(){
  if (this->current_node->lchild != NULL){
    this->_stack.push(this->current_node);
    this->current_node = this->current_node->lchild;
  }else if (this->current_node->rchild != NULL){
    this->current_node = this->current_node->rchild;
  }else{
    this->current_node = NULL;
    while (!this->_stack.empty()){
      this->current_node = this->_stack.top();
      this->_stack.pop();
      if (this->current_node->rchild != NULL){
        this->current_node = this->current_node->rchild;
        break;
      }
    }
  }
  return *this;
}

template<class T, class Ref, class Ptr>
class __binarytree_inorder_iterator:public __binarytree_iterator_base<T, Ref, Ptr>{
public:
  typedef __binarytree_inorder_iterator<T, Ref, Ptr> self;
  typedef typename __binarytree_iterator_base<T, Ref, Ptr>::link_type link_type;
  typedef typename __binarytree_iterator_base<T, Ref, Ptr>::value_type value_type;
  typedef typename __binarytree_iterator_base<T, Ref, Ptr>::reference reference;
  typedef typename __binarytree_iterator_base<T, Ref, Ptr>::pointer pointer;
  typedef forward_iterator_tag iterator_category;

  //constructor functions
  __binarytree_inorder_iterator() {}
  __binarytree_inorder_iterator(link_type x);
  __binarytree_inorder_iterator(const self& x);

  bool operator==(const self& x) const;
  bool operator!=(const self& x) const;

  reference operator*() const { return this->current_node->val; }
  pointer operator->() const {return &(operator*()); }
  self& operator++();
};

template<class T, class Ref, class Ptr>
__binarytree_inorder_iterator<T, Ref, Ptr>::__binarytree_inorder_iterator(link_type x){
  if (NULL == x){
    this->current_node = NULL;
    return;
  }
  while (x->lchild != NULL){
    this->_stack.push(x);
    x = x->lchild;
  }
  this->current_node = x;
}

template<class T, class Ref, class Ptr>
__binarytree_inorder_iterator<T, Ref, Ptr>::__binarytree_inorder_iterator(const self& x){
  this->current_node = x.current_node;
  this->_stack = x._stack;
}

template<class T, class Ref, class Ptr>
bool __binarytree_inorder_iterator<T, Ref, Ptr>::operator==(const self& x) const{
  return (this->current_node == x.current_node) &&
         (this->_stack == x._stack);
}

template<class T, class Ref, class Ptr>
bool __binarytree_inorder_iterator<T, Ref, Ptr>::operator!=(const self& x) const{
  return !((this->current_node == x.current_node) &&
         (this->_stack == x._stack));
}

template<class T, class Ref, class Ptr>
__binarytree_inorder_iterator<T, Ref, Ptr>& __binarytree_inorder_iterator<T, Ref, Ptr>::operator++(){
  if (!this->_stack.empty()){
    this->current_node = this->_stack.top();
    this->_stack.pop();
    link_type ptr = this->current_node;
    if (ptr->rchild != NULL){
      ptr = ptr->rchild;
      while (ptr != NULL){
        this->_stack.push(ptr);
        ptr = ptr->lchild;
      }
    }
  }else{
    this->current_node = NULL;
  }
  return *this;
}

template<class T, class Ref, class Ptr>
class __binarytree_postorder_iterator:public __binarytree_iterator_base<T, Ref, Ptr>{
public:
  typedef __binarytree_postorder_iterator<T, Ref, Ptr> self;
  typedef typename __binarytree_iterator_base<T, Ref, Ptr>::link_type link_type;
  typedef typename __binarytree_iterator_base<T, Ref, Ptr>::value_type value_type;
  typedef typename __binarytree_iterator_base<T, Ref, Ptr>::reference reference;
  typedef typename __binarytree_iterator_base<T, Ref, Ptr>::pointer pointer;
  typedef forward_iterator_tag iterator_category;

  //constructor functions
  __binarytree_postorder_iterator() {}
  __binarytree_postorder_iterator(link_type x);
  __binarytree_postorder_iterator(const self& x);

  bool operator==(const self& x) const;
  bool operator!=(const self& x) const;

  reference operator*() const { return this->current_node->val; }
  pointer operator->() const {return &(operator*()); }
  self& operator++();

private:
  link_type prev = NULL;
};

template<class T, class Ref, class Ptr>
__binarytree_postorder_iterator<T, Ref, Ptr>::__binarytree_postorder_iterator(link_type x){
  if (x == NULL){
    this->current_node = NULL;
    return;
  }
  while (x->lchild != NULL){
    this->_stack.push(x);
    x = x->lchild;
  }
  this->current_node = x;
  prev = x;
}

template<class T, class Ref, class Ptr>
__binarytree_postorder_iterator<T, Ref, Ptr>::__binarytree_postorder_iterator(const self& x){
  this->current_node = x.current_node;
  this->_stack = x._stack;
}

template<class T, class Ref, class Ptr>
bool __binarytree_postorder_iterator<T, Ref, Ptr>::operator==(const self& x) const{
  return (this->current_node == x.current_node) &&
         (this->_stack == x._stack);
}

template<class T, class Ref, class Ptr>
bool __binarytree_postorder_iterator<T, Ref, Ptr>::operator!=(const self& x) const{
  return !((this->current_node == x.current_node) &&
         (this->_stack == x._stack));
}

template<class T, class Ref, class Ptr>
__binarytree_postorder_iterator<T, Ref, Ptr>& __binarytree_postorder_iterator<T, Ref, Ptr>::operator++(){
  Tnode<T>* node = NULL;
  prev = this->current_node;
  if (this->_stack.empty()){
    this->current_node = NULL;
    return *this;
  }
  while (node || !this->_stack.empty()){
    if (node){
      this->_stack.push(node);
      node = node->lchild;
    }else{
      node =this->_stack.top();
      if (node->rchild != NULL && node->rchild != prev){
        node = node->rchild;
      }else{
        this->current_node = node;
        this->_stack.pop();
        break;
      }
    }
  }
  return *this;
}


//!binarytree class
template<class T>
class BinaryTree{
public:
  typedef __binarytree_preorder_iterator<T, T&, T*> iterator;
    
  //!constructor
  BinaryTree();
  BinaryTree(const char* input); //使用广义表构建二叉树
  ~BinaryTree();

  iterator begin() const {return iterator(root);}
  iterator end() const {return iterator();}

  //!level-order tranversal
  void levelOrder() const;
  //!pre-order
  void preOrder() const;
  //!in-order
  void inOrder() const;
  //!post-order
  void postOrder() const;
  void preOrderNorecurse1() const;
  void preOrderNorecurse2() const;
  void inOrderNorecurse1() const;
  void inOrderNorecurse2() const;
  void postOrderNorecurse1() const;
  void postOrderNorecurse2() const;
  void printLevel(size_t level) const;
  //!hight of tree
  int getHight() const {
    return getHight(this->root);
  }
  int getSubTreeHight(Tnode<T>* node) const{
    return getHight(node);
  }
  Tnode<T>* getRoot() const{
    return this->root;
  }

private:
  Tnode<T>* root;
  void preOrder(Tnode<T>* node) const;
  void inOrder(Tnode<T>* node) const;
  void postOrder(Tnode<T>* node) const;
  void printLevel(Tnode<T>* node, size_t level) const;
  int getHight(Tnode<T>* node) const;
  void releaseTree(Tnode<T>* node);
};

template<class T>
BinaryTree<T>::BinaryTree(){
  this->root = NULL;
}

template<class T>
BinaryTree<T>::BinaryTree(const char* input){
  //使用广义表构建二叉树
  if (input == NULL) return;
  Tnode<T>* ptr1;
  Tnode<T>* ptr2;
  this->root = NULL;
  stack<Tnode<T>* > _stack;
  int k = 0;
  for (int i = 0; i < strlen(input); ++i){
    switch (input[i]){
      case '(' : _stack.push(ptr2); ptr1 = ptr2; k = 1; break;
      case ')' : _stack.pop(); break;
      case ',' : k = 2; break;
      default: 
      ptr2 = new Tnode<T>(input[i]);
      if (this->root == NULL){
        this->root = ptr2;
      }else{
        ptr1 = _stack.top();
        if (k == 1){
          ptr1->lchild = ptr2;
        }else{
          ptr1->rchild = ptr2;
        }
      }
    }
  }
}

//partialization for type int
template<>
BinaryTree<int>::BinaryTree(const char* input){
  //使用广义表构建二叉树
  if (input == NULL) return;
  Tnode<int>* ptr1;
  Tnode<int>* ptr2;
  this->root = NULL;
  stack<Tnode<int>* > _stack;
  int k = 0;
  for (int i = 0; i < strlen(input); ++i){
    switch (input[i]){
      case '(' : _stack.push(ptr2); ptr1 = ptr2; k = 1; break;
      case ')' : _stack.pop(); break;
      case ',' : k = 2; break;
      default:
      ptr2 = new Tnode<int>(input[i] - '0');
      if (this->root == NULL){
        this->root = ptr2;
      }else{
        ptr1 = _stack.top();
        if (k == 1){
          ptr1->lchild = ptr2;
        }else{
          ptr1->rchild = ptr2;
        }
      }
    }
  }
}

template<class T>
BinaryTree<T>::~BinaryTree(){
  releaseTree(this->root);
}

template<class T>
void BinaryTree<T>::levelOrder() const{
  if (this->root == NULL){
    cout << "Tree is empty!" << endl;
    return;
  }
  queue<Tnode<T>* > que;
  que.push(this->root);
  cout << "Level order sequence:" << endl;
  while (!que.empty()){
    Tnode<T>* tmp = que.front();
    que.pop();
    cout << tmp->val << ",";
    if (tmp->lchild) que.push(tmp->lchild);
    if (tmp->rchild) que.push(tmp->rchild);
  }
  cout << endl;
}

template<class T>
void BinaryTree<T>::preOrder() const{
  if (this->root == NULL){
    cout << "Tree is empty!" << endl;
    return;
  }
  cout << "Preorder traversal:" << endl;
  preOrder(this->root);
  cout << endl;
}

template<class T>
void BinaryTree<T>::inOrder() const{
  if (this->root == NULL){
    cout << "Tree is empty!" << endl;
    return;
  }
  cout << "Inorder traversal:" << endl;
  inOrder(this->root);
  cout << endl;
}

template<class T>
void BinaryTree<T>::postOrder() const{
  if (this->root == NULL){
    cout << "Tree is empty!" << endl;
    return;
  }
  cout << "Post order traversal:" << endl;
  postOrder(this->root);
  cout << endl;
}

template<class T>
void BinaryTree<T>::printLevel(size_t level) const{
  printLevel(this->root, level);
  cout << endl;
}

template<class T>
void BinaryTree<T>::printLevel(Tnode<T>* node, size_t level) const{
  if (node == NULL || level < 0)
    return;
  if (level == 0){
    cout << node->val << ",";
  }
  else{
    printLevel(node->lchild, level - 1);
    printLevel(node->rchild, level - 1);
  }
}

template<class T>
void BinaryTree<T>::preOrder(Tnode<T>* node) const{
  if (node != NULL){
    cout << node->val << ",";
    preOrder(node->lchild);
    preOrder(node->rchild);
  }
}

template<class T>
void BinaryTree<T>::preOrderNorecurse1() const{
  cout << "preorder norecurse 1:" << endl;
  if (this->root == NULL) return;
  Tnode<T>* node = this->root;
  stack<Tnode<T>* > _stack;
  _stack.push(node);
  while (!_stack.empty()){
    node = _stack.top();
    _stack.pop();
    cout << node->val << ",";
    if (node->rchild) _stack.push(node->rchild);
    if (node->lchild) _stack.push(node->lchild);
  }
  cout << endl;
}

template<class T>
void BinaryTree<T>::preOrderNorecurse2() const{
  cout << "preorder norecurse2:" << endl;
  if (this->root == NULL) return;
  Tnode<T>* node = this->root;
  stack<Tnode<T>* > _stack;
  while (node || !_stack.empty()){
    if (node){
      _stack.push(node);
      cout << node->val << "," ;
      node = node->lchild;
    }else{
      node = _stack.top();
      _stack.pop();
      node = node->rchild;
    }
  }
  cout << endl;
 }

template<class T>
void BinaryTree<T>::inOrderNorecurse1() const{
  cout << "inorder norecurse1:" << endl;
  if (this->root == NULL) return;
  Tnode<T>* node = this->root;
  stack<Tnode<T>* > _stack;
  while (node){
    _stack.push(node);
    node = node->lchild;
  }
  while (!_stack.empty()){
    node = _stack.top();
    _stack.pop();
    cout << node->val << ",";
    if (node->rchild){
      node = node->rchild;
      while (node){
        _stack.push(node);
        node = node->lchild;
      }
    }
  }
  cout << endl;
}

template<class T>
void BinaryTree<T>::inOrderNorecurse2() const{
  //if current node is not null, go left and push into stack
  //else, pop the stack and visit, set the current node to right child
  cout << "inorder norecurse2:" << endl;
  if (this->root == NULL) return;
  Tnode<T>* node = this->root;
  stack<Tnode<T>* > _stack;
  while (node || !_stack.empty()){
    if (node){
      _stack.push(node);
      node = node->lchild;
    }else{
      node = _stack.top();
      _stack.pop();
      cout << node->val << ",";
      node = node->rchild;
    }
  }
  cout << endl;
}

template<class T>
void BinaryTree<T>::inOrder(Tnode<T>* node) const{
  if (node != NULL){
    inOrder(node->lchild);
    cout << node->val << ",";
    inOrder(node->rchild);
  }
}

template<class T>
void BinaryTree<T>::postOrder(Tnode<T>* node) const{
  if (node != NULL){
    postOrder(node->lchild);
    postOrder(node->rchild);
    cout << node->val << ",";
  }
}

template<class T>
void BinaryTree<T>::postOrderNorecurse1() const{
  cout << "post order norecurse 1:" << endl;
  if (this->root == NULL) return;
  stack<Tnode<T>* > stmp, svisit;
  Tnode<T>* node = this->root;
  stmp.push(node);
  while (!stmp.empty()){
    node = stmp.top();
    stmp.pop();
    svisit.push(node);
    if (node->lchild != NULL) stmp.push(node->lchild);
    if (node->rchild != NULL) stmp.push(node->rchild);
  }
  while (!svisit.empty()){
    node = svisit.top();
    svisit.pop();
    cout << node->val << ",";
  }
  cout << endl;
}

template<class T>
void BinaryTree<T>::postOrderNorecurse2() const{
  cout << "post order norecurse2:" << endl;
  if (this->root == NULL) return;
  Tnode<T>* node = this->root;
  Tnode<T>* prev;
  stack<Tnode<T>* > _stack;
  while (node != NULL || !_stack.empty()){
    if (node){
      _stack.push(node);
      node = node->lchild;
    }
    else{
      node = _stack.top();
      if (node->rchild != NULL && prev != node->rchild)
        node = node->rchild;
      else{
      cout << node->val << ",";
      prev = node;
      node = NULL;
      _stack.pop();
      }
    }
  }
  cout << endl;
}

template<class T>
int BinaryTree<T>::getHight(Tnode<T>* node) const{
  if (node == NULL) return 0;
  int leftHight = getHight(node->lchild);
  int rightHight = getHight(node->rchild);
  return leftHight > rightHight ? leftHight + 1 : rightHight + 1;
}

template<class T>
void BinaryTree<T>::releaseTree(Tnode<T>* node){
  if (node != NULL){
    if (node->lchild) releaseTree(node->lchild);
    if (node->rchild) releaseTree(node->rchild);
    delete node;
  }
}
#endif


