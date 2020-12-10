#include <iostream>
#include <vector>
#include "readFromFile.hpp"
#include "edge.h"
#include "graph.h"

using namespace std;

//usage ./finalproj [edges filepath] [ego features filepath] [features filepath]

int main(int argc, const char* argv[]){
	vector<Vertex> edges;
	vector<Vertex> egoFeatures;
	vector<Vertex> features;
	Vertex egoNode = argv[1];
	if(argc >= 1){
		edges = file_to_vector(argv[1]);
		egoNode = egoNode.substr(egoNode.find("/") + 1, egoNode.size() - egoNode.find(".") - 1);
		egoFeatures = file_to_vector(argv[2]);
		features = file_to_vector(argv[3]);
	}

	//test for egofeatures array
	// for(unsigned i = 0; i < egoFeatures.size(); i++){
	// 	cout << egoFeatures[i] << " ";
	// }

	features.push_back(egoNode);
	for(unsigned i = 0; i < egoFeatures.size(); i++){
		features.push_back(egoFeatures[i]);
	}

	//test for features array
	// for(unsigned i = 0; i < features.size(); i++){
	// 	if(i % 1365 == 0){
	// 		cout << endl;
	// 	}
	// 	cout << features[i] << " ";
	// }

	Graph G(true, true);
	G.fillGraph(edges, features, egoNode);
	//G.DFS(egoNode);
	G.print();

	vector<Vertex> path = G.Dijkstra("663463", "12007182");
	for(unsigned i = 0; i < path.size(); i++){
		cout << path[i] << " ";
	}
	cout << endl;
	
}