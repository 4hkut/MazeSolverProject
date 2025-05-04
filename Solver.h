#ifndef SOLVER_H
#define SOLVER_H

#include "Node.h"     
#include "Graph.h"
#include "Maze.h"
#include <stack>
#include <queue>
using namespace std;

class Solver {
public:
    static bool solveDFS(Maze& maze) {
        Graph* graph = maze.toGraph();  
        Node* start = graph->getNode(maze.getStartRow(), maze.getStartCol());
        Node* end = graph->getNode(maze.getEndRow(), maze.getEndCol());

        if (!start || !end) return false;

        stack<Node*> s;
        s.push(start);
        start->visited = true;

        while (!s.empty()) {
            Node* current = s.top(); s.pop();

            if (current == end) {
                markPath(current, maze);
                delete graph;
                return true;
            }

            for (Node* neighbor : current->neighbors) {
                if (!neighbor->visited) {
                    neighbor->visited = true;
                    neighbor->parent = current;
                    s.push(neighbor);
                }
            }
        }

        delete graph;
        return false;
    }

    static bool solveBFS(Maze& maze) {
        Graph* graph = maze.toGraph();
        Node* start = graph->getNode(maze.getStartRow(), maze.getStartCol());
        Node* end = graph->getNode(maze.getEndRow(), maze.getEndCol());

        if (!start || !end) return false;

        queue<Node*> q;
        q.push(start);
        start->visited = true;

        while (!q.empty()) {
            Node* current = q.front(); q.pop();

            if (current == end) {
                markPath(current, maze);
                delete graph;
                return true;
            }

            for (Node* neighbor : current->neighbors) {
                if (!neighbor->visited) {
                    neighbor->visited = true;
                    neighbor->parent = current;
                    q.push(neighbor);
                }
            }
        }

        delete graph;
        return false;
    }

private:
    static void markPath(Node* endNode, Maze& maze) {
        Node* current = endNode->parent;
        while (current && current->parent) {
            maze.setCell(current->row, current->col, '*'); // or your marker
            current = current->parent;
        }
    }
};

#endif
