#ifndef wirelessNetwork_H
#define wirelessNetwork_H

#include <list>
#include <vector>
#include <queue>
//author: Jose R de la Vega
//        801-12-2105
//        j.r.delavega17@gmail.com
#include <iostream>
#include <fstream>
#include <cstdlib>
#include "MyGraph.h"

using namespace std;

class wirelessNetwork : public MyGraph {
  public:
    MyGraph D;
    float size;
    vector<bool> visitados;

  public:
    wirelessNetwork();
    wirelessNetwork(float sz, int n);
    void topologyControl();
    vector<int> compassRouting(int s, int t);

};
#endif