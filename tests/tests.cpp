#include "../graph.h"
#include "../cs225/catch/catch.hpp"

/** 
* ===================================================================================
*                               DFS test cases
* ===================================================================================
*/

TEST_CASE("DFS Test - No outgoing paths", "[weight=1]"){
    // https://i.gyazo.com/7cd42322c2cfd471c7841229f5e9566d.png
    Graph g(true, true);
    g.insertVertex("0");
    g.insertVertex("1");
    g.insertVertex("2");
    g.insertVertex("3");

    g.insertEdge("1", "0");
    g.insertEdge("2", "1");
    g.insertEdge("3", "0");
    g.insertEdge("3", "2");

    vector<string> expected = {"0"};
    vector<string> result = g.DFS("0");
	REQUIRE(expected[0] == result[0]);
}

TEST_CASE("DFS Test - Connected graph", "[weight=1]"){
    // https://i.gyazo.com/5774678812e25f4cba1ca83f70915514.png
    Graph g(true, true);
    g.insertVertex("0");
    g.insertVertex("1");
    g.insertVertex("2");
    g.insertVertex("3");
    g.insertVertex("4");

    g.insertEdge("0", "1");
    g.insertEdge("0", "2");
    g.insertEdge("0", "3");
    g.insertEdge("1", "3");
    g.insertEdge("1", "4");
    g.insertEdge("2", "4");
    g.insertEdge("3", "4");

    vector<string> expected = {"0", "1", "3", "4", "2"};
    vector<string> result = g.DFS("0");
    for(unsigned i = 0; i < expected.size(); i++){
		REQUIRE(expected[i] == result[i]);
	}
}

TEST_CASE("DFS Test - Disconnected graph", "[weight=1]"){
    // https://i.gyazo.com/988a156201881b465b97f8264fe2260a.png
    Graph g(true, true);
    for(int i = 0; i < 8; i++){
        g.insertVertex(to_string(i));
    }

    g.insertEdge("0", "1");
    g.insertEdge("0", "2");
    g.insertEdge("1", "2");
    g.insertEdge("1", "3");
    g.insertEdge("2", "3");
    g.insertEdge("3", "4");
    g.insertEdge("5", "7");
    g.insertEdge("7", "6");

    vector<string> expected = {"0", "1", "2", "3", "4"};
    vector<string> result = g.DFS("0");
    for(unsigned i = 0; i < expected.size(); i++){
		REQUIRE(expected[i] == result[i]);
	}

    expected = {"5", "7", "6"};
    result = g.DFS("5");
    for(unsigned i = 0; i < expected.size(); i++){
		REQUIRE(expected[i] == result[i]);
	}
}

TEST_CASE("DFS Test - Cycle", "[weight=1]"){
    // https://i.gyazo.com/1a399064a5eb5d7c1f703da15bc30f35.png
    Graph g(true, true);
    for(int i = 0; i < 8; i++){
        g.insertVertex(to_string(i));
    }

    g.insertEdge("0", "1");
    g.insertEdge("1", "3");
    g.insertEdge("2", "1");
    g.insertEdge("3", "2");
    g.insertEdge("3", "4");
    g.insertEdge("4", "5");
    g.insertEdge("5", "7");
    g.insertEdge("6", "4");
    g.insertEdge("7", "6");

    vector<string> expected = {"0", "1", "3", "2", "4", "5", "7", "6"};
    vector<string> result = g.DFS("0");
    for(unsigned i = 0; i < expected.size(); i++){
		REQUIRE(expected[i] == result[i]);
	}
}

/** 
* ===================================================================================
*                               Dijkstra test cases
* ===================================================================================
*/

