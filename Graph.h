#ifndef GRAPH_H
#define GRAPH_H

#include "Node.h"   
#include <map>
#include <vector>
#include <utility>
using namespace std;

class Graph {
private:
    map<pair<int, int>, Node*> nodes;

public:
    ~Graph() {
        for (auto& pair : nodes) {
            delete pair.second;
        }
    }

    Node* addNode(int row, int col) {
        if (nodes.find({row, col}) == nodes.end()) {
            nodes[{row, col}] = new Node(row, col);
        }
        return nodes[{row, col}];
    }

    void addEdge(int r1, int c1, int r2, int c2) {
        Node* a = getNode(r1, c1);
        Node* b = getNode(r2, c2);
        if (a && b) {
            a->neighbors.push_back(b);
            b->neighbors.push_back(a);  // if undirected
        }
    }

    Node* getNode(int row, int col) {
        auto it = nodes.find({row, col});
        return it != nodes.end() ? it->second : nullptr;
    }
};

#endif
