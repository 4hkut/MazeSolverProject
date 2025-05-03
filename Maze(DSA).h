#ifndef MAZE_H
#define MAZE_H

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include "Graph.h"
using namespace std;

class Maze {
private:
    vector<vector<char>> grid;
    int rows, cols;
    int startRow, startCol, endRow, endCol;
public:
    Maze(const string& filename) {
        ifstream file(filename);
        if (!file) {
            cerr << "Could not open file\n";
            exit(1);
        }
        file >> rows >> cols;
        grid.resize(rows, vector<char>(cols));
        for (int r = 0; r < rows; ++r) {
            for (int c = 0; c < cols; ++c) {
                file >> grid[r][c];
                if (grid[r][c] == 'S') { startRow = r; startCol = c; }
                if (grid[r][c] == 'E') { endRow = r; endCol = c; }
            }
        }
    }

    void printMaze() {
        for (auto& row : grid) {
            for (auto& cell : row) {
                cout << cell << " ";
            }
            cout << "\n";
        }
    }

    char getCell(int r, int c) { return grid[r][c]; }
    void setCell(int r, int c, char val) { grid[r][c] = val; }
    int getRows() { return rows; }
    int getCols() { return cols; }
    int getStartRow() { return startRow; }
    int getStartCol() { return startCol; }
    int getEndRow() { return endRow; }
    int getEndCol() { return endCol; }

    void saveToFile(const string& filename) {
        ofstream out(filename);
        out << rows << " " << cols << "\n";
        for (auto& row : grid) {
            for (auto& cell : row) {
                out << cell << " ";
            }
            out << "\n";
        }
    }

    
    Graph* toGraph() {
        Graph* graph = new Graph();

        for (int r = 0; r < rows; ++r) {
            for (int c = 0; c < cols; ++c) {
                char cell = grid[r][c];
                if (cell == 'S' || cell == 'E' || cell == '.') {
                    graph->addNode(r, c);
                }
            }
        }

        for (int r = 0; r < rows; ++r) {
            for (int c = 0; c < cols; ++c) {
                char cell = grid[r][c];
                if (cell == 'S' || cell == 'E' || cell == '.') {
                    // Check 4 directions
                    if (r > 0 && (grid[r-1][c] == '.' || grid[r-1][c] == 'E' || grid[r-1][c] == 'S'))
                        graph->addEdge(r, c, r-1, c);
                    if (r < rows-1 && (grid[r+1][c] == '.' || grid[r+1][c] == 'E' || grid[r+1][c] == 'S'))
                        graph->addEdge(r, c, r+1, c);
                    if (c > 0 && (grid[r][c-1] == '.' || grid[r][c-1] == 'E' || grid[r][c-1] == 'S'))
                        graph->addEdge(r, c, r, c-1);
                    if (c < cols-1 && (grid[r][c+1] == '.' || grid[r][c+1] == 'E' || grid[r][c+1] == 'S'))
                        graph->addEdge(r, c, r, c+1);
                }
            }
        }
        return graph;
    }
};

#endif
