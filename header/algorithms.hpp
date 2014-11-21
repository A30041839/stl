#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include "vector.hpp"
/* basic functions
 */

template<class T>
inline void swap(T& a, T& b){
  T tmp = a;
  a = b;
  b = tmp;
}

/* sort algorithms
 */


//! heap sort
template<class T>
class heap_sort{
public:
  typedef typename vector<T>::iterator iterator;
  static void sort(iterator start, iterator finish){
    if (start == finish) return;
    BuildMaxheap(start, finish);
    while (start != finish - 1){
      --finish;
      swap(*start, *finish);
      Maxheapify(start, finish, start);
    }
  }

private:
  static void Maxheapify(iterator begin, iterator end, iterator position){
    while (position <= begin + (end - begin) / 2 - 1){
      iterator lchild = position + (position - begin + 1);
      iterator rchild = position + (position - begin + 2);
      if (rchild < end){
        if (*lchild > *rchild){
          if (*lchild > *position){
            swap(*position, *lchild);
            position = lchild;
          }else{
            break;
          }
        }else{
          if (*rchild > *position){
            swap(*position, *rchild);
            position = rchild;
          }else{
            break;
          }
        }
      }else if (lchild < end){
        if (*lchild > *position){
          swap(*position, *lchild);
        }
        break;
      }else{
        break;
      }
    }
  }
  
  static void BuildMaxheap(iterator start, iterator finish){
    for (size_t i = (finish - start) / 2; i != 0; --i)
      Maxheapify(start, finish, start + i - 1);
  }
  
};

//! insertion sort
template<class T>
class insertion_sort{
public:
  typedef typename vector<T>::iterator iterator;
  static void sort(iterator start, iterator finish){
    if (start == finish) return;
    for (iterator iter = start + 1; iter < finish; ++iter){
      iterator pos = findpos(start, iter);
      T tmp = *iter;
      move(pos + 1, iter);
      *(pos + 1) = tmp;
    }
  }

private:
    static iterator findpos(iterator start, iterator pos){
      iterator iter = pos - 1;
      for (; iter >= start && *iter > *pos; --iter);
      return iter;
    }

    static void move(iterator pos1, iterator pos2){
      while (pos2 > pos1){
        *pos2 = *(pos2 - 1);
        --pos2;
      }
    }
};  

//! quick sort
template<class T>
class quick_sort{
public:
  typedef typename vector<T>::iterator iterator;
  static void sort(iterator start, iterator finish){
    if (start == finish || start == finish - 1) return;
    iterator pos = partition(start, finish);
    sort(start, pos );
    sort(pos + 1, finish);
  }

private:
  static iterator partition(iterator begin, iterator end){
    iterator mid = begin + (end - begin) / 2;
    swap(*mid, *(end - 1));
    iterator it1 = begin - 1;
    T pivot = *(end - 1);
    for (iterator it2 = begin; it2 < end - 1; ++it2){
      if (*it2 < pivot){
        ++it1;
        swap(*it1, *it2);
      }
    }
    swap(*(it1 + 1), *(end - 1));
    return it1 +1;
  }
};

//! merge sort
template<class T>
class merge_sort{
public:
  typedef typename vector<T>::iterator iterator;
  static void sort(iterator start, iterator finish){
    if (start == finish || start == finish - 1) return;
    iterator mid = start + (finish - start) / 2;
    sort(start, mid);
    sort(mid, finish);
    merge(start, mid, mid, finish);
  }

private:
  static void merge(iterator s1, iterator e1, iterator s2, iterator e2){
    vector<T> tmp;
    iterator _s1 = s1;
    iterator _s2 = s2;
    while (_s1 < e1 && _s2 < e2){
      if (*_s1 < *_s2){
        tmp.push_back(*_s1);
        ++_s1;
      }else{
        tmp.push_back(*_s2);
        ++_s2;
      }
    }
    while (_s1 < e1){
      tmp.push_back(*_s1);
      ++_s1;
    }
    while (_s2 < e2){
      tmp.push_back(*_s2);
      ++_s2;
    } 
    for (iterator iter = tmp.begin(); iter < tmp.end(); ++iter){
      *s1 = *iter;
      ++s1;
    }
  }
};

//! select sort
template<class T>
class select_sort{
public:
  typedef typename vector<T>::iterator iterator;
  static void sort(iterator start, iterator finish){
    for (iterator iter = start; iter < finish; ++iter){
      swap(*(select(iter, finish)), *iter);
    }
  }

private:
  static iterator select(iterator begin, iterator end){
    T val = *begin;
    iterator result = begin;
    while (begin < end){
      if (*begin < val){
        val = *begin;
        result = begin;
      }
      ++begin;
    }
    return result;
  }
};

//! bubble sort
template<class T>
class bubble_sort{
public:
  typedef typename vector<T>::iterator iterator;
  static void sort(iterator start, iterator finish){
    if (start == finish) return;
    while (start < finish){
      for (iterator iter = finish - 1; iter > start; --iter){
        if (*iter < *(iter - 1))
          swap(*iter, *(iter - 1));
      }
      ++start;
    }
  }
};

#endif
