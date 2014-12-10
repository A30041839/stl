#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <vector>
#include <iostream>
#include <unordered_set>

template<class T>
struct LNode{
  typedef T value_type;
  typedef LNode<T>* pointer_type;
  value_type val;
  pointer_type next;

  LNode(): val(value_type()), next(NULL) {}
  LNode(value_type& x): val(x), next(NULL) {}
};

template<class T>
class LinkedList{
public:
  typedef T value_type;
  typedef typename LNode<T>::pointer_type pointer_type;
  //constructors 
  LinkedList(){ head = new LNode<value_type>(); }
  LinkedList(std::vector<value_type>& vec){
    head = new LNode<value_type>();
    for (size_t i = 0; i < vec.size(); ++i)
      insert_to_tail(vec[i]);
  }
  LinkedList(const LinkedList<T>& other){
    head = new LNode<value_type>();
    pointer_type ptr = other.head->next;
    while (ptr != NULL){
      insert_to_tail(ptr->val);
      ptr = ptr->next;
    }
  }

  ~LinkedList(){
    clear();
    delete head;
  }

  LinkedList<T>& operator=(const LinkedList<T>& other){
    if (this != &other){
      clear();
      pointer_type ptr = other.head->next;
      while (ptr != NULL){
        insert_to_tail(ptr->val);
        ptr = ptr->next;
      }
    }
    return *this;
  }

  void insert_to_tail(value_type& x){
    pointer_type ptr = head;
    while(ptr->next != NULL)
      ptr = ptr->next;
    ptr->next = new LNode<value_type>(x);
  }

  void print_list() const{
    pointer_type ptr = head->next;
    while (ptr != NULL){
      if (ptr->next != NULL)
        std::cout << ptr->val << ",";
      else
        std::cout << ptr->val << std::endl;
      ptr = ptr->next;
    }
  }

  void clear(){
    //mind for loop in linked list
    //store nodes freed
    std::unordered_set<LNode<T>* > s;
    pointer_type ptr = head->next;
    while (ptr != NULL){
      if (s.count(ptr) == 0){
        pointer_type tmp = ptr->next;
        s.insert(ptr);      
        delete ptr;
        ptr = tmp;        
      }else{
        break;
      }
    }
  }

  LNode<value_type>* head;
};

#endif
