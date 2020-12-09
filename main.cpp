#include <iostream>
#include <vector>
#include "readFromFile.hpp"
#include "graph.h"
#include "edge.h"
#include <algorithm>

using namespace std;

int main(int argc, const char* argv[]){
	vector<string> edges;
	string egoNode = argv[1];
	if(argc >= 1){
		edges = file_to_vector(argv[1]);
		egoNode = egoNode.substr(egoNode.find("/") + 1, egoNode.size() - egoNode.find(".") - 1);
	}
	Graph G(false, true);
	G.fillGraph(edges, egoNode);
	//vector of vertices
	G.fillWeights();

	1364
	G.DFS(egoNode);
	//G.print();


}