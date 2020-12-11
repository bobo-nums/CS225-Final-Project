#include "graph.h"
#include <stack>
#include <queue>
using namespace std;

const Vertex Graph::InvalidVertex = "_CS225INVALIDVERTEX";
const int Graph::InvalidWeight = INT_MIN;
const string Graph:: InvalidLabel = "_CS225INVALIDLABEL";
const Edge Graph::InvalidEdge = Edge(Graph::InvalidVertex, Graph::InvalidVertex, Graph::InvalidWeight, Graph::InvalidLabel);

Graph::Graph(bool weighted) : weighted(weighted),directed(false)
{
}

Graph::Graph(bool weighted, bool directed) : weighted(weighted),directed(directed)
{
}


// =============================================================================================================
void Graph::fillGraph(vector<Vertex> edges, vector<string> features, string egoNode, unsigned numFeatures){
    this->insertVertex(egoNode);
    //iterate through vector of edges and add all vertices
    //do not worry about duplicates
    for(unsigned i = 0; i < edges.size(); i++){
        this->insertVertex(edges[i]);
        this->insertEdge(egoNode, edges[i]);
    }
  
    //iterate through sets of vertices to insert edges
    for(unsigned i = 0; i < edges.size(); i+=2){
        this->insertEdge(edges[i], edges[i+1]);
    }

    unsigned data_interval = numFeatures;
    for(unsigned i = 0; i < features.size(); i += data_interval){
        for(unsigned j = i+1; j < i + data_interval; j++){
            feature_map[features[i]].push_back(features[j]);
        }
    }
    fillWeights();
}

void Graph::fillWeights(){
    vector<Edge> edges = this->getEdges();
    for(Edge e : edges){
        Vertex source = e.source;
        Vertex dest = e.dest;
        unsigned num_common = intersection(feature_map[source], feature_map[dest]);

        this->setEdgeWeight(source, dest, num_common);
    }
}

int Graph::intersection(vector<string> &v1, vector<string> &v2){
    int sum = 0;
    for(unsigned i = 0; i < v1.size(); i++){
        if(v1[i] == v2[i] && v1[i] == "1" && v2[i] == "1"){
            sum++;
        }
    }
    return 1364 - sum;
}

vector<string> Graph::DFS(string start_vertex){
    vector<string> result;
    set<string> visited; 
    
    stack<string> stk;
    stk.push(start_vertex);
    string curr_vertex;

    while(!stk.empty()){
        curr_vertex = stk.top();
        stk.pop();

        if(visited.find(curr_vertex) == visited.end()){
            result.push_back(curr_vertex);
            visited.insert(curr_vertex);
        }

        for(string neighbor : getAdjacent(curr_vertex)){
            if(visited.find(neighbor) == visited.end()){
                stk.push(neighbor);
            }
        }
    }
    return result;
}

vector<string> Graph::Dijkstra(string source, string destination){
    //struct for comparison function of priority queue
    struct CompareWeight { 
        bool operator()(std::pair<string, int> const& a, std::pair<string, int> const& b) 
        { 
            //return true if vertex a's value > vertex b's value
            return a.second > b.second; 
        } 
    };

    vector<Vertex> vertices = this->getVertices();
    std::unordered_map<string, int> distances;  // initialize tentative distance values for each vertex
    std::unordered_map<string, string> prev_map;   // initialize a map that maps current vertex -> its previous vertex
    typedef std::priority_queue<std::pair<string, int>, vector<std::pair<string, int>>, CompareWeight> myqueue;
    myqueue q;   // initialize the priority queue of vertex distance pairs
    std::set<string> visited;   //initialize visited set to check which vertices have been visited

    // Check if source has outgoing edges
    vector<Vertex> adj = this->getAdjacent(source);
    if(adj.empty()){
        return vector<Vertex>();
    }

    for(Vertex v : vertices){
        distances[v] = INT_MAX;
    }
    distances[source] = 0;
    q.push(std::pair<string, int>(source, 0));

    while(q.top().first != destination && !q.empty()){
        //get the pair from priority_queue
        std::pair<string, int> curr_node = q.top();
        string curr_vertex = curr_node.first;
        q.pop();

        //mark current node as visited
        visited.insert(curr_vertex);
        
        vector<string> neighbors = this->getAdjacent(curr_vertex);
        for(string neighbor : neighbors){
            if(visited.find(neighbor) == visited.end()){
                int dist = distances[curr_vertex] + this->getEdgeWeight(curr_vertex, neighbor);
                if(dist <= distances[neighbor]){
                    distances[neighbor] = dist;
                    prev_map[neighbor] = curr_vertex;
                    q.push(std::pair<string, int>(neighbor, dist));
                }
            }
        }
    }

    if(prev_map.find(destination) == prev_map.end()){
        return vector<Vertex>();
    } 
  
    //extract path from previous
    vector<string> path;
    string curr = destination;
    while(curr != source){
        path.push_back(curr);
        curr = prev_map[curr];
    }
    path.push_back(source);
    std::reverse(path.begin(), path.end());
    return path;
}

