#ifndef HASH_TABLE_H
#define HASH_TABLE_H
/* base class for hashset and hashmap
 */
#include "hashcode.hpp"
#include <cstring>
#include <iterator>
//!hash node class
template<class Key, class Value>
struct hash_node{
  typedef Key key_type;
  typedef Value value_type;
  typedef size_t size_type;
  hash_node* next;
  const key_type key;
  value_type value;
  size_type hash_code;
  size_type bucket_id;

  hash_node(): next(NULL), key(key_type()){}
  explicit hash_node(const key_type& _key, const value_type& _value, size_type _hash_code, size_type _bucket_id)
  : key(_key), value(_value), hash_code(_hash_code), bucket_id(_bucket_id)
  {}

  value_type* get_ptr(){
    return &value;
  }
  value_type& get_val(){
    return value;
  }
};

template<class Key, class Value>
struct hashtable_iterator_base{
  typedef hash_node<Key, Value>* node_pointer;
  node_pointer pointer;
  explicit hashtable_iterator_base():pointer(NULL) {}
  explicit hashtable_iterator_base(node_pointer x): pointer(x) {}
};

template<class Key, class Value>
struct hashtable_iterator:hashtable_iterator_base<Key, Value>{
  typedef typename hash_node<Key, Value>::value_type value_type;
  typedef value_type* pointer_type;
  typedef value_type& reference;
  typedef hashtable_iterator self;
  typedef typename hashtable_iterator_base<Key, Value>::node_pointer node_pointer;
  typedef std::forward_iterator_tag iterator_category;


  hashtable_iterator(){}
  explicit hashtable_iterator(node_pointer x): hashtable_iterator_base<Key, Value>(x) {}
  hashtable_iterator(const self& x): hashtable_iterator_base<Key, Value>(x.pointer) {}

  bool operator==(const self& x) const {return x.pointer == this->pointer;}
  bool operator!=(const self& x) const {return x.pointer != this->pointer;}

  reference operator*() const{
    return this->pointer->get_val();
  }
  pointer_type operator->() const{
    return this->pointer->get_ptr();
  }
  self& operator++(){
    this->pointer = this->pointer->next;
    return *this;
  }
  self operator++(int){
    self tmp(*this);
    this->pointer = this->pointer->next;
    return tmp;
  }
};

template<class Key, class Value>
struct hashtable_const_iterator:hashtable_iterator_base<Key, Value>{
  typedef typename hash_node<Key, Value>::value_type value_type;
  typedef const value_type* pointer_type;
  typedef const value_type& reference;
  typedef hashtable_const_iterator self;
  typedef typename hashtable_iterator_base<Key, Value>::node_pointer node_pointer;  
  typedef std::forward_iterator_tag iterator_category;

  hashtable_const_iterator(){}
  explicit hashtable_const_iterator(node_pointer x): hashtable_iterator_base<Key, Value>(x) {}
  hashtable_const_iterator(const self& x): hashtable_iterator_base<Key, Value>(x.pointer) {}

  bool operator==(const self& x) const {return x.pointer == this->pointer;}
  bool operator!=(const self& x) const {return x.pointer != this->pointer;}

  reference operator*() const{
    return this->pointer->get_val();
  }
  pointer_type operator->() const{
    return this->pointer->get_ptr();
  }
  self& operator++(){
    this->pointer = this->pointer->next;
    return *this;
  }
  self operator++(int){
    self tmp(*this);
    this->pointer = this->pointer->next;
    return tmp;
  }
};


//! base class for HashSet and HashMap
template<class Key, class Value, class Hasher = hash_func>
class Hashtable{
public:
  //public typedefs
  typedef Key key_type;
  typedef Value value_type;
  typedef Hasher hasher_type;
  typedef size_t size_type;
  typedef hash_node<key_type, value_type>* node_pointer;

  typedef hashtable_iterator<key_type, value_type> iterator;
  typedef hashtable_const_iterator<key_type, value_type> const_iterator;

  //constructor, destructor, assignments
  explicit Hashtable(size_type init_bkt = 101);
  Hashtable(const Hashtable&);
  ~Hashtable();
  
  //iterators
  iterator begin() {return iterator(m_before_node->next);}
  const_iterator cbegin() const {return const_iterator(m_before_node->next);}
  iterator end() {return iterator();}
  const_iterator cend() const {return const_iterator();}

