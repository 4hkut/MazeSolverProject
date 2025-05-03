#ifndef SOLVER_H
#define SOLVER_H

#include "Maze.h"
#include <stack>
#include <queue>
#include <vector>
#include <iostream>
using namespace std;

class Solver {
public:
    static bool solveDFS(Maze& maze) {
        struct Point { int r, c; };
        stack<Point> s;
        s.push({maze.getStartRow(), maze.getStartCol()});

        while (!s.empty()) {
            Point p = s.top(); s.pop();

            if (maze.getCell(p.r, p.c) == 'E') {
                cout << "DFS: Maze solved!\n";
                return true;
            }

            if (maze.getCell(p.r, p.c) != 'S')
                maze.setCell(p.r, p.c, '*');

            vector<Point> neighbors = {
                {p.r - 1, p.c}, {p.r + 1, p.c},
                {p.r, p.c - 1}, {p.r, p.c + 1}
            };

            for (auto n : neighbors) {
                if (n.r >= 0 && n.r < maze.getRows() &&
                    n.c >= 0 && n.c < maze.getCols()) {
                    char cell = maze.getCell(n.r, n.c);
                    if (cell == '.' || cell == 'E') {
                        s.push(n);
                    }
                }
            }
        }
        cout << "DFS: No path found.\n";
        return false;
    }

    static bool solveBFS(Maze& maze) {
        struct Point { int r, c; };
        queue<Point> q;
        q.push({maze.getStartRow(), maze.getStartCol()});

        while (!q.empty()) {
            Point p = q.front(); q.pop();

            if (maze.getCell(p.r, p.c) == 'E') {
                cout << "BFS: Maze solved!\n";
                return true;
            }

            if (maze.getCell(p.r, p.c) != 'S')
                maze.setCell(p.r, p.c, '+');

            vector<Point> neighbors = {
                {p.r - 1, p.c}, {p.r + 1, p.c},
                {p.r, p.c - 1}, {p.r, p.c + 1}
            };

            for (auto n : neighbors) {
                if (n.r >= 0 && n.r < maze.getRows() &&
                    n.c >= 0 && n.c < maze.getCols()) {
                    char cell = maze.getCell(n.r, n.c);
                    if (cell == '.' || cell == 'E') {
                        q.push(n);
                    }
                }
            }
        }
        cout << "BFS: No path found.\n";
        return false;
    }
};

#endif
