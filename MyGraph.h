//author: Jose R de la Vega
//        801-12-2105
//        j.r.delavega17@gmail.com

#ifndef MYGRAPH_H
#define MYGRAPH_H

#include <list>
#include <vector>
#include <queue>
#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;

class VecinoYPeso {
protected:
  int vecino;
  float peso;

public:
  VecinoYPeso() {vecino = -1; peso = 0;}
  VecinoYPeso(int v, float p) {vecino = v; peso = p;}
  VecinoYPeso(int v) {vecino = v; peso = 0;}
  int getVecino();
  void setVecino(int n);
  float getPeso();
  void setPeso(float n);
  friend class wirelessNetwork;
  friend class MyGraph;
};

class MyGraph {
 public:
  /***** Function Members *****/
  void addVertex();
  void addVertex(float x, float y);
  void addEdge(int from, int to, float weight);
  void deleteVertex(int n);
  void deleteEdge(int from, int to);
  int getNumberVertices();
  int getNumberEdges();
  int getNumNeighbors(int n);
  vector<int> getNeighbors(int n);
  float dist(int from, int to);
  void graphviz();
  void display(ostream & out);
  void depthFirstSearch(int start);
  int getMaxDegree();
  float getAvgDegree();
  float coseno(int s, int t, int v);
 
  /***** "Head nodes" of adjacency lists *****/
   class Vertex
   {
    public: 
     float posX;
     float posY;
     vector<VecinoYPeso> adjacencyList;
     Vertex() {};
     Vertex(float x, float y) { posX = x; posY = y;}
   }; // end of Vertex class

  /***** Data Member *****/
   vector<Vertex> Vertices;
   float size;
  

};

#endif