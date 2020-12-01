#include <iostream>
#include <vector>
#include "readFromFile.hpp"
#include "graph.h"

using namespace std;

int main(int argc, const char* argv[]){
	vector<string> out;
	string egoNode = argv[1];
	if(argc >= 1){
		out = file_to_vector(argv[1]);
		egoNode = egoNode.substr(egoNode.find("/") + 1, egoNode.size() - egoNode.find(".") - 1);
	}

	Graph G(false, true);
	G.fillGraph(out, egoNode);

	G.DFS(egoNode);
	//G.print();
}