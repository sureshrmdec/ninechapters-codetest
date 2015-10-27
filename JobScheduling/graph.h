#include <vector>
#include <unordered_map>

class Graph
{
public:
    template<typename T>
    using VertexMap     = std::unordered_map<Vertex*, T>;
    using AdjacencyList = VertexMap<std::vector<Vertex*>>;

    void addEdge(Vertex* u, Vertex* v);

    std::vector<Vertex*> topoSort();

    VertexMap<int> indegrees() const;
    int indegree(Vertex*) const;

    const AdjacencyList& adjacencyList() const;
private:
    AdjacencyList _vertices;
};

void Graph::addEdge(Vertex* u, Vertex* v)
{
    _vertices[v];               // initialise adjacency list for v
    _vertices[u].push_back(v);  // add v as being adjacent to u
}

enum Colour { White, Grey, Black };

void topoSortVertex(Vertex* vertex,
                    Colour& colour,
                    const Graph::AdjacencyList& adjacencyList,
                    Graph::VertexMap<Colour>& visited,
                    std::vector<Vertex*>& sorted)
{
    colour = Grey;

    for (Vertex* neighbour : adjacencyList.at(vertex))
    {
        Colour& neighbour_colour = visited[neighbour];
        if (neighbour_colour == White)
        {
            topoSortVertex(neighbour, neighbour_colour, adjacencyList, visited, sorted);
        }
        else
        if (neighbour_colour == Grey)
        {
            throw std::runtime_error("cycle in graph");
        }
    }

    colour = Black;
    sorted.push_back(vertex);
}

std::vector<Vertex*> Graph::topoSort()
{
    VertexMap<int> indegs = indegrees();

    std::vector<Vertex*> sorted;
    sorted.reserve(indegs.size());

    VertexMap<Colour> visited;
    visited.reserve(indegs.size());

    for (auto& pair : indegs)
    {
        if (pair.second == 0) // vertex has indegree of 0
        {
            Vertex* vertex = pair.first;
            Colour& colour = visited[vertex];
            if (colour == White)
            {
                topoSortVertex(vertex, colour, _vertices, visited, sorted);
            }
        }
    }

    return sorted;
}

Graph::VertexMap<int> Graph::indegrees() const
{
    VertexMap<int> indegrees;

    for (auto& pair : _vertices)
    {
        indegrees[pair.first]; // initialise indegree for this vertex
        for (Vertex* neighbour : pair.second)
        {
            ++indegrees[neighbour];
        }
    }

    return indegrees;
}

int Graph::indegree(Vertex* v) const
{
    return indegrees().at(v);
}

const Graph::AdjacencyList& Graph::adjacencyList() const
{
    return _vertices;
}