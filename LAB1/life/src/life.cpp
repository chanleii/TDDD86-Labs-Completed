#include <iostream>
#include "grid.h"
#include "lifeutil.h"
#include <string>
#include <fstream>

using namespace std;

void showGrid(const Grid<char> &grid);
int countNeighbours(const Grid<char> &grid, int column, int row);
void tickGrid(Grid<char> &oldGrid);

int main() {

    string filename,line;
    int rows,cols;

    cout << "Welcome to Game Of Life! \n";
    system("pause");

    clearConsole();

    cout << "Please enter grid name: ";
    cin >> filename;

    ifstream infile(filename);

    getline(infile, line);
    rows = stoi(line);
    getline(infile, line);
    cols = stoi(line);

    Grid<char> grid(rows,cols);

    //Sets values to the grid from the inputfile.
    for(int row = 0; row < rows; row++){
        getline(infile, line);
        int col = 0;
        for(char letter : line) {
            grid.set(row,col,letter);
            col++;
        }
    }

    showGrid(grid);


    while(true) {
            char gameAction = 's';
            cout << "a)nimate t)ick q)uit? " << endl;
            cin >> gameAction;

            if(gameAction == 'a') {
                for(int ticks = 0; ticks < 50; ticks++) {
                    tickGrid(grid);
                    showGrid(grid);
                    pause(100);
                }
            } else if(gameAction == 't') {
                tickGrid(grid);
                showGrid(grid);
            } else if(gameAction == 'q') {
                break;
            }
        }

    cout << "Have a nice Life! "  << endl;
    return 0;
}

void showGrid(const Grid<char> &grid) {
    /*
     * Prints the entire grid.
     */
    string gridline;
    clearConsole();

    for (int i = 0; i < grid.numRows(); i++) {
        for (int j = 0; j < grid.numCols(); j++) {
            gridline += grid.get(i,j);
        }
        cout << gridline << endl;
        gridline.clear();
    }
}

int countNeighbours(const Grid<char> &grid, int column, int row) {
    /*
     * Sets rNeighbours to the number of neighbours to a given position in grid.
     */
    int neighbours = 0;

    for(int x = column - 1; x <= column + 1; x++) {
        for(int y = row - 1; y <= row + 1; y++) {
            if(grid.inBounds(y, x) && !(x == column && y == row)) {
                if(grid.get(y, x) == 'X') {
                    neighbours++;
                }
            }
        }
    }

    return neighbours;
}

void tickGrid(Grid<char> &oldGrid) {
    /*
     * Generates the next generation of the grid based on the current state.
     */
    Grid<char> newGrid = oldGrid;
    int neighbours;

    for(int x = 0; x < oldGrid.numCols(); x++) {
        for(int y = 0; y < oldGrid.numRows(); y++) {
            neighbours = countNeighbours(oldGrid, x, y);

            if(neighbours <= 1) {
                newGrid.set(y, x, '-');
            } else if(neighbours == 3) {
                if(oldGrid.get(y, x) != 'X') { //Sätter en cell om den är tom
                    newGrid.set(y, x, 'X');
                }
            } else if(neighbours >= 4) {
                if(oldGrid.get(y, x) == 'X') {
                    newGrid.set(y, x, '-');
                }
            }
        }
    }

    oldGrid = newGrid;
}