  //public member functions
  Hashtable& operator=(const Hashtable&);
  size_type size() const;
  bool containsKey(const key_type& key) const;
  void clear();

protected:
  void insert_unique_node(node_pointer node, const key_type& key, size_type bkt_id);
  void insert_bucket_begin(node_pointer node, size_type bkt_id);
  void remove_node(node_pointer node, const key_type& key, size_type bkt_id);
  void remove_bucket_begin(node_pointer node, size_type bkt_id);
  bool bucket_contain_key(const key_type& key, size_type bkt_id) const;
  bool contain_value(const value_type& value) const;  
  void rehash();
  size_type get_bucket_id(size_type hash_code) const;
  hash_node<Key, Value>* get_node_ptr(const key_type& x) const;
  size_type get_hash_code(const key_type& key) const;

private:
  void de_allocate();
  node_pointer* m_buckets;
  size_type m_current_size;
  size_type m_bucket_count;
  node_pointer m_before_node;
  hasher_type m_hasher;
};

template<class Key, class Value, class Hasher>
Hashtable<Key, Value, Hasher>::Hashtable(size_type init_bkt)
: m_current_size(0), m_bucket_count(init_bkt){
  m_buckets = new node_pointer[init_bkt];
  m_hasher = hasher_type();
  memset(m_buckets, 0, sizeof(m_buckets) * m_bucket_count);
  m_before_node = new hash_node<key_type, value_type>();
}

//!copy constructor
template<class Key, class Value, class Hasher>
Hashtable<Key, Value, Hasher>::Hashtable(const Hashtable& x): m_current_size(x.m_current_size),
                                                       m_bucket_count(x.m_bucket_count),
                                                       m_hasher(x.m_hasher){
  m_buckets = new node_pointer[m_bucket_count];
  memcpy(m_buckets, x.m_buckets, sizeof(x.m_buckets) * x.m_bucket_count);
  m_before_node = new hash_node<key_type, value_type>();
  node_pointer ptr = x.m_before_node->next;
  node_pointer prev = m_before_node;
  while (ptr){
    node_pointer tmp = new hash_node<key_type, value_type>(ptr->key, ptr->value, ptr->hash_code, ptr->bucket_id);
    prev->next = tmp;
    ptr = ptr->next;
    prev = tmp;
  }
}

template<class Key, class Value, class Hasher>
Hashtable<Key, Value, Hasher>::~Hashtable(){
  de_allocate();
}

template<class Key, class Value, class Hasher>
Hashtable<Key, Value, Hasher>& Hashtable<Key, Value, Hasher>::operator=(const Hashtable& x){
  de_allocate();
  m_current_size = x.m_current_size;
  m_bucket_count = x.m_bucket_count;
  m_hasher = x.m_hasher;

  m_buckets = new node_pointer[m_bucket_count];
  memcpy(m_buckets, x.m_buckets, sizeof(x.m_buckets) * x.m_bucket_count);
  m_before_node = new hash_node<key_type, value_type>();
  node_pointer ptr = x.m_before_node->next;
  node_pointer prev = m_before_node;
  while (ptr){
    node_pointer tmp = new hash_node<key_type, value_type>(ptr->key, ptr->value, ptr->hash_code, ptr->bucket_id);
    prev->next = tmp;
    ptr = ptr->next;
    prev = tmp;
  }
  return *this;
}


template<class Key, class Value, class Hasher>
size_t Hashtable<Key, Value, Hasher>::size() const{
  return m_current_size;
}

template<class Key, class Value, class Hasher>
bool Hashtable<Key, Value, Hasher>::containsKey(const key_type& key) const{
  return bucket_contain_key(key, get_bucket_id(m_hasher(key)));
}

template<class Key, class Value, class Hasher>
void Hashtable<Key, Value, Hasher>::clear(){
  //remove elements in the hashtable and set the m_bucket_count to default
  de_allocate();
  m_current_size = 0;
  m_bucket_count = 101;
  m_buckets = new node_pointer[m_bucket_count];
  memset(m_buckets, 0, sizeof(m_buckets) * m_bucket_count);
  m_before_node = new hash_node<key_type, value_type>();
}

template<class Key, class Value, class Hasher>
void Hashtable<Key, Value, Hasher>::insert_unique_node(node_pointer node, const key_type& key, size_type bkt_id){
  if (!bucket_contain_key(key, bkt_id)){
    insert_bucket_begin(node, bkt_id);
    if(++m_current_size > 10 * m_bucket_count)
      rehash();
  }
}

