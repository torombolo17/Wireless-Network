//author: Jose R de la Vega
//        801-12-2105
//        j.r.delavega17@gmail.com
#include "wirelessNetwork.h"
#include "MyGraph.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <cmath>
#include <ctime>
#define PI 3.14159265

using namespace std;;

wirelessNetwork::wirelessNetwork(){
	srand(time(NULL));
	float distance;
	float x = 0;
	float y = 0;
	D.size = 10;
	 //asigna coordenadas randoms a los nodos creados
	for(int i = 0; i < 500; i++){
		x = D.size * ((double) rand() / (RAND_MAX));
		y = D.size * ((double) rand() / (RAND_MAX));
		D.addVertex(x, y);
		visitados.push_back(false);
	}

	// calcula la distancia entre nodos para asignar los vecinos
	for(int i = 0; i < 500; i++){
		for(int j = i+1; j < 500; j++){
			distance = D.dist(i, j);
			if(distance <= 1){
				D.addEdge(i ,j ,distance);
			}
		}
	}
}

wirelessNetwork::wirelessNetwork(float sz, int n){
	srand(time(NULL));
	float distance;
	float x = 0; 
	float y = 0;
	D.size = sz;
	for(int i = 0; i < n; i++){
		x = D.size * ((double) rand() / (RAND_MAX));
		y = D.size * ((double) rand() / (RAND_MAX));
		D.addVertex(x, y);
		visitados.push_back(false);
	}

	for(int i = 0; i < n; i++){
		for(int j = i+1; j < n; j++){ //uso i + 1 para no a~adir el mismo nodo como vecino
			distance = D.dist(i, j);
			if(distance <= 1){
				D.addEdge(i ,j ,distance);
			}
		}
	}
}

void wirelessNetwork::topologyControl(){
	vector<int> nodesToErase; // lista que va a guardar los vecinos a borrar sus aristas
	for(int i = 0; i < D.Vertices.size(); i++ ){ //recorre todos los nodos
		vector<int> nodeNeigh;
		nodeNeigh = D.getNeighbors(i); //guarda los vecinos de el nodo

		for(int j = 0 ; j < nodeNeigh.size(); j++){ // recorre los vecinos del nodo
			vector<int> neighOfNeigh;
			neighOfNeigh = D.getNeighbors(nodeNeigh[j]);// guarda los vecinos de el vecino de nodo

			for(int k = 0 ; k < neighOfNeigh.size(); k++){ // recorre los vecinos del vecino del nodo
				if(D.dist(i,neighOfNeigh[k]) < D.dist(i, nodeNeigh[j]) &&  // comparacion de distancia entre nodos
				   D.dist(nodeNeigh[j],neighOfNeigh[k]) < D.dist(i, nodeNeigh[j])) {
					    nodesToErase.push_back(D.Vertices[i].adjacencyList[j].vecino);
				}
			}
		}
		for(int m = 0; m < nodesToErase.size(); m++){
			D.deleteEdge(i, nodesToErase[m]); // borra las arristas a los vecinos guardados en el vector
		}
		nodesToErase.clear();
	}
}

vector<int> addToList(int n, vector<int> rest){
	vector<int> newList;
	newList.push_back(n);
	for(int i = 0; i < rest.size(); i++){
		newList.push_back(rest[i]);
	}
	return newList;
}

vector<int> wirelessNetwork::compassRouting(int s, int t){
	
	vector<int> recorrido;
	if(D.Vertices[s].posX == -1 || D.Vertices[t].posX == -1) { // verifica que los nodos sean validos
		cout << "Invalid Nodes \n";
		return recorrido;
	}

	else if(s == t) { //si el nodo dado es tambien el destino
		recorrido.push_back(t);
		//visitados[s] = true;
		return recorrido;
	}
	else if(visitados[s]){
		vector<int> empty;
		return empty;
	}

	else {
		vector<int> neigh = D.getNeighbors(s);
		int num = neigh.size();

		if(num == 0){
			vector<int> empty;
			//visitados[s] = true;
			return empty;
		}

		else if(num == 1 && visitados[s] == true){
			vector<int> empty;
			visitados[s] = true;
			return empty;
		}

		else{
			double maxCoseno = -2;   //el valor inicial del coseno maximo puede ser cualquier numero menor de -1
			int next = s;
			//conseguir el vecino con el coseno maximo que seria el angulo minimo
			for (int i = 0; i < num; i++) {
				int neighbor = neigh[i];
				if (D.coseno(s, t, neighbor) > maxCoseno && visitados[s] == false) {
					maxCoseno = D.coseno(s, t, neighbor);
					next = neighbor;
				}
			}
			visitados[s] = true;
			return addToList(s, compassRouting(next, t));
		}
	}
}