#ifndef _HASHSET_H
#define _HASHSET_H

#include "hashtable.hpp"

template<class Key, class Hasher = hash_func>
class HashSet:public Hashtable<Key, Key, Hasher>{
public:
  typedef Key key_type;
  typedef size_t size_type;
  typedef typename Hashtable<Key, Key, Hasher>::node_pointer node_pointer;
  typedef typename Hashtable<Key, Key, Hasher>::iterator iterator;
  typedef typename Hashtable<Key, Key, Hasher>::const_iterator const_iterator;

  HashSet(size_type init_bkt = 101): Hashtable<Key, Key, Hasher>(init_bkt) {}
  HashSet(const HashSet& x): Hashtable<Key, Key, Hasher>(x) {}
  HashSet(iterator first, iterator last, size_type init_bkt = 101);
  HashSet(const_iterator first, const_iterator last, size_type init_bkt = 101);
  bool operator==(const HashSet&) const;
  bool operator!=(const HashSet&) const;

  void insert(const key_type& key);
  void remove(const key_type& key);
};

template<class Key, class Hasher>
HashSet<Key, Hasher>::HashSet(iterator first, iterator last, size_type init_bkt)
:Hashtable<Key, Key, Hasher>(init_bkt){
  iterator iter = first;
  while (iter != last){
    insert(*iter);
    iter++;
  }
}

template<class Key, class Hasher>
HashSet<Key, Hasher>::HashSet(const_iterator first, const_iterator last, size_type init_bkt)
:Hashtable<Key, Key, Hasher>(init_bkt){
  const_iterator iter = first;
  while (iter != last){
    insert(*iter);
    iter++;
  }
}

template<class Key, class Hasher>
bool HashSet<Key, Hasher>::operator==(const HashSet& x) const{
  const_iterator iter = this->cbegin();
  while (iter != this->cend()){
    if (!x.containsKey(*iter))
      return false;
    iter++;
  }
  iter = x.cbegin();
  while (iter != x.cend()){
    if (!this->containsKey(*iter))
      return false;
    iter++;
  }
  return true;
}

template<class Key, class Hasher>
bool HashSet<Key, Hasher>::operator!=(const HashSet& x) const{
  return !operator==(x);
}

template<class Key, class Hasher>
void HashSet<Key, Hasher>::insert(const key_type& key){
  size_type hash_code = this->get_hash_code(key);
  size_type bucket_id = this->get_bucket_id(hash_code);
  node_pointer node = new hash_node<Key, Key>(key, key, hash_code, bucket_id); 
  this->insert_unique_node(node, key, bucket_id);
}

template<class Key, class Hasher>
void HashSet<Key, Hasher>::remove(const key_type& key){
  node_pointer ptr = this->get_node_ptr(key);
  if (ptr){
    this->remove_node(ptr, key, ptr->bucket_id);
  }
}

#endif
