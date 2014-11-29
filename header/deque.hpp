#ifndef DEQUE_H
#define DEQUE_H

#include <algorithm>
#include <stdexcept>

#ifndef DEQUE_BUFFER_SIZE
#define DEQUE_BUFFER_SIZE 512
#endif

#ifndef DEQUE_MAP_INCREMENT
#define DEQUE_MAP_INCREMENT 10
#endif

template<class T, class Ref, class Ptr>
struct __deque_iterator{
  typedef __deque_iterator<T, Ref, Ptr> iterator;
  typedef __deque_iterator<T, const Ref, const Ptr> const_iterator;
  typedef __deque_iterator self;
  typedef std::random_access_iterator_tag iterator_category;

  typedef T value_type;
  typedef Ref reference;
  typedef Ptr pointer;
  typedef size_t size_type;
  typedef ptrdiff_t difference_type;
  typedef T** map_pointer;

  //constructor
  __deque_iterator(): cur(0), first(0), last(0), node(0) {}

  __deque_iterator(T* x, map_pointer y)
    : cur(x), first(*y), last(*y + DEQUE_BUFFER_SIZE), node(y) {}

  __deque_iterator(const self& x)
    : cur(x.cur), first(x.first), last(x.last), node(x.node) {}

  self& operator=(const self& x){
    cur = x.cur;
    first = x.first;
    last = x.last;
    node = x.node;
    return *this;
  }

  self& operator++(){
    cur++;
    if (cur == last){
      //jump to the next buffer
      set_node(node + 1, 0);
    }
    return *this;
  }

  self operator++(int){
    self tmp = *this;
    ++*this;
    return tmp;
  }

  self& operator--(){
    if (cur == first){
      //jump to the previous buffer
      set_node(node - 1, DEQUE_BUFFER_SIZE - 1);
    }else{
      cur--;
    }
    return *this;
  }

  self operator--(int){
    self tmp = *this;
    --*this;
    return tmp;
  }

  self operator+(difference_type n) const{
    self tmp = *this;
    tmp += n;
    return tmp;
  }

  self operator-(difference_type n) const{
    self tmp = *this;
    tmp -= n;
    return tmp;
  }

  self& operator+=(difference_type n){
    difference_type offset = cur + n - first;
    if (offset >= 0 && offset < difference_type(DEQUE_BUFFER_SIZE)){
      cur = cur + n;
      return *this;
    }else{
      difference_type node_offset = offset > 0 ? (offset / difference_type(DEQUE_BUFFER_SIZE)) :
                                                 (offset / difference_type(DEQUE_BUFFER_SIZE) - 1);
      size_type pos = offset > 0 ? (offset % difference_type(DEQUE_BUFFER_SIZE)) :
                                   (difference_type(DEQUE_BUFFER_SIZE) - (-offset) % difference_type(DEQUE_BUFFER_SIZE));
      set_node(node + node_offset, pos);
      return *this;
    }
  }

  self& operator-=(difference_type n){
    return operator+=(-n);
  }

  difference_type operator-(const self& x) const{
    difference_type node_offset = node - x.node - 1;
    difference_type offset = node_offset * difference_type(DEQUE_BUFFER_SIZE) 
                             + difference_type(cur - first) + difference_type(x.last - x.cur);
    return offset;
  }

  reference operator*() const{
    return *cur;
  }

  pointer operator->() const{
    return cur;
  }
  
  bool operator==(const self& x) const{
    return cur == x.cur;
  }

  bool operator!=(const self& x) const{
    return cur != x.cur;
  }

  bool operator<(const self&x) const{
    return node == x.node ? cur < x.cur : node < x.node;
  }

  T* cur;
  T* first;
  T* last;
  map_pointer node;

  void set_node(map_pointer _node, size_type _n){
    node = _node;
    first = *node;
    last = *node + DEQUE_BUFFER_SIZE;
    cur = first + _n;
  }
};


template<class T>
class deque{
public:
  typedef T value_type;
  typedef T* pointer;
  typedef T** map_pointer;
  typedef T& reference;
  typedef size_t size_type;
  typedef ptrdiff_t difference_type;
  typedef __deque_iterator<T, T&, T*> iterator;
  typedef __deque_iterator<T, const T&, const T*> const_iterator;

  //iterator
  iterator begin() const{
    return start;
  }
  iterator end() const{
    return finish;
  }
  const_iterator cbegin() const{
    return const_iterator(start.cur, start.node);
  }
  const_iterator cend() const{
    return const_iterator(finish.cur, finish.node);
  }

  //constructors
  deque(){
    map = new pointer[1];
    map[0] = new value_type[DEQUE_BUFFER_SIZE];
    map_start = map;
    map_size = 1;
    map_maxlen = 1;
    start = iterator(map[0], &map[0]);
    finish = start;
  }

  deque(size_type n, const value_type& x) { fill_initialize(n, x); }

  deque(size_type n) { fill_initialize(n, value_type()); }

