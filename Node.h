#ifndef NODE_H
#define NODE_H

#include <vector>
using namespace std;

class Node {
public:
    int row, col;
    bool visited;
    vector<Node*> neighbors;
    Node* parent;

    Node(int r, int c) : row(r), col(c), visited(false), parent(nullptr) {}
};

#endif
