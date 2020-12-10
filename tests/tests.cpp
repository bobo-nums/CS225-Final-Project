#include "../graph.h"
#include "../cs225/catch/catch.hpp"

TEST_CASE("Dijkstra1 test", "[weight=1]"){

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
    expected.push_back("one");
	expected.push_back("three");
	expected.push_back("five");

	for(unsigned i = 0; i < expected.size(); i++){
		REQUIRE(expected[i] == result[i]);
	}
}
TEST_CASE("Dijkstra2 test", "[weight=1]"){

    Graph G(true, true);
    for(int i = 0; i < 8; i++){
        G.insertVertex(to_string(i));
    }

    G.insertEdge("0", "1");
    G.setEdgeWeight("0", "1", 4);
    G.insertEdge("0", "7");
    G.setEdgeWeight("0", "7", 8);
    G.insertEdge("1", "7");
    G.setEdgeWeight("1", "7", 11);
    G.insertEdge("7", "1");
    G.setEdgeWeight("7", "1", 11);
    G.insertEdge("1", "2");
    G.setEdgeWeight("1", "2", 8);
    G.insertEdge("7", "8");
    G.setEdgeWeight("7", "8", 7);
    G.insertEdge("8", "7");
    G.setEdgeWeight("8", "7", 7);
    G.insertEdge("7", "6");
    G.setEdgeWeight("7", "6", 1);
    G.insertEdge("2", "8");
    G.setEdgeWeight("2", "8", 2);
    G.insertEdge("8", "6");
    G.setEdgeWeight("8", "6", 6);
    G.insertEdge("6", "8");
    G.setEdgeWeight("6", "8", 6);
    G.insertEdge("2", "3");
    G.setEdgeWeight("2", "3", 7);
    G.insertEdge("2", "5");
    G.setEdgeWeight("2", "5", 4);
    G.insertEdge("5", "2");
    G.setEdgeWeight("5", "2", 4);
    G.insertEdge("6", "5");
    G.setEdgeWeight("6", "5", 2);
    G.insertEdge("3", "5");
    G.setEdgeWeight("3", "5", 14);
    G.insertEdge("5", "3");
    G.setEdgeWeight("5", "3", 14);
    G.insertEdge("3", "4");
    G.setEdgeWeight("3", "4", 9);
    G.insertEdge("5", "4");
    G.setEdgeWeight("5", "4", 10);

    vector<string> sol_path, test;
    sol_path.push_back("0");
    sol_path.push_back("7");
    sol_path.push_back("6");
    sol_path.push_back("5");
    sol_path.push_back("4");

    test = G.Dijkstra("0", "4");
    for(size_t i=0; i<4; i++){
        REQUIRE(test[i] == sol_path[i]);
    }
}
TEST_CASE("Dijkstra3 test", "[weight=1]"){
    Graph G(true, true);

    G.insertVertex("one");
    G.insertVertex("two");
    G.insertVertex("three");
    G.insertVertex("four");
    G.insertVertex("five");
    G.insertVertex("six");

    G.insertEdge("one", "two");
    G.setEdgeWeight("one", "two", 4);
    G.insertEdge("one", "three");
    G.setEdgeWeight("one", "three", 2);
    G.insertEdge("two", "three");
    G.setEdgeWeight("two", "three", 5);
    G.insertEdge("two", "four");
    G.setEdgeWeight("two", "four", 10);
    G.insertEdge("three", "five");
    G.setEdgeWeight("three", "five", 3);
    G.insertEdge("five", "four");
    G.setEdgeWeight("five", "four", 4);
    G.insertEdge("four", "six");
    G.setEdgeWeight("four", "six", 11);

    vector<string> sol_path, test;

    sol_path.push_back("one");
    sol_path.push_back("three");
    sol_path.push_back("five");
    sol_path.push_back("four");
    sol_path.push_back("six");

    test = G.Dijkstra("one", "six");

    for(size_t i=0; i<4; i++){
        REQUIRE(test[i] == sol_path[i]);
    }
}