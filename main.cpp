
#include "Maze.h"
#include "Solver.h"
#include "MazeGenerator.h"  // Include maze generator header
#include <iostream>
using namespace std;

int main() {
    Maze* maze = nullptr;
    Maze* originalMaze = nullptr; // Pointer to store the original maze
    string filename;
    int choice;

    while (true) {
        cout << "\n--- Maze Solver Menu ---\n";
        cout << "1. Load Maze from File\n";
        cout << "2. Print Maze\n";
        cout << "3. Solve with DFS\n";
        cout << "4. Solve with BFS\n";
        cout << "5. Save Maze to File\n";
        cout << "6. Generate Random Maze\n";
        cout << "7. Exit\n";
        cout << "Choose option: ";
        cin >> choice;

        if (choice == 1) {
            cout << "Enter filename to load: ";
            cin >> filename;
            delete maze;  // Free previous maze if any
            maze = new Maze(filename);  // Load the maze from the file
            originalMaze = new Maze(*maze);  // Save a copy of the original maze
            cout << "Maze loaded!\n\n";
        }
        else if (choice == 2) {
            if (originalMaze) {
                originalMaze->printMaze();  // Always print the original maze
            } else {
                cout << "Load a maze first.\n\n";  
            }
        }
        else if (choice == 3) {
            if (maze) {
                // Restore the original maze before solving with DFS
                *maze = *originalMaze;

                // Solve with DFS
                if (Solver::solveDFS(*maze)) {
                    cout << "DFS Solved!\n";
                    maze->printMaze();
                    
                    // Ask user if they want to save the DFS solution
                    char saveChoice;
                    cout << "Do you want to save the DFS solution? (y/n): ";
                    cin >> saveChoice;

                    if (saveChoice == 'y' || saveChoice == 'Y') {
                        string saveFilename = filename + "_DFS";
                        maze->saveToFile(saveFilename);
                        cout << "DFS solution saved to " << saveFilename << "\n\n"; 
                    }
                } else {
                    cout << "No path found (DFS).\n\n";  
                }
            } else {
                cout << "Load a maze first.\n\n";  
            }
        }
        else if (choice == 4) {
            if (maze) {
                // Restore the original maze before solving with BFS
                *maze = *originalMaze;

                // Solve with BFS
                if (Solver::solveBFS(*maze)) {
                    cout << "BFS Solved!\n";
                    maze->printMaze();
                    
                    // Ask user if they want to save the BFS solution
                    char saveChoice;
                    cout << "Do you want to save the BFS solution? (y/n): ";
                    cin >> saveChoice;

                    if (saveChoice == 'y' || saveChoice == 'Y') {
                        string saveFilename = filename + "_BFS";
                        maze->saveToFile(saveFilename);
                        cout << "BFS solution saved to " << saveFilename << "\n\n";  
                    }
                } else {
                    cout << "No path found (BFS).\n\n"; 
                }
            } else {
                cout << "Load a maze first.\n\n"; 
            }
        }
        else if (choice == 5) {
            if (maze) {
                // Save the current maze to a file
                cout << "Enter filename to save: ";
                cin >> filename;
                maze->saveToFile(filename);
                cout << "Maze saved to " << filename << "\n\n";  
            } else {
                cout << "Load a maze first.\n\n"; 
            }
        }
        else if (choice == 6) {
            int r, c;
            cout << "Enter number of rows: ";
            cin >> r;
            cout << "Enter number of columns: ";
            cin >> c;
            cout << "Enter filename to save generated maze: ";
            cin >> filename;
            MazeGenerator::generateMaze(r, c, filename);  // Generate a random maze
            cout << "\nMaze generated and saved to " << filename << "\n\n"; 
        }
        else if (choice == 7) {
            cout << "Goodbye!\n";
            break;  // Exit the program
        }
        else {
            cout << "Invalid choice. Please try again.\n\n"; 
        }
    }

    delete maze;
    delete originalMaze; // Free the original maze copy
    return 0;
}
