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

TEST_CASE("Dijkstra Test - No outgoing paths", "[weight=1]"){
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

    G.insertVertex("1");
    G.insertVertex("2");
    G.insertVertex("3");
    G.insertVertex("4");
    G.insertVertex("5");
    G.insertVertex("6");

    G.insertEdge("1", "2");
    G.setEdgeWeight("1", "2", 4);
    G.insertEdge("1", "3");
    G.setEdgeWeight("1", "3", 2);
    G.insertEdge("2", "3");
    G.setEdgeWeight("2", "3", 5);
    G.insertEdge("2", "4");
    G.setEdgeWeight("2", "4", 10);
    G.insertEdge("3", "5");
    G.setEdgeWeight("3", "5", 3);
    G.insertEdge("5", "4");
    G.setEdgeWeight("5", "4", 4);
    G.insertEdge("4", "6");
    G.setEdgeWeight("4", "6", 11);

    vector<string> sol_path, test;

    sol_path.push_back("1");
    sol_path.push_back("3");
    sol_path.push_back("5");
    sol_path.push_back("4");
    sol_path.push_back("6");

    test = G.Dijkstra("1", "6");

    for(size_t i=0; i<4; i++){
        REQUIRE(test[i] == sol_path[i]);
    }
}