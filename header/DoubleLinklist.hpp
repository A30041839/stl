//Implementation of double linked list in C++.
//@date: 2014/10/15

#ifndef DOUBLE_LINKLIST_H
#define DOUBLE_LINKLIST_H

#include <iostream>
#include <stdexcept>

using namespace std;

template<class T>
struct DNode{
  typedef DNode<T>* link_type;
  T value;
  link_type prev;
  link_type next;

  DNode() {}
  DNode(T val, link_type prev, link_type next){
    this->value = val;
    this->prev = prev;
    this->next = next;
  }
};

template<class T, class Ref, class Ptr>
struct __list_iterator{
  typedef __list_iterator<T, T&, T*> iterator;
  typedef __list_iterator<T, const T&, const T*> const_iterator;
  typedef __list_iterator<T, Ref, Ptr> self;

  typedef bidirectional_iterator_tag iterator_category;

  typedef T value_type;
  typedef Ref reference;
  typedef Ptr pointer;
  typedef DNode<T>* link_type;
  
  //point to current node
  link_type node;

  //constructor functions
  __list_iterator(link_type x) : node(x) {}
  __list_iterator() {}
  __list_iterator(const iterator& x): node(x.node) {}

  bool operator==(const self& x) const { return x.node == node; }
  bool operator!=(const self& x) const { return x.node != node; }

  reference operator*() const { return (*node).value; }
  pointer operator->() const {return &(operator*()); }
  self& operator++() {
    node = node->next;
    return *this;
  }
  self& operator--(){
    node = node->prev;
    return *this;
  }
  self operator++(int){
    self tmp = *this;
    node = node->next;
    return tmp;
  }
  self operator--(int){
    self tmp = *this;
    node = node->prev;
    return tmp;
  }
};

template<class T>
class DoubleLinklist{
public:
  typedef __list_iterator<T, T&, T*> iterator;
  typedef __list_iterator<T, const T&, const T*> const_iterator;
  
  typedef DNode<T>* link_type;

  DoubleLinklist();
  ~DoubleLinklist();

  iterator begin() { return head->next;}
  const_iterator begin() const { return head->next;}
  iterator end() {return head;}
  const_iterator end() const {return head;}

  size_t size() const;
  bool isEmpty() const;

  T& get(size_t index) const;
  T& get_first() const;
  T& get_last() const;

  bool insert(size_t pos, T val);
  bool insert_first(T val);
  bool append_last(T val);

  bool delete_first();
  bool delete_last();
  bool delete_node(size_t pos);
  void clear();
  void print();

private:
  link_type head;
  size_t count;
  link_type get_node(size_t pos) const;
};

template<class T>
DoubleLinklist<T>::DoubleLinklist(){
  this->head = new DNode<T>();
  this->head->prev = this->head->next = this->head;
  this->count = 0;
}

template<class T>
DoubleLinklist<T>::~DoubleLinklist(){
  clear();
  delete head;
}

template<class T>
void DoubleLinklist<T>::clear(){
  link_type ptr = head->next;
  for (size_t i = 0; i < this->count; ++i){
    link_type tmp = ptr->next;
    delete ptr;
    ptr = tmp;
  }
  head->next = head->prev = head;
  this->count = 0;
}

template<class T>
size_t DoubleLinklist<T>::size() const{
  return this->count;
}

template<class T>
bool DoubleLinklist<T>::isEmpty() const{
 return this->count == 0;
}

template<class T>
T& DoubleLinklist<T>::get(size_t index) const{
  if (index >= 0 && index < this->count){
    return get_node(index)->value;
  }
  else{
    throw runtime_error("Index out of bound!");
  }
}

template<class T>
T& DoubleLinklist<T>::get_first() const{
  if (count > 0)
    return this->head->value;
  else
    throw runtime_error("The link list is empty!");
}

template<class T>
T& DoubleLinklist<T>::get_last() const{
  if (count > 0)
    return this->head->prev->value;
  else
    throw runtime_error("The link list is empty!");
}

template<class T>
bool DoubleLinklist<T>::insert(size_t pos, T val){
  if (pos >= 0 && pos < this->count){
    link_type tmp = get_node(pos);
    link_type newNode = new DNode<T>(val, tmp->prev, tmp);
    tmp->prev->next = newNode;
    tmp->prev = newNode;
    this->count++;
    return true;
    }
  else{
    return false;
  }
}

template<class T>
bool DoubleLinklist<T>::insert_first(T val){
  link_type newNode = new DNode<T>(val, head, head->next);
  head->next->prev = newNode;
  head->next = newNode;
  this->count++;
  return true;  
}

template<class T>
bool DoubleLinklist<T>::append_last(T val){
  link_type newNode = new DNode<T>(val, head->prev,head);
  head->prev->next = newNode;
  head->prev = newNode;
  this->count++;
  return true;
}

template<class T>
bool DoubleLinklist<T>::delete_first(){
  return delete_node(0);
}

template<class T>
bool DoubleLinklist<T>::delete_last(){
  return delete_node(this->count - 1);
}

template<class T>
bool DoubleLinklist<T>::delete_node(size_t pos){
  link_type del = get_node(pos);
  if (del){
    del->prev->next = del->next;
    del->next->prev = del->prev;
    delete del;
    this->count--;
    return true;
  }
  else{
    return false;
  }
}

template<class T>
typename DoubleLinklist<T>::link_type DoubleLinklist<T>::get_node(size_t pos) const{
  if (pos >= 0 && pos < this->count){
    link_type ptr = this->head;
    for(size_t i = 0; i <= pos; ++i){
      ptr = ptr->next;
    }
    return ptr;
  }
  else{
    return NULL;
  }
}

template<class T>
void DoubleLinklist<T>::print(){
  if (this->count > 0){
    link_type ptr = this->head;
    for(size_t i = 0; i < this->count - 1; ++i){
      ptr = ptr->next;
      cout << ptr->value << ",";
    }
    cout << ptr->next->value << endl;
  }
  else{
    cout << "The list is empty!" << endl;
  }
}
#endif
 
