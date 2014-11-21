//queue is a container adapter, and the underlying container is deque.
#ifndef QUEUE_H
#define QUEUE_H

#include "deque.hpp"

template<class T>
class queue{
public:
  typedef T value_type;
  typedef size_t size_type;

  explicit queue(){ m_deque = new deque<T>(); }
  ~queue(){ delete m_deque; }

  bool empty() const { return m_deque->empty(); } 
  size_type size() const { return m_deque->size(); }
  value_type front() const {return m_deque->front(); }
  value_type back() const { return m_deque->back(); }
  void push(const value_type& x) { m_deque->push_back(x); }
  void pop() { m_deque->pop_front(); }

private:
  deque<T>* m_deque;
};

#endif