  deque(const deque<T>& x);

  ~deque() {deallocate();}

  deque<T>& operator=(const deque<T>& x){
    if (this != &x){
      if (size() >= x.size()){
        erase(std::copy(x.begin(), x.end(), begin()), end());
      }else{
        insert(end(), x.size() - size());
        std::copy(x.begin(), x.end(), begin());
      }
    }
    return *this;
  }

  reference operator[](size_type n) const {
    if (n >= size())
      throw std::out_of_range("Index out of range!");
    return *(start + n);
  } 

  reference front() const { return *start; }
  
  reference back() const {
    iterator tmp = finish;
    --tmp;
    return *tmp;
  }

  bool empty() const { return finish == start; }

  size_type size() const {  return size_type(finish - start); }

  void push_back(const value_type& x){
    if (finish.cur < finish.last - 1){
      //still have empty slot
      *finish.cur = x;
      ++finish.cur;
    }else{
      push_back_aux(x);
    }
  }

  void push_front(const value_type& x){
    if (start.cur > start.first){
      --start.cur;
      *start.cur = x;
    }else{
      push_front_aux(x);
    }
  }

  void pop_back(){
    if (empty()) return;
    if (finish.cur > finish.first){
      --finish.cur;
    }else{
      pop_back_aux();
    }
  }

  void pop_front(){
    if (empty()) return;
    if (start.cur != start.last - 1){
      ++start.cur;
    }else{
      pop_front_aux();
    }
  }

  void insert(iterator position, const value_type& x){
    if (position == start){
      push_front(x);
    }else if (position == finish){
      push_back(x);
    }else{
      insert_aux(position, x);
    }
  }

  void insert(iterator position) { insert(position, value_type()); }

  void insert(iterator position, size_type n, const value_type& x){
    difference_type left_len = position - start;
    difference_type right_len = finish - position;
    if (left_len < right_len){
      //the left part is shorter, move the elements forward
      for (size_type i = 0; i < n; ++i)
        push_front(value_type());
      std::copy(start + n, start + n + left_len, start);
      std::fill(start + left_len, start + left_len + n, x);
    }else{
      //the right part is shorter, move the elements backward
      for (size_type i = 0; i < n; ++i)
        push_back(value_type());
      std::copy_backward(start + left_len, finish - n, finish);
      std::fill(start + left_len, start + left_len + n, x);
    }
  }

  void insert(iterator position, size_type n) { insert(position, n, value_type()); }
  
  void insert(iterator position, iterator first, iterator last){
    difference_type left_len = position - start;
    difference_type right_len = finish - position;
    size_type n = last - first;
    if (left_len < right_len){
      //the left part is shorter, move the elements forward
      for (size_type i = 0; i < n; ++i)
        push_front(value_type());
      std::copy(start + n, start + n + left_len, start);
      std::copy(first, last, start + left_len);
    }else{
      //the right part is shorter, move the elements backward
      for (size_type i = 0; i < n; ++i)
        push_back(value_type());
      std::copy_backward(start + left_len, finish - n, finish);
      std::copy(first, last, start + left_len);
    }
  }

  void erase(iterator position){
    if (position == start){
      pop_front();
    }else if (position == finish - 1){
      pop_back();
    }else{
      erase_aux(position);
    }
  }

  void erase(iterator first, iterator last){
    difference_type left_len = first - start;
    difference_type right_len = finish - last;
    if (left_len < right_len){
      //move the left part to the right
      std::copy_backward(start, first, last);
      for (int i = 0; i < last - first; ++i)
        pop_front();
    }else{
      //move the right part to the left
      std::copy(last, finish, first);
      for (int i = 0; i < last - first; ++i)
        pop_back();
    }
  }

  void clear(){
    erase(start, finish);
  }

protected:
  map_pointer map;
  size_type map_size;
  size_type map_maxlen;
  map_pointer map_start;
  iterator start;
  iterator finish;

  void push_back_aux(const value_type& x);

  void push_front_aux(const value_type& x);

  void pop_back_aux();

  void pop_front_aux();

  void insert_aux(iterator position, const value_type& x);

  void erase_aux(iterator position);

  void deallocate();

  void fill_initialize(size_type n, const value_type& x){
    map_size = (n - 1) / DEQUE_BUFFER_SIZE + 1;
    map = new pointer[map_size];
    for (size_type i = 0; i < map_size - 1; ++i){
      pointer buffer = new value_type[DEQUE_BUFFER_SIZE];
      std::fill(buffer, buffer + DEQUE_BUFFER_SIZE, x);
      map[i] = buffer;
    }
    pointer buffer = new value_type[DEQUE_BUFFER_SIZE];
    std::fill(buffer, buffer + n % DEQUE_BUFFER_SIZE, x);
    map[map_size - 1] = buffer;
    map_start = map;
    map_maxlen = map_size;
    start = iterator(map[0], &map[0]);
    finish = start + n;
  }
  