template<class Key, class Value, class Hasher>
void Hashtable<Key, Value, Hasher>::insert_bucket_begin(node_pointer node, size_type bkt_id){
  //if the bucket is not empty, then insert the node to the beginning
  if (m_buckets[bkt_id]){
    node->next = m_buckets[bkt_id]->next;
    m_buckets[bkt_id]->next = node;
  }else{
  //if the bucket is empty, then insert it to the beginning and update m_before_node
    node->next = m_before_node->next;
    m_before_node->next = node;
    //if node->next is not empty, then we should update former begin bucket that 
    //is pointing to the m_before_node
    if (node->next){
      m_buckets[node->next->bucket_id] = node;
    }
    m_buckets[bkt_id] = m_before_node;
  }
}

template<class Key, class Value, class Hasher>
void Hashtable<Key, Value, Hasher>::remove_node(node_pointer node, const key_type& key, size_type bkt_id){
  if (bucket_contain_key(key, bkt_id)){
    //if the node is at the beginning of bucket
    if (m_buckets[bkt_id]->next == node){
      remove_bucket_begin(node, bkt_id);
    }else{
      node_pointer ptr = m_buckets[bkt_id]->next;
      while(ptr->next != node)
        ptr = ptr->next;
      ptr->next = node->next;
      delete node;
  }
  m_current_size--;
  }
}

template<class Key, class Value, class Hasher>
void Hashtable<Key, Value, Hasher>::remove_bucket_begin(node_pointer node, size_type bkt_id){
  if (!node->next || node->next->bucket_id != bkt_id){
    //bucket is now empty
    m_buckets[bkt_id]->next = node->next;
    m_buckets[bkt_id] = NULL;
  }else{
    m_buckets[bkt_id]->next = node->next;
  }
  delete node;
}

template<class Key, class Value, class Hasher>
bool Hashtable<Key, Value, Hasher>::bucket_contain_key(const key_type& key, size_type bkt_id) const{
  //check whether this bucket contains the given key node
  if (m_buckets[bkt_id] == NULL) 
    return false;
  node_pointer ptr = m_buckets[bkt_id]->next;
  for (; ptr && ptr->key != key; ptr = ptr->next) {}
  return ptr == NULL ? false : true;
}

template<class Key, class Value, class Hasher>
bool Hashtable<Key, Value, Hasher>::contain_value(const value_type& value) const{
  node_pointer ptr = m_before_node->next;
  while (ptr){
    if (ptr->value == value)
      return true;
    ptr = ptr->next;
  }
  return false;
}

template<class Key, class Value, class Hasher>
void Hashtable<Key, Value, Hasher>::rehash(){
  //simple rehash policy:
  //if m_current_size exceeds 10*m_bucket_count, then double the m_bucket_count
  delete m_buckets;
  m_bucket_count *= 2;
  m_buckets = new node_pointer[m_bucket_count];
  memset(m_buckets, 0, sizeof(m_buckets) * m_bucket_count);
  node_pointer ptr = m_before_node->next;
  node_pointer before_ptr = m_before_node;
  while(ptr != NULL){
    ptr->bucket_id = get_bucket_id(ptr->hash_code);
    if (m_buckets[ptr->bucket_id] == NULL)
      m_buckets[ptr->bucket_id] = before_ptr;
    ptr = ptr->next;
    before_ptr = before_ptr->next;
  }
}

template<class Key, class Value, class Hasher>
size_t Hashtable<Key, Value, Hasher>::get_bucket_id(size_type hash_code) const{
  size_type bucket_id = hash_code % m_bucket_count;
  return bucket_id;
}

template<class Key, class Value, class Hasher>
void Hashtable<Key, Value, Hasher>::de_allocate(){
  delete m_buckets;
  node_pointer ptr = m_before_node->next;
  while (ptr){
    node_pointer tmp = ptr->next;
    delete ptr;
    ptr = tmp;
  }
  delete m_before_node;
}

template<class Key, class Value, class Hasher>
hash_node<Key, Value>* Hashtable<Key, Value, Hasher>::get_node_ptr(const key_type& x) const{
  node_pointer ptr =  m_before_node->next;
  while(ptr){
    if (ptr->key == x)
      return ptr;
    ptr = ptr->next;
  }
  return NULL;
}

template<class Key, class Value, class Hasher>
size_t Hashtable<Key, Value, Hasher>::get_hash_code(const key_type& key) const{
  return m_hasher(key);
}

#endif
