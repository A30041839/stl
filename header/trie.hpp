#ifndef TRIE_H
#define TRIE_H

#include <cstring>

struct Tnode{
  bool terminable;
  Tnode** next;
  Tnode(size_t capacity): terminable(false){
    next = new Tnode*[capacity];
    memset(next, 0, sizeof(next) * capacity);
  }
  ~Tnode(){delete next;}
};

template<class Hasher>
class Trie{
public:
  Trie(size_t node_capacity = 26)
  : m_node_capacity(node_capacity),
    m_size(0)
  {
   m_hasher = Hasher();
   m_root = new Tnode(node_capacity);}
  ~Trie(){releaseTrie(m_root);}

  void insert(const char* str);
  bool find(const char* str) const;
  void remove(const char* str);
  void clear();
  size_t size() const;

private:
  void releaseTrie(Tnode* node);
  Tnode* m_root;
  Hasher m_hasher;
  size_t m_node_capacity;
  size_t m_size;
};

template<class Hasher>
void Trie<Hasher>::insert(const char* str){
  if (str == NULL) return;
  Tnode* node = m_root;
  for (size_t i = 0; i < strlen(str); ++i){
    size_t index = m_hasher(str[i]);
    if (node->next[index] != 0){
      node = node->next[index];
    }else{
      node->next[index] = new Tnode(m_node_capacity);
      node = node->next[index];
    }
  }
  node->terminable = true;
  m_size++;
}

template<class Hasher>
bool Trie<Hasher>::find(const char* str) const{
  if (str == NULL) return false;
  Tnode* node = m_root;
  for (size_t i = 0; i < strlen(str); ++i){
    size_t index = m_hasher(str[i]);
    if (node->next[index] != 0){
      node = node->next[index];
    }else{
      return false;
    }
  }
  return node->terminable == true;
}

template<class Hasher>
void Trie<Hasher>::remove(const char* str){
  //若树中存在str，则将其terminable置为false
  if (str == NULL) return;
  Tnode* node = m_root;
  for (size_t i = 0; i < strlen(str); ++i){
    size_t index = m_hasher(str[i]);
    if (node->next[index] != 0){
      node = node->next[index];
    }else{
      return;
    }
  }
  node->terminable = false;
  m_size--;
}

template<class Hasher>
void Trie<Hasher>::clear(){
  releaseTrie(m_root);
  m_size = 0;
  m_root = new Tnode(m_node_capacity);
}

template<class Hasher>
void Trie<Hasher>::releaseTrie(Tnode* node){
  //递归删除整棵Trie树
  for (size_t i = 0; i < m_node_capacity; ++i){
    if (node->next[i] != 0)
      releaseTrie(node->next[i]);
  }
  delete node;
}

template<class Hasher>
size_t Trie<Hasher>::size() const{
  return m_size;
}

#endif
