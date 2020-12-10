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

	// Graph G(true, true);
	// G.fillGraph(edges, features, egoNode);
	// //G.DFS(egoNode);
	// // G.print();

	// string test1 = "663463";
	// string test2 = "9616792";
	// cout << "Test Dijkstra: " << test1 << ", " << test2 << endl;
	// vector<Vertex> path = G.Dijkstra(test1, test2);
	// for(unsigned i = 0; i < path.size(); i++){
	// 	cout << path[i] << " ";
	// }
	// cout << endl;

	Graph g(true, true);
    g.insertVertex("one");
    g.insertVertex("two");
    g.insertVertex("three");
    g.insertVertex("four");
    g.insertVertex("five");
    g.insertVertex("six");

    g.insertEdge("one", "two");
    g.setEdgeWeight("one", "two", 6);

    g.insertEdge("one", "three");
    g.setEdgeWeight("one", "three", 2);

    g.insertEdge("one", "four");
    g.setEdgeWeight("one", "four", 3);

    g.insertEdge("two", "five");
    g.setEdgeWeight("two", "five", 1);

    g.insertEdge("four", "five");
    g.setEdgeWeight("four", "five", 3);

    g.insertEdge("three", "five");
    g.setEdgeWeight("three", "five", 1);

	g.print();
    vector<string> result = g.Dijkstra("one", "five");
	for(unsigned i = 0; i < result.size(); i++){
		cout << result[i] << " ";
	}
	cout << endl;	
}