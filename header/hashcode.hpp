#ifndef HASH_CODE_H
#define HASH_CODE_H
#include <string>
struct hash_func{
  size_t operator()(const std::string& a) const{
    size_t hashcode = 0;
    for (size_t i = 0; i < a.length(); ++i)
      hashcode += a[i];
    return hashcode;
  }
  size_t operator()(const int& a) const{
    size_t hashcode = a >= 0 ? a : -1 * a;
    return hashcode;
  }
};

#endif