TEST_CASE("Dijkstra - Basic test", "[weight=1]"){
    // https://i.gyazo.com/4d0628465e0c5cf2840c764809cefc0c.png
    Graph g(true, true);

    for(int i = 0; i < 6; i++){
        g.insertVertex(to_string(i));
    }

    g.insertEdge("0", "1");
    g.setEdgeWeight("0", "1", 4);

    g.insertEdge("0", "2");
    g.setEdgeWeight("0", "2", 2);

    g.insertEdge("1", "2");
    g.setEdgeWeight("1", "2", 5);

    g.insertEdge("1", "3");
    g.setEdgeWeight("1", "3", 10);

    g.insertEdge("2", "4");
    g.setEdgeWeight("2", "4", 3);

    g.insertEdge("4", "3");
    g.setEdgeWeight("4", "3", 4);

    g.insertEdge("3", "5");
    g.setEdgeWeight("3", "5", 11);

    vector<string> expected = {"0", "2", "4", "3", "5"};
    vector<string> result = g.Dijkstra("0", "5");
    for(unsigned i = 0; i < expected.size(); i++){
		REQUIRE(expected[i] == result[i]);
	}
}

TEST_CASE("Dijkstra Test - Advanced test", "[weight=1]"){
    // https://i.gyazo.com/1b54614f2e26ba882b6ac75e156c0758.png
    Graph g(true, true);
    for(int i = 0; i < 8; i++){
        g.insertVertex(to_string(i));
    }

    g.insertEdge("0", "1");
    g.setEdgeWeight("0", "1", 4);

    g.insertEdge("0", "7");
    g.setEdgeWeight("0", "7", 8);

    g.insertEdge("1", "7");
    g.setEdgeWeight("1", "7", 11);

    g.insertEdge("7", "1");
    g.setEdgeWeight("7", "1", 11);

    g.insertEdge("1", "2");
    g.setEdgeWeight("1", "2", 8);

    g.insertEdge("7", "8");
    g.setEdgeWeight("7", "8", 7);

    g.insertEdge("8", "7");
    g.setEdgeWeight("8", "7", 7);

    g.insertEdge("7", "6");
    g.setEdgeWeight("7", "6", 1);

    g.insertEdge("2", "8");
    g.setEdgeWeight("2", "8", 2);

    g.insertEdge("8", "6");
    g.setEdgeWeight("8", "6", 6);

    g.insertEdge("6", "8");
    g.setEdgeWeight("6", "8", 6);

    g.insertEdge("2", "3");
    g.setEdgeWeight("2", "3", 7);

    g.insertEdge("2", "5");
    g.setEdgeWeight("2", "5", 4);

    g.insertEdge("5", "2");
    g.setEdgeWeight("5", "2", 4);

    g.insertEdge("6", "5");
    g.setEdgeWeight("6", "5", 2);

    g.insertEdge("3", "5");
    g.setEdgeWeight("3", "5", 14);

    g.insertEdge("5", "3");
    g.setEdgeWeight("5", "3", 14);

    g.insertEdge("3", "4");
    g.setEdgeWeight("3", "4", 9);

    g.insertEdge("5", "4");
    g.setEdgeWeight("5", "4", 10);

    vector<string> expected = {"0", "7", "6", "5", "4"};
    vector<string> result = g.Dijkstra("0", "4");
    for(unsigned i = 0; i < expected.size(); i++){
		REQUIRE(expected[i] == result[i]);
	}
}

TEST_CASE("Dijkstra Test - Path doesn't exist", "[weight=1]"){
    // https://i.gyazo.com/8642a1dfebb404b8bdcaba153d123819.png
    Graph g(true, true);
    g.insertVertex("0");
    g.insertVertex("1");
    g.insertVertex("2");
    g.insertVertex("3");

    g.insertEdge("1", "0");
    g.setEdgeWeight("1", "0", 1);

    g.insertEdge("2", "1");
    g.setEdgeWeight("2", "1", 2);

    g.insertEdge("3", "0");
    g.setEdgeWeight("3", "0", 4);

    g.insertEdge("3", "2");
    g.setEdgeWeight("3", "2", 6);

    vector<string> result = g.Dijkstra("0", "3");
	REQUIRE(result.size() == 0);

    result = g.Dijkstra("1", "2");
    REQUIRE(result.size() == 0);
}