int Graph::centrality(Vertex vertex){
    vector<Vertex> vertices = this->getVertices();
    unordered_map<Vertex, int> dict_of_measures;

    // Go through every combination of two vertices, and store the frequency of each node in a map
    for(unsigned i = 0; i < vertices.size()-1; i++){
        for(unsigned j = i+1; j < vertices.size(); j++){
            vector<Vertex> path = Dijkstra(vertices[i], vertices[j]);
            vector<Vertex> reversePath = Dijkstra(vertices[j], vertices[i]);
            if(path.size() > 2){
                for(unsigned k = 1; k < path.size()-1; k++){
                    dict_of_measures[path[k]] = dict_of_measures[path[k]] + 1;
                }
            }
            if(reversePath.size() > 2){
                for(unsigned k = 1; k < reversePath.size()-1; k++){
                    dict_of_measures[reversePath[k]] = dict_of_measures[reversePath[k]] + 1;
                }
            }
        }
    }
    return dict_of_measures[vertex];
}
// =============================================================================================================


vector<Vertex> Graph::getAdjacent(Vertex source) const 
{
    auto lookup = adjacency_list.find(source);

    if(lookup == adjacency_list.end())
        return vector<Vertex>();

    else
    {
        vector<Vertex> vertex_list;
        unordered_map <Vertex, Edge> & map = adjacency_list[source];
        for (auto it = map.begin(); it != map.end(); it++)
        {
            vertex_list.push_back(it->first);
        }
        return vertex_list;
    }
}


Vertex Graph::getStartingVertex() const
{
    return adjacency_list.begin()->first;
}

vector<Vertex> Graph::getVertices() const
{
    vector<Vertex> ret;

    for(auto it = adjacency_list.begin(); it != adjacency_list.end(); it++)
    {
        ret.push_back(it->first);
    }

    return ret;
}

Edge Graph::getEdge(Vertex source , Vertex destination) const
{
    if(assertEdgeExists(source, destination, __func__) == false)
        return Edge();
    Edge ret = adjacency_list[source][destination];
    return ret;
}

vector<Edge> Graph::getEdges() const
{
    if (adjacency_list.empty())
        return vector<Edge>();

    vector<Edge> ret;
    set<pair<Vertex, Vertex>> seen;

    for (auto it = adjacency_list.begin(); it != adjacency_list.end(); it++)
    {
        Vertex source = it->first;
        for (auto its = adjacency_list[source].begin(); its != adjacency_list[source].end(); its++)
        {
            Vertex destination = its->first;
            if(seen.find(make_pair(source, destination)) == seen.end())
            {
                //this pair is never added to seen
                ret.push_back(its->second);
                seen.insert(make_pair(source,destination));
                if(!directed)
                {
                    seen.insert(make_pair(destination, source));
                }
            }
        }
    }

    return ret;
}

bool Graph::vertexExists(Vertex v) const
{
    return assertVertexExists(v, "");
}

bool Graph::edgeExists(Vertex source, Vertex destination) const
{
    return assertEdgeExists(source, destination, "");
}

Edge Graph::setEdgeLabel(Vertex source, Vertex destination, string label)
{
    if (assertEdgeExists(source, destination, __func__) == false)
        return InvalidEdge;
    Edge e = adjacency_list[source][destination];
    Edge new_edge(source, destination, e.getWeight(), label);
    adjacency_list[source][destination] = new_edge;

    if(!directed)
    {
        Edge new_edge_reverse(destination,source, e.getWeight(), label);
        adjacency_list[destination][source] = new_edge_reverse;
    }
    return new_edge;
}


string Graph::getEdgeLabel(Vertex source, Vertex destination) const
{
    if(assertEdgeExists(source, destination, __func__) == false)
        return InvalidLabel;
    return adjacency_list[source][destination].getLabel();
}

