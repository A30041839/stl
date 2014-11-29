#ifndef VECTOR_H
#define VECTOR_H

#include <algorithm>

template<class T>
class vector{
public:
  typedef T value_type;
  typedef T& reference;
  typedef T* pointer;
  typedef T* iterator;
  typedef const T* const_iterator;
  typedef size_t size_type;

  iterator begin() const {return first;}
  iterator end() const {return last;}
  const_iterator cbegin() const {return first;}
  const_iterator cend() const {return last;}

  size_type size() const {return size_type(end() - begin());}
  size_type capacity() const {return size_type(end_of_storage - begin());}
  bool empty() const {return begin() == end();}
  reference operator[](size_type n) const {return *(begin() + n);}

  //constructors
  vector(): first(0), last(0), end_of_storage(0) {}
  vector(size_type n, const T& value) {fill_initialize(n, value);}
  explicit vector(size_type n) {fill_initialize(n, T());}
  vector(const vector<T>& x){
    array = new value_type[x.size()];
    std::copy(x.begin(), x.end(), array);
    first = array;
    last = first + x.size();
    end_of_storage = last;
  }
  ~vector() {delete[] array;}

  vector<T>& operator=(const vector<T>& x){
    delete[] array;
    array = new value_type[x.size()];
    std::copy(x.begin(), x.end(), array);
    first = array;
    last = first + x.size();
    end_of_storage = last;
    return *this;
  }
  
  reference front() const {return *begin();}
  reference back() const {return *(end() - 1);}

  void push_back(const T& x){
    if (last != end_of_storage){
      T x_copy = x;
      *last = x_copy;
      last++;
    }else{
      expand_volume();
      T x_copy = x;
      *last = x_copy;
      last++;
    }
  }

  iterator insert(iterator position, const T& x){
    if (last != end_of_storage){
      std::copy_backward(position, last, last + 1);
      T x_copy = x;
      *position = x_copy;
      last++;
      return position;
    }else{
      expand_volume();
      std::copy_backward(position, last, last + 1);
      T x_copy = x;
      *position = x_copy;
      last++;
      return position;
    }
  }

  void pop_back(){
    if (first != last){
      --last;
    }
  };

  void erase(iterator position){
    if (position + 1 != last)
      std::copy(position + 1, last, position);
    --last;
  }

  void erase(iterator start, iterator finish){
    std::copy(finish, last, start);
    last = last - (finish - start);
  }

  void clear() {erase(begin(), end());}


protected:
  pointer first;
  pointer last;
  pointer end_of_storage;
  value_type* array;

  void fill_initialize(size_type n, const T& x){
    array = new value_type[n];
    for (int i = 0; i < n; ++i)
      array[i] = x;
    first = array;
    last = array + n;
    end_of_storage = last;
  }

  T* expand_volume(){
    size_type oldsize = size_type(end_of_storage - begin());
    size_type newsize = oldsize == 0 ? 1 : 2 * oldsize;
    value_type* newarray = new value_type[newsize];
    std::copy(begin(), end(), newarray);
    if (oldsize > 0)
      delete[] array;
    array = newarray;
    first = array;
    last = first + oldsize;
    end_of_storage = first + newsize; 
    return array;
  }

};

#endif
