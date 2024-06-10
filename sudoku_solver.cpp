#include <iostream>
using namespace std;

const int N = 9;

// Function to print the Sudoku grid
void printGrid(int grid[N][N]) {
    for (int row = 0; row < N; row++) {
        for (int col = 0; col < N; col++)
            cout << grid[row][col] << " ";
        cout << endl;
    }
}

// Function to check if a number can be placed in the given position
bool isSafe(int grid[N][N], int row, int col, int num) {
    // Check if the number is already present in the row or column
    for (int x = 0; x < N; x++) {
        if (grid[row][x] == num || grid[x][col] == num)
            return false;
    }

    // Check if the number is already present in the 3x3 box
    int startRow = row - row % 3;
    int startCol = col - col % 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (grid[i + startRow][j + startCol] == num)
                return false;
        }
    }
    return true;
}

// Function to solve the Sudoku puzzle using backtracking
bool solveSudoku(int grid[N][N]) {
    int row, col;

    // Check if there is any unassigned position
    bool isFilled = true;
    for (row = 0; row < N; row++) {
        for (col = 0; col < N; col++) {
            if (grid[row][col] == 0) {
                isFilled = false;
                break;
            }
        }
        if (!isFilled)
            break;
    }

    // If all positions are filled, the Sudoku is solved
    if (isFilled)
        return true;

    // Try placing numbers from 1 to 9
    for (int num = 1; num <= 9; num++) {
        // Check if the number can be placed
        if (isSafe(grid, row, col, num)) {
            // Place the number if safe
            grid[row][col] = num;

            // Recursively solve the remaining grid
            if (solveSudoku(grid))
                return true;

            // If the placement doesn't lead to a solution, backtrack
            grid[row][col] = 0;
        }
    }
    return false;
}

int main() {
    int grid[N][N] = {
        {5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},
        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9}
    };

    if (solveSudoku(grid) == true)
        printGrid(grid);
    else
        cout << "No solution exists.";

    return 0;
}
