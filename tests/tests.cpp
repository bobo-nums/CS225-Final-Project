#include "../graph.h"
#include "../cs225/catch/catch.hpp"

TEST_CASE("Dijkstra's test", "[weight=1]"){

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

	vector<string> expected;
	vector<string> result = g.Dijkstra("one", "five");
	expected.push_back("three");
	expected.push_back("five");
	
	for(unsigned i = 0; i < expected.size(); i++){
		REQUIRE(expected[i] == result[i]);
	}
}