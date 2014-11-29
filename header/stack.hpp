//stack is a container adapter, and the underlying container is deque.
#ifndef STACK_H
#define STACK_H

#include "deque.hpp"

template<class T>
class stack{
public:
  typedef T value_type;
  typedef size_t size_type;

  explicit stack() { }
  stack(const stack<T>& x){
    m_deque = x.m_deque;
  }
  ~stack(){ }
  
  stack<T>& operator=(const stack<T>& x){
    m_deque = x.m_deque;
    return *this;
  }
  bool empty() const { return m_deque.empty(); }
  size_type size() const { return m_deque.size(); }
  value_type top() const {return m_deque.back(); }
  void push(const value_type& x) { m_deque.push_back(x); }
  void pop() { m_deque.pop_back(); }

private:
  deque<T> m_deque;
};

#endif
