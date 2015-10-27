#include <iostream>
#include <fstream>
#include <vector>
#include "Vertex.h"
#include "Graph.h"
using namespace std;

vector<string> parse_line(string line) {
    vector<string> ret;

    size_t found = line.find("<");
    if (found!=string::npos) {
        ret.push_back(line.substr(0,found));
        ret.push_back(line.substr(found+1));
        return ret;
    }

    found = line.find(">");
    if (found!=string::npos) {
        ret.push_back(line.substr(found+1));
        ret.push_back(line.substr(0,found));
        return ret;
    }

    return ret;
}

int main(int argc, char const *argv[])
{
    string line;
    ifstream myfile(argv[1]);

    getline(myfile, line);
    int N = stoi(line);
    Graph g;
    vector<Vertex> v;
    for (int i = 0; i < N; i++) {
        Vertex vertex  {  to_string(i) };
        v.push_back(vertex);
    }

    vector<string> inputs;
    while (getline(myfile,line)) {
        inputs = parse_line(line);
        for (int i = 0; i < inputs.size(); i++) {
            int vec1 = stoi(inputs[0]) - 1;
            int vec2 = stoi(inputs[1]) - 1;
            g.addEdge(&v[vec2], &v[vec1]);
        }
    }

    for (Vertex* v : g.topoSort())
        cout << stoi(v->name())+1 << " ";
    cout << '\n';
}