int Graph::getEdgeWeight(Vertex source, Vertex destination) const
{
    if (!weighted)
        error("can't get edge weights on non-weighted graphs!");

    if(assertEdgeExists(source, destination, __func__) == false)
        return InvalidWeight;
    return adjacency_list[source][destination].getWeight();
}

void Graph::insertVertex(Vertex v)
{
    // will overwrite if old stuff was there
    removeVertex(v);
    // make it empty again
    adjacency_list[v] = unordered_map<Vertex, Edge>();
}


Vertex Graph::removeVertex(Vertex v)
{

    if (adjacency_list.find(v) != adjacency_list.end())
    {
        if(!directed){
            for (auto it = adjacency_list[v].begin(); it != adjacency_list[v].end(); it++)
            {
                Vertex u = it->first;
                adjacency_list[u].erase(v); 
            }
            adjacency_list.erase(v);
            return v;
        }
        
        adjacency_list.erase(v);
        for(auto it2 = adjacency_list.begin(); it2 != adjacency_list.end(); it2++)
        {
            Vertex u = it2->first;
            if (it2->second.find(v)!=it2->second.end())
            {
                it2->second.erase(v);
            }
        }
        return v;
    }

    return InvalidVertex;
}

bool Graph::insertEdge(Vertex source, Vertex destination)
{
    if(adjacency_list.find(source)!= adjacency_list.end() 
    && adjacency_list[source].find(destination)!= adjacency_list[source].end())
    {
        //edge already exists
        return false;
    }

    if(adjacency_list.find(source)==adjacency_list.end())
    {
        adjacency_list[source] = unordered_map<Vertex, Edge>();
    }
        //source vertex exists
    adjacency_list[source][destination] = Edge(source, destination);
    if(!directed)
    {
        if(adjacency_list.find(destination)== adjacency_list.end())
        {
            adjacency_list[destination] = unordered_map<Vertex, Edge>();
        }
        adjacency_list[destination][source] = Edge(source, destination);
    }
    
    return true;
}

Edge Graph::removeEdge(Vertex source, Vertex destination)
{
    if(assertEdgeExists(source, destination, __func__) == false)
        return InvalidEdge;
    Edge e = adjacency_list[source][destination];
    adjacency_list[source].erase(destination);
    // if undirected, remove the corresponding edge
    if(!directed)
    {
        adjacency_list[destination].erase(source);
    }
    return e;
}


Edge Graph::setEdgeWeight(Vertex source, Vertex destination, int weight)
{
    if (assertEdgeExists(source, destination, __func__) == false)
        return InvalidEdge;
    Edge e = adjacency_list[source][destination];
    //std::cout << "setting weight: " << weight << std::endl;
    Edge new_edge(source, destination, weight, e.getLabel());
    adjacency_list[source][destination] = new_edge;

    if(!directed)
        {
            Edge new_edge_reverse(destination,source, weight, e.getLabel());
            adjacency_list[destination][source] = new_edge_reverse;
        }

    return new_edge;
}

bool Graph::assertVertexExists(Vertex v, string functionName) const
{
    if (adjacency_list.find(v) == adjacency_list.end())
    {
        if (functionName != "")
            error(functionName + " called on nonexistent vertices");
        return false;
    }
    return true;
}

bool Graph::assertEdgeExists(Vertex source, Vertex destination, string functionName) const
{
    if(assertVertexExists(source,functionName) == false)
        return false;
    if(adjacency_list[source].find(destination)== adjacency_list[source].end())
    {
        if (functionName != "")
            error(functionName + " called on nonexistent edge " + source + " -> " + destination);
        return false;
    }

    if(!directed)
    {
        if (assertVertexExists(destination,functionName) == false)
            return false;
        if(adjacency_list[destination].find(source)== adjacency_list[destination].end())
        {
            if (functionName != "")
                error(functionName + " called on nonexistent edge " + destination + " -> " + source);
            return false;
        }
    }
    return true;
}

bool Graph::isDirected() const
{
    return directed;
}

void Graph::clear()
{
    adjacency_list.clear();
}


/**
 * Prints a graph error and quits the program.
 * The program is exited with a segfault to provide a stack trace.
 * @param message - the error message that is printed
 */
void Graph::error(string message) const
{
    cerr << "\033[1;31m[Graph Error]\033[0m " + message << endl;
}

