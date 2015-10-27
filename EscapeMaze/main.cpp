#include <iostream>
#include <list>
#include <fstream>
#include <vector>
 
using namespace std;

class Graph
{
        int V; // No. of vertices
        list<int> *adj; // Pointer to an array containing adjacency lists
    public:
        list<int> Queue;
        Graph(int V); // Constructor
        void addEdge(int v, int w); // function to add an edge to graph
        bool isReachable(int s, int d); // returns true if there is a path from s to d
};
 
Graph::Graph(int V)
{
    this->V = V;
    adj = new list<int> [V];
}
 
void Graph::addEdge(int v, int w)
{
    adj[v].push_back(w); // Add w to v’s list.
}
 
// A BFS based function to check whether d is reachable from s.
bool Graph::isReachable(int s, int d)
{
    // Base case
    if (s == d)
        return true;
 
    // Mark all the vertices as not visited
    bool *visited = new bool[V];
    for (int i = 0; i < V; i++)
        visited[i] = false;
 
    // Create a queue for BFS
    list<int> queue = this->Queue;
 
    // Mark the current node as visited and enqueue it
    visited[s] = true;
    queue.push_back(s);
 
    // it will be used to get all adjacent vertices of a vertex
    list<int>::iterator i;
 
    while (!queue.empty())
    {
        // Dequeue a vertex from queue and print it
        s = queue.front();
        queue.pop_front();
 
        // Get all adjacent vertices of the dequeued vertex s
        // If a adjacent has not been visited, then mark it visited
        // and enqueue it
        for (i = adj[s].begin(); i != adj[s].end(); ++i)
        {
            // If this adjacent node is the destination node, then return true
            if (*i == d) {
                return true;
            }
                
 
            // Else, continue to do BFS
            if (!visited[*i])
            {
                visited[*i] = true;
                queue.push_back(*i);
            }
        }
    }
 
    return false;
}

int main(int argc, char const *argv[])
{
    vector<string> maze;
    string line;
    ifstream myfile(argv[1]);
    while (getline(myfile,line))
        maze.push_back(line);

    int length = maze[0].size();
    int width = maze.size();
    int mazeSize = length * width;

    int start;
    int end;

    Graph g(mazeSize);
    for (int i = 0; i < width; i++) {
        string curr = maze[i];
        for (int j = 0; j < length; j++) {
            if (curr[j] == 'W')
                continue;
            if (curr[j] == 'S')
                start = i*length + j;
            if (curr[j] == 'E')
                end = i*length + j;
            if ((j > 0) && (curr[j-1] != 'W')) 
                g.addEdge(i*length+j, i*length+j-1);
            if ((j < length-1) && (curr[j+1] != 'W'))
                g.addEdge(i*length+j, i*length+j+1);
            if ((i > 0) && (maze[i-1][j] != 'W'))
                g.addEdge(i*length+j, (i-1)*length+j);    
            if ((i < width-1) && (maze[i+1][j] != 'W'))
                g.addEdge(i*length+j, (i+1)*length+j);
        }
    }

    if (g.isReachable(start, end)) 
        cout << "Path found" << endl;
    else
        cout << "No Path is found" << endl;

    return 0;

}