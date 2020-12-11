#include <iostream>
#include <vector>
#include "readFromFile.hpp"
#include "edge.h"
#include "graph.h"
#include <string.h>

using namespace std;

// Usage: 	./finalproj [egoNode] [dfs, dijkstra, centrality] [source] [destination (for dijkstra)]

int main(int argc, const char* argv[]){
	// Initialize variables & parse input 
	Vertex egoNode = argv[1];
	vector<Vertex> edges;
	vector<Vertex> egoFeatures;
	vector<Vertex> features;
	vector<Vertex> featNames;
	unsigned numFeatures = 0;
	bool dfs = false;
	bool dijkstra = false;
	bool centrality = false;
	string source = "";
	string destination = "";
	if(argc >= 1){
		egoNode = argv[1];
		edges = file_to_vector("sample_dataset/" + egoNode + ".edges");
		egoFeatures = file_to_vector("sample_dataset/" + egoNode + ".egofeat");
		features = file_to_vector("sample_dataset/" + egoNode + ".feat");
		featNames = file_to_vector("sample_dataset/" + egoNode + ".featnames");
		numFeatures = (unsigned)stoi(featNames[featNames.size() - 2]) + 2;
		if(strcmp(argv[2], "dfs") == 0){
			dfs = true;
			source = argv[3];
		}
		else if(strcmp(argv[2], "dijkstra") == 0){
			dijkstra = true;
			source = argv[3];
			destination = argv[4];
		}
		else if(strcmp(argv[2], "centrality") == 0){
			centrality = true;
			source = argv[3];
		}
	}

	// Add features to our nodes
	features.push_back(egoNode);
	for(unsigned i = 0; i < egoFeatures.size(); i++){
		features.push_back(egoFeatures[i]);
	}

	// Create weighted, directed graph
	Graph G(true, true);
	G.fillGraph(edges, features, egoNode, numFeatures);

	// Print the graph
	G.print();
	
	// Run DFS
	if(dfs){
		vector<string> dfs_result = G.DFS(source);
		cout << "DFS Output" << endl;
		for(unsigned i = 0; i < dfs_result.size(); i++){
			cout << dfs_result[i] << " ";
		}
		cout << endl;
	}

	// Run Dijkstra's algorithm
	if(dijkstra){
		vector<string> dijkstra_result = G.Dijkstra(source, destination);
		cout << "Dijkstra Output" << endl;
		for(unsigned i = 0; i < dijkstra_result.size(); i++){
			cout << dijkstra_result[i] << " ";
		}
		cout << endl;
	}
	
	// Run Betweenness Centrality algorithm
	if(centrality){
		int centrality_result = G.centrality(source);
		cout << "Betweenness Centrality Output" << endl;
		cout << centrality_result;
		cout << endl;
	}
}