TEST_CASE("Dijkstra Test - Connected graph", "[weight=1]"){
    // https://i.gyazo.com/1ceb26b442364c8fa052f676c5c14ce4.png
    Graph g(true, true);
    g.insertVertex("0");
    g.insertVertex("1");
    g.insertVertex("2");
    g.insertVertex("3");
    g.insertVertex("4");

    g.insertEdge("0", "1");
    g.setEdgeWeight("0", "1", 1);

    g.insertEdge("0", "2");
    g.setEdgeWeight("0", "2", 0);

    g.insertEdge("0", "3");
    g.setEdgeWeight("0", "3", 2);

    g.insertEdge("1", "4");
    g.setEdgeWeight("1", "4", 1);

    g.insertEdge("2", "4");
    g.setEdgeWeight("2", "4", 5);

    g.insertEdge("3", "4");
    g.setEdgeWeight("3", "4", 1);

    vector<string> expected = {"0", "1", "4"};
    vector<string> result = g.Dijkstra("0", "4");
    for(unsigned i = 0; i < expected.size(); i++){
		REQUIRE(expected[i] == result[i]);
	}
}

TEST_CASE("Dijkstra Test - Disconnected graph", "[weight=1]"){
    // https://i.gyazo.com/a71f8359d9cfd74ac01e002872850122.png
    Graph g(true, true);
	for(int i = 0; i < 8; i++){
        g.insertVertex(to_string(i));
    }

	g.insertEdge("0", "1");
	g.setEdgeWeight("0", "1", 6);

	g.insertEdge("0", "2");
	g.setEdgeWeight("0", "2", 2);

	g.insertEdge("0", "3");
	g.setEdgeWeight("0", "3", 3);

	g.insertEdge("1", "4");
	g.setEdgeWeight("1", "4", 1);

	g.insertEdge("3", "4");
	g.setEdgeWeight("3", "4", 3);

	g.insertEdge("2", "4");
	g.setEdgeWeight("2", "4", 1);

    g.insertEdge("5", "6");
	g.setEdgeWeight("5", "6", 1);

    g.insertEdge("5", "7");
	g.setEdgeWeight("5", "7", 5);

	vector<string> expected = {"0", "2", "4"};
	vector<string> result = g.Dijkstra("0", "4");
	for(unsigned i = 0; i < expected.size(); i++){
		REQUIRE(expected[i] == result[i]);
	}
}

TEST_CASE("Dijkstra Test - Cycle", "[weight=1]"){
    // https://i.gyazo.com/2366899155803252516eded8fb0440ca.png
    Graph g(true, true);
    for(int i = 0; i < 8; i++){
        g.insertVertex(to_string(i));
    }

    g.insertEdge("0", "1");
    g.setEdgeWeight("0", "1", 2);

    g.insertEdge("1", "3");
    g.setEdgeWeight("1", "3", 3);

    g.insertEdge("2", "1");
    g.setEdgeWeight("2", "1", 1);

    g.insertEdge("3", "2");
    g.setEdgeWeight("3", "2", 1);

    g.insertEdge("3", "4");
    g.setEdgeWeight("3", "4", 5);

    g.insertEdge("4", "5");
    g.setEdgeWeight("4", "5", 2);

    g.insertEdge("5", "7");
    g.setEdgeWeight("5", "7", 4);

    g.insertEdge("6", "4");
    g.setEdgeWeight("6", "4", 1);

    g.insertEdge("7", "6");
    g.setEdgeWeight("7", "6", 1);

    vector<string> expected = {"0", "1", "3", "4", "5", "7"};
    vector<string> result = g.Dijkstra("0", "7");
    for(unsigned i = 0; i < expected.size(); i++){
		REQUIRE(expected[i] == result[i]);
	}
}
