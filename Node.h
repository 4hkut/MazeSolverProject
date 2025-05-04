#ifndef NODE_H
#define NODE_H

#include <vector>

class Node {
public:
    int row, col;
    bool visited;
    std::vector<Node*> neighbors;
    Node* parent;

    Node(int r, int c) : row(r), col(c), visited(false), parent(nullptr) {}
};

#endif
