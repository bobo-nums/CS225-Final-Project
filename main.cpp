#include <iostream>
#include <vector>
#include "readFromFile.hpp"

using namespace std;

// int main(int argc, const char * argv[]) {

// 	std::cout << "Filename: " << argv[1] << std::endl;
	
// 	// convert file to string representation
// 	std::cout << "String Representation:" << std::endl;
// 	std::cout << file_to_string(argv[1]) << std::endl;
	
// 	// convert file to vector representation
// 	std::cout << "Vector Representation:" << std::endl;
// 	std::vector<std::string> vectorRepr = file_to_vector(argv[1]);
// 	for (auto word : vectorRepr) {
// 		std::cout << word << std::endl;
// 	}	
// }
#include "graph.h"

int main(int argc, const char* argv[]){
	vector<string> out;
	string egoNode = argv[1];
	if(argc >= 1){
		out = file_to_vector(argv[1]);
		egoNode = egoNode.substr(egoNode.find("/") + 1, egoNode.size() - egoNode.find(".") - 1);

		// for(unsigned i = 0; i < out.size(); i++)
		// 	cout << out[i] << " ";
	}

	Graph G(false, true);
	G.fillGraph(out, egoNode);

	G.DFS(egoNode);
	//G.print();
	
}