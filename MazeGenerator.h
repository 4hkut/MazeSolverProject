#ifndef MAZEGENERATOR_H
#define MAZEGENERATOR_H

#include <fstream>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

class MazeGenerator {
public:
    static void generateMaze(int rows, int cols, const string& filename) {
        // Initialize grid with walls
        vector<vector<char>> grid(rows, vector<char>(cols, '#'));

        srand(time(0));

        // Create a simple path
        int r = rand() % rows;   // Start row
        int c = rand() % cols;   // Start column
        grid[r][c] = 'S';        // Start position

        // Generate a simple path by randomly walking through the grid
        createSimplePath(grid, r, c, rows, cols);

        // Place the end point (E) at the farthest point from start
        int endR = rand() % rows;
        int endC = rand() % cols;
        grid[endR][endC] = 'E';  // End position

        // Save to file
        ofstream out(filename);
        if (!out) {
            cerr << "Could not create file " << filename << endl;
            return;
        }

        out << rows << " " << cols << "\n";
        for (auto& row : grid) {
            for (auto& cell : row) {
                out << cell << " ";
            }
            out << "\n";
        }

        cout << "Maze generated and saved to " << filename << endl;
    }

private:
    static void createSimplePath(vector<vector<char>>& grid, int r, int c, int rows, int cols) {
        // Move randomly in one of the 4 directions (up, down, left, right)
        vector<pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};  // up, down, left, right

        // Make sure we're within the grid bounds
        for (int i = 0; i < 50; ++i) { // Limit to 50 steps to avoid infinite loop
            int dirIndex = rand() % 4; // Randomly choose direction
            int newR = r + directions[dirIndex].first;
            int newC = c + directions[dirIndex].second;

            if (newR >= 0 && newR < rows && newC >= 0 && newC < cols && grid[newR][newC] == '#') {
                grid[newR][newC] = '.';  // Open up the cell to form the path
                r = newR;
                c = newC;
            }
        }
    }
};

#endif
