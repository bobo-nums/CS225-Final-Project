# CS 225 Final Project
## Team Members: Bowen Xiao, Richard Przybek, Nathen Smith, Vijay Gopalakrishnan

Video Link: https://www.youtube.com/watch?v=dQw4w9WgXcQ

Traversal: DFS

Covered Algorithms: Dijkstra’s Algorithm

Complex/Uncovered Algorithms: Betweenness Centrality

Dataset: http://snap.stanford.edu/data/ego-Twitter.html 

## Instructions
Download _twitter.tar.gz_ from http://snap.stanford.edu/data/ego-Twitter.html

Extract contents and place all files into a folder called _sample_dataset_ in the project directory
* Folder _sample_dataset_ should have various .circles, .edges, .egofeat, .feat, & .featnames files

Build the project and test cases using _make_ and _make test_

Run the project using the following command: _./finalproj [egoNode] [dfs, dijkstra, centrality] [source] [destination (ONLY for dijkstra)]_
* [egoNode]: The number in the file name (Ex. 12831.edges -> 12831)
* [dfs, dijkstra, centrality]: Choose which algorithm to run
* [source node]: Choose the source node to run algorithms with (any number in the .edges file)
* [destination node]: Choose the destination node. _Used only when performing Dijkstra's algorithm_
* DFS Example: ./finalproj 12831 dfs 8479062
* Dijkstra Example: ./finalproj 12831 dijkstra 20904050 13019862
* Centrality Example: ./finalproj 12831 centrality 528 

Run the test cases using the following command: ./test