  void map_free_end(){
    *(map_start + map_size - 1) = 0;
    --map_size;
  }

  void map_free_start(){
    *map_start = 0;
    --map_size;
    ++map_start;
  }

  map_pointer map_alloc_end();

  map_pointer map_alloc_start();

};

template<class T>
deque<T>::deque(const deque<T>& x){
  map = new pointer[1];
  map[0] = new value_type[DEQUE_BUFFER_SIZE];
  map_start = map;
  map_size = 1;
  map_maxlen = 1;
  start = iterator(map[0], &map[0]);
  finish = start;
  insert(finish, x.begin(), x.end()); 
}

template<class T>
void deque<T>::push_back_aux(const value_type& x){
  //construct a new buffer at the end
  map_pointer ptr = map_alloc_end();
  map_pointer prevptr = ptr - 1;
  (*prevptr)[DEQUE_BUFFER_SIZE - 1] = x;
  *ptr = new value_type[DEQUE_BUFFER_SIZE];
  start.node = map_start;
  finish.node = ptr;
  finish.first = *ptr;
  finish.last = *ptr + DEQUE_BUFFER_SIZE;
  finish.cur = finish.first;
}

template<class T>
void deque<T>::push_front_aux(const value_type& x){
  //construct a new buffer at the front
  map_pointer ptr = map_alloc_start();
  *ptr = new value_type[DEQUE_BUFFER_SIZE];
  (*ptr)[DEQUE_BUFFER_SIZE - 1] = x;
  finish.node = map_start + map_size - 1;
  start.node = ptr;
  start.first = *ptr;
  start.last = *ptr + DEQUE_BUFFER_SIZE;
  start.cur = start.last - 1;
}

template<class T>
void deque<T>::pop_back_aux(){
  --finish;
  //release the last buffer
  delete[] *(map_start + map_size - 1);
  *(map_start + map_size - 1) = 0;
  --map_size;
}

template<class T>
void deque<T>::pop_front_aux(){
  //release the first buffer
  ++start;
  delete[] *map_start;
  *map_start = 0;
  ++map_start;
  --map_size;
}

template<class T>
void deque<T>::insert_aux(iterator position, const value_type& x){
    difference_type left_len = position - start;
    difference_type right_len = finish - position;
    if (left_len < right_len){
      //the left part is shorter, move the elements forward
      push_front(value_type());
      std::copy(start + 1, start + 1 + left_len, start);
      std::fill(start + left_len, start + left_len + 1, x);
    }else{
      //the right part is shorter, move the elements backward
      push_back(value_type());
      std::copy_backward(start + left_len, finish - 1, finish);
      std::fill(start + left_len, start + left_len + 1, x);
    }
}

template<class T>
void deque<T>::erase_aux(iterator position){
    difference_type left_len = position - start;
    difference_type right_len = finish - position;
    if (left_len < right_len){
      //the left part is shorter, move the elements backward
      std::copy_backward(start, position, position + 1);
      pop_front();
    }else{
      //the right part is shorter, move the elements forward
      std::copy(position + 1, finish, position);
      pop_back();
    }
}

template<class T>
typename deque<T>::map_pointer deque<T>::map_alloc_end(){
  //if the end has free slot, then allocate it directly
  if (map_start + map_size < map + map_maxlen){
    ++map_size;
    return map_start + map_size - 1;
  }else{
    //allocate new map, increment the size by DEQUE_MAP_INCREMENT at the end
    map_pointer _map = new pointer[map_maxlen + DEQUE_MAP_INCREMENT];
    std::fill(_map, _map + map_maxlen + DEQUE_MAP_INCREMENT, nullptr);
    std::copy(map, map + map_maxlen, _map);
    ++map_size;
    map_maxlen += DEQUE_MAP_INCREMENT;
    map_start = map_start - map + _map;
    delete[] map;
    map = _map;
    return map_start + map_size - 1;
  }
}

template<class T>
typename deque<T>::map_pointer deque<T>::map_alloc_start(){
  //if the beginning has free slot, then allocate it directly
  if (map_start > map){
    ++map_size;
    --map_start;
    return map_start;
  }else{
    //allocate new map, increment the size by DEQUE_MAP_INCREMENT at the beginning
    map_pointer _map = new pointer[map_maxlen + DEQUE_MAP_INCREMENT];
    std::fill(_map, _map + map_maxlen + DEQUE_MAP_INCREMENT, nullptr);
    std::copy(map, map + map_maxlen, _map + DEQUE_MAP_INCREMENT);
    ++map_size;
    map_maxlen += DEQUE_MAP_INCREMENT;
    map_start = _map + DEQUE_MAP_INCREMENT - 1;
    delete[] map;
    map = _map;
    return map_start;
  }
}

template<class T>
void deque<T>::deallocate(){
  for(map_pointer ptr = map_start; ptr != map_start + map_size; ++ptr)
    delete[] *ptr;
  delete[] map;
}

#endif
