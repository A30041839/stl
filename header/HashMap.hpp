#ifndef _HASHMAP_H
#define _HASHMAP_H

#include "hashtable.hpp"

template<class Key, class Tp>
struct pair{
  typedef Key key_type;
  typedef Tp mapped_type;
  const key_type first;
  mutable mapped_type second;
  pair():first(key_type()), second(mapped_type()) {}
  pair(const key_type& _first, const mapped_type& _second)
  :first(_first), second(_second) {}
  pair(const pair&x):first(x.first), second(x.second) {}

  bool operator==(const pair& x) const {return first == x.first && second == x.second;}
  bool operator!=(const pair& x) const {return first != x.first || second != x.second;}
};

template<class Key, class Tp, class Hasher = hash_func>
class HashMap:public Hashtable<Key, pair<Key, Tp>, Hasher>{
public:
  typedef Key key_type;
  typedef Tp mapped_type;
  typedef pair<key_type, mapped_type> value_type;
  typedef size_t size_type;
  typedef typename Hashtable<key_type, value_type, Hasher>::node_pointer node_pointer;
  typedef typename Hashtable<key_type, value_type, Hasher>::iterator iterator;
  typedef typename Hashtable<key_type, value_type, Hasher>::const_iterator const_iterator;

  HashMap(size_type init_bkt = 101): Hashtable<key_type, value_type, Hasher>(init_bkt) {}
  HashMap(const HashMap& x): Hashtable<key_type, value_type, Hasher>(x) {}
  HashMap(iterator first, iterator last, size_type init_bkt = 101);
  HashMap(const_iterator first, const_iterator last, size_type init_bkt = 101);
  bool operator==(const HashMap&) const;
  bool operator!=(const HashMap&) const;
  mapped_type& operator[](const key_type& key);

  bool contains(const value_type& value) const;
  void insert(const value_type& value);
  void insert(iterator first, iterator last);
  void insert(const_iterator first, const_iterator last);
  void remove(const key_type& key);
};

template<class Key, class Tp, class Hasher>
HashMap<Key, Tp, Hasher>::HashMap(iterator first, iterator last, size_type init_bkt)
:Hashtable<key_type, value_type, Hasher>(init_bkt){
  iterator iter = first;
  while (iter != last){
    insert(*iter);
    iter++;
  }
}

template<class Key, class Tp, class Hasher>
HashMap<Key, Tp, Hasher>::HashMap(const_iterator first, const_iterator last, size_type init_bkt)
:Hashtable<key_type, value_type, Hasher>(init_bkt){
  const_iterator iter = first;
  while (iter != last){
    insert(*iter);
    iter++;
  }
}

template<class Key, class Tp, class Hasher>
bool HashMap<Key, Tp, Hasher>::contains(const value_type& value) const{
  return this->contain_value(value);
}

template<class Key, class Tp, class Hasher>
bool HashMap<Key, Tp, Hasher>::operator==(const HashMap& x) const{
  const_iterator iter = this->cbegin();
  while (iter != this->cend()){
    if (!x.contains(*iter))
      return false;
    iter++;
  }
  iter = x.cbegin();
  while (iter != x.cend()){
    if (!this->contains(*iter))
      return false;
    iter++;
  }
  return true;
}

template<class Key, class Tp, class Hasher>
bool HashMap<Key, Tp, Hasher>::operator!=(const HashMap& x) const{
  return !operator==(x);
}

template<class Key, class Tp, class Hasher>
void HashMap<Key, Tp, Hasher>::insert(const value_type& value){
  size_type hash_code = this->get_hash_code(value.first);
  size_type bucket_id = this->get_bucket_id(hash_code);
  node_pointer node = new hash_node<key_type, value_type>(value.first, value, hash_code, bucket_id); 
  this->insert_unique_node(node, value.first, bucket_id);
}

template<class Key, class Tp, class Hasher>
void HashMap<Key, Tp, Hasher>::insert(iterator first, iterator last){
  iterator iter = first;
  while (iter != last){
    insert(value_type(*iter));
    iter++;
  }
}

template<class Key, class Tp, class Hasher>
void HashMap<Key, Tp, Hasher>::insert(const_iterator first, const_iterator last){
  const_iterator iter = first;
  while (iter != last){
    insert(value_type(*iter));
    iter++;
  }
}

template<class Key, class Tp, class Hasher>
void HashMap<Key, Tp, Hasher>::remove(const key_type& key){
  node_pointer ptr = this->get_node_ptr(key);
  if (ptr){
    this->remove_node(ptr, key, ptr->bucket_id);
  }
}

template<class Key, class Tp, class Hasher>
Tp& HashMap<Key, Tp, Hasher>::operator[](const key_type& key){
  if (this->containsKey(key)){
    return this->get_node_ptr(key)->get_ptr()->second;
  }else{
    size_type hash_code = this->get_hash_code(key);
    size_type bucket_id = this->get_bucket_id(hash_code);
    node_pointer node = new hash_node<key_type, value_type>(key, value_type(key, mapped_type()), hash_code, bucket_id); 
    this->insert_unique_node(node, key, bucket_id);
    return node->get_ptr()->second;
  }
}

#endif