/**
 * Creates a name for snapshots of the graph.
 * @param title - the name to save the snapshots as
 */
void Graph::initSnapshot(string title)
{
    picNum = 0;
    picName = title;
}

/**
 * Saves a snapshot of the graph to file.
 * initSnapshot() must be run first.
 */
void Graph::snapshot()
{
    std::stringstream ss;
    ss << picNum;
    string newName = picName + ss.str();
    savePNG(newName);
    ++picNum;
}

/**
 * Prints the graph to stdout.
 */
void Graph::print() const
{
    for (auto it = adjacency_list.begin(); it != adjacency_list.end(); ++it) 
    {
        cout << it->first << endl;
        for (auto it2 = it->second.begin(); it2 != it->second.end(); ++it2) 
        {
            std::stringstream ss;
            ss << it2->first; 
            string vertexColumn = "    => " + ss.str();
            vertexColumn += " " ;
            cout << std::left << std::setw(26) << vertexColumn;
            string edgeColumn = "edge label = \"" + it2->second.getLabel()+ "\"";
            cout << std::left << std::setw(26) << edgeColumn;
            if (weighted)
                cout << "weight = " << it2->second.getWeight();
            cout << endl;
        }
        cout << endl;
    }
}

/**
 * Saves the graph as a PNG image.
 * @param title - the filename of the PNG image
 */
void Graph::savePNG(string title) const
{
    std::ofstream neatoFile;
    string filename = "images/" + title + ".dot";
    neatoFile.open(filename.c_str());

    if (!neatoFile.good())
        error("couldn't create " + filename + ".dot");

    neatoFile
        << "strict graph G {\n"
        << "\toverlap=\"false\";\n"
        << "\tdpi=\"1300\";\n"
        << "\tsep=\"1.5\";\n"
        << "\tnode [fixedsize=\"true\", shape=\"circle\", fontsize=\"7.0\"];\n"
        << "\tedge [penwidth=\"1.5\", fontsize=\"7.0\"];\n";

    vector<Vertex> allv = getVertices();
    //lambda expression
    sort(allv.begin(), allv.end(), [](const Vertex& lhs, const Vertex& rhs) {
        return stoi(lhs.substr(3)) > stoi(rhs.substr(3));
    });

    int xpos1 = 100;
    int xpos2 = 100;
    int xpos, ypos;
    for (auto it : allv) {
        string current = it;
        neatoFile 
            << "\t\"" 
            << current
            << "\"";
        if (current[1] == '1') {
            ypos = 100;
            xpos = xpos1;
            xpos1 += 100;
        }
        else {
            ypos = 200;
            xpos = xpos2;
            xpos2 += 100;
        }
        neatoFile << "[pos=\""<< xpos << "," << ypos <<"\"]";
        neatoFile << ";\n";
    }

    neatoFile << "\tedge [penwidth=\"1.5\", fontsize=\"7.0\"];\n";

    for (auto it = adjacency_list.begin(); it != adjacency_list.end(); ++it) 
    {
        for (auto it2 = it->second.begin(); it2 != it->second.end(); ++it2) 
        {
            string vertex1Text = it->first;
            string vertex2Text = it2->first;

            neatoFile << "\t\"" ;
            neatoFile << vertex1Text;
            neatoFile << "\" -- \"" ;
            neatoFile << vertex2Text;
            neatoFile << "\"";

            string edgeLabel = it2->second.getLabel();
            if (edgeLabel == "WIN") {
                neatoFile << "[color=\"blue\"]";
            } else if (edgeLabel == "LOSE") {
                neatoFile << "[color=\"red\"]";                
            } else {
                neatoFile << "[color=\"grey\"]";
            }
            if (weighted && it2->second.getWeight() != -1)
                neatoFile << "[label=\"" << it2->second.getWeight() << "\"]";
            
            neatoFile<< "[constraint = \"false\"]" << ";\n";
        }
    }

    neatoFile << "}";
    neatoFile.close();
    string command = "neato -n -Tpng " + filename + " -o " + "images/" + title
                     + ".png 2> /dev/null";
    int result = system(command.c_str());


    if (result == 0) {
        cout << "Output graph saved as images/" << title << ".png" << endl;
    } else {
        cout << "Failed to generate visual output graph using `neato`. Install `graphviz` or `neato` to generate a visual graph." << endl;
    }

    string rmCommand = "rm -f " + filename + " 2> /dev/null";
    system(rmCommand.c_str());
}

