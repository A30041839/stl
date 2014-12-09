#ifndef GRAPH_H
#define GRAPH_H

#include "vector.hpp"
#include <utility>

template<class T>
struct Gnode{
  //constructor
  Gnode(): val(T()), visited(false) {}
  Gnode(T _val): val(_val), visited(false) {}

  T val;
  bool visited;
  vector<Gnode<T>* > adjacents;
};

template<class T>
class DirectedGraph{
public:
  typedef Gnode<T>* pointer_type;
  DirectedGraph() {}
  ~DirectedGraph() {
    for (int i = 0; i < m_graph.size(); ++i){
      delete m_graph[i];
    }
  }

  void insertEdge(const std::pair<T, T>& edge){
    //insert node
    insertNode(edge.first);
    insertNode(edge.second);
    //insert an edge
    pointer_type startNode = findNode(edge.first);
    pointer_type endNode = findNode(edge.second);
    int i = 0;
    for (; i < startNode->adjacents.size(); ++i){
      if (startNode->adjacents[i] == endNode){
        break;
      }
    }
    if (i == startNode->adjacents.size()){
      startNode->adjacents.push_back(endNode);
    }
  }

  void insertNode(T val){
    if (findNode(val) == NULL){
      pointer_type newNode = new Gnode<T>(val);
      //must be very careful when returing the address
      //of a vector element, because the vector may expand
      //size, which causes the previous address to be invalidated
      m_graph.push_back(newNode);
    }
  }

  pointer_type findNode(T val){
    for (int i = 0; i < m_graph.size(); ++i){
      if (m_graph[i]->val == val){
        return m_graph[i];
      }
    }
    return NULL;
  }

  vector<Gnode<T>* > m_graph;
};

#endif
