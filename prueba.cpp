//author: Jose R de la Vega
//        801-12-2105
//        j.r.delavega17@gmail.com
#include "MyGraph.h"
#include "wirelessNetwork.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <cmath>
using namespace std;

void experimentOne(){
	for(int i = 500; i < 1000; i = i+50) {
		wirelessNetwork WR(10, i);
		cout << "Average degree: " << WR.D.getAvgDegree() << endl;
		cout << "Max degree: " << WR.D.getMaxDegree() << endl;
		cout << "with topology: " << endl;
		WR.topologyControl();
		cout << "Average degree: " << WR.D.getAvgDegree() << endl;
		cout << "Max degree: " << WR.D.getMaxDegree() << endl;
	}

}

void experimetTwo(wirelessNetwork H){
	srand(time(NULL));
	vector<int> ruta;
	for(int j = 0; j < 10; j++){
		int x = rand() % 1000;
		int y = rand() % 1000;
		ruta = H.compassRouting(x,y);
		if(!ruta.empty()){ 
			if(ruta[ruta.size()-1] == y){
				cout << "path found: " << endl;
				cout << "Number of nodes passed by: " << ruta.size() << endl;
				for(int i = 0; i < ruta.size(); i++){ 
					cout << ruta[i] << " ";
				}
				cout << endl;
			}
			else
				cout << "No path found \n";
		}
		else
			cout << "No path found \n";
	}
}

void experimetThree(wirelessNetwork H){
	H.topologyControl();
	experimetTwo(H);
}

int main(){

	wirelessNetwork WN(10, 1000);
	cout << "Experiment One: \n";
	experimentOne();
	cout << "===========================================\n";
	cout << "Experiment Two: \n";
	experimetTwo(WN);
	cout << "===========================================\n";
	cout << "Experiment Three: \n";
	experimetThree(WN);
	return 0;
}