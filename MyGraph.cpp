//author: Jose R de la Vega
//        801-12-2105
//        j.r.delavega17@gmail.com
#include "MyGraph.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>
#include <cmath>
#include <fstream>
using namespace std;


//--- implementacion de funciones de VecinoYPeso

int VecinoYPeso::getVecino(){
  return vecino;
}

void VecinoYPeso::setVecino(int n){
  vecino = n;
}

float VecinoYPeso::getPeso(){
  return peso;
}

void VecinoYPeso::setPeso(float n){
  peso = n;
}
//--------------------------------------------------
//---- Implementacion de funciones de digraph
void MyGraph::addVertex(){
  Vertices.push_back(Vertex(0, 0));
}

void MyGraph::addVertex(float x, float y) { 
   Vertices.push_back(Vertex(x, y));
}

//A~ade una arista de un nodo from a uno to y de to a from y les asigna un peso
void MyGraph::addEdge(int from, int to, float weight) { 
  if (from < 0 || to < 0) {
    cout << "Warning in InsertEdge: invalid node index " 
        << from << ", " << to << endl;
    return;
  }
  VecinoYPeso VP;
  VP.setVecino(to);
  VP.setPeso(weight);
  Vertices[from].adjacencyList.push_back(VP);
  VP.setVecino(from);
  Vertices[to].adjacencyList.push_back(VP);

}

//borra una arista de un nodo from a un nodo to y de to a from
void MyGraph::deleteEdge(int from, int to){
  
  for (int i = 0; i < Vertices[from].adjacencyList.size(); i++){
    if(Vertices[from].adjacencyList[i].getVecino() == to){
      Vertices[from].adjacencyList.erase(Vertices[from].adjacencyList.begin() + i);
    }
  }

  for (int j = 0; j < Vertices[to].adjacencyList.size(); j++) {
    if(Vertices[to].adjacencyList[j].getVecino() == from){
      Vertices[to].adjacencyList.erase(Vertices[to].adjacencyList.begin() + j);
    }
  }
}

//borra un vertice aunque no la uso en el programa
void MyGraph::deleteVertex(int n){
  Vertices[n].posX = -1;
  Vertices[n].posY = -1;
  for (int i = 0; i < Vertices[n].adjacencyList.size(); i++){
    Vertices[n].adjacencyList.erase(Vertices[n].adjacencyList.begin() + i);
  }

  for(int i = 0; i < Vertices.size(); i++){
    for(int j = 0; j < Vertices[i].adjacencyList.size(); j++){
      if(Vertices[i].adjacencyList[j].getVecino() == n){
        Vertices[i].adjacencyList.erase(Vertices[i].adjacencyList.begin() + j);
      }
    }
  }
}

//devuelve el numero de vecinos
int MyGraph::getNumNeighbors(int n){
  return Vertices[n].adjacencyList.size();
}

//devuelve un vector con los vecinos de un nodo n
vector<int> MyGraph::getNeighbors(int n){
  vector<int> v;
  for(int i = 0; i < Vertices[n].adjacencyList.size(); i++){
    v.push_back(Vertices[n].adjacencyList[i].vecino);
  }
  return v;
}

//devuelve la cantidad de nodos en el grafo
int MyGraph::getNumberVertices(){
  int conta = 0;
  for(int i = 0; i < Vertices.size(); i++) {
    if(Vertices[i].posX != -1){
      conta++;
    }
  }
  return conta;
}

//devuelve la cantidad de aristas en el grafo
int MyGraph::getNumberEdges(){
  int conta = 0;
  for(int i = 0; i < Vertices.size(); i++){
    for(int j = 0; j < Vertices[i].adjacencyList.size(); j++){
      if(Vertices[i].posX != -1){
        if(Vertices[i].adjacencyList[j].getVecino() > i){ //se pone que sea mayor que i para que no repitas
          conta++;                                        //las aristas ya que las aristas se guardan comomgrafos dirigidos
        }
      }
    }
  }
  return conta;
}

//calcula la distancia entre dos nodos
float MyGraph::dist(int from, int to){
  float distancia;
  float x = Vertices[from].posX;
  float y = Vertices[from].posY;
  float x2 = Vertices[to].posX;
  float y2 = Vertices[to].posY;
  distancia = sqrt(pow(x2 - x, 2) + pow(y2 - y, 2));
  return distancia;
}

//un display para orientarme cuando comenze el programa
void MyGraph::display(ostream & out)
{
  out << "Adjacency-List Representation: \n";
  for (int i = 0; i < Vertices.size(); i++) {
    if(Vertices[i].posX != -1){
      out << i << ": (" <<  Vertices[i].posX << ", " << Vertices[i].posY << ") : "; // imprime las cordenadas
    
      for (int j = 0; j < Vertices[i].adjacencyList.size(); j++){
        out << "V: " << Vertices[i].adjacencyList[j].getVecino() << "  " //imprime el vecino
            << "P: " << Vertices[i].adjacencyList[j].getPeso() << "  "; //imprime el peso
      }
    
      out << endl;
    }
  }
}

//imprime el formato que utiliza grapviz
void MyGraph::graphviz() {
  ofstream myfile;
  string dotName;
  int count = 0;

  do {
    if(count < 1)
      cout << "Please enter a name for the .dot file (add the .dot at the end): ";
    else{
      cout << "Invalid name for .dot file. Did you use de .dot?\n"
           << "Please try again: ";
    }
    cin >> dotName;
    count++;
  }while(!(dotName[dotName.length()-1] == 't' && dotName[dotName.length()-2] == 'o' && dotName[dotName.length()-3] == 'd' && dotName[dotName.length()-4] == '.'));

  myfile.open(dotName.c_str());
  myfile << "graph G {\n";
  myfile << "overlap=false;\n";
  myfile << "size = " << "\"" << size << "," << size << "\";\n";
  myfile << "node [shape=square, fixedsize=true, fontsize=5, width=.10, height=.10];";
  for(int i = 0; i < getNumberVertices(); i++){
    myfile << i << " [ pos = \"" << Vertices[i].posX << "," << Vertices[i].posY << "!\", label=\"" << i << "\"]";
    myfile << endl;
  }
  
  for(int i = 0; i < Vertices.size(); i++){
    for(int j = 0; j < Vertices[i].adjacencyList.size(); j++){
      if(Vertices[i].adjacencyList[j].getVecino() > i){ //se pone que sea mayor que i para que no repitas
        myfile << i << "--" << Vertices[i].adjacencyList[j].getVecino() << endl;//las aristas ya que las aristas se guardan como grafos dirigidos
      }
    }
  }
  myfile << "}\n";
  myfile.close();
}

//devuelve el grado maximo del grafo
int MyGraph::getMaxDegree(){
  int max = getNumNeighbors(0);
  for(int i = 1; i < Vertices.size(); i++){
    int number = getNumNeighbors(i);
    if(number > max){
      max = number;
    }
  }
  return max;
}

float MyGraph::getAvgDegree(){
  int num = 0;
  int avg;
  for(int i = 0; i < Vertices.size(); i++){
    num = num + getNumNeighbors(i);
  }
  avg = num / Vertices.size();
  return avg;
}

float MyGraph::coseno(int s, int t, int v) { 
  float a = dist(t, v);
  float b = dist(t, s);
  float c = dist(s, v);
  return (b*b + c*c - a*a) / (2*b*c);
}