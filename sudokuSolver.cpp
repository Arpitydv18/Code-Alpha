#include <iostream>
using namespace std;

#define N 9

// Function to print Sudoku grid
void printGrid(int grid[N][N]) {
    for (int row = 0; row < N; row++) {
        for (int col = 0; col < N; col++) {
            cout << grid[row][col] << " ";
        }
        cout << endl;
    }
}

// Check if placing num is valid
bool isSafe(int grid[N][N], int row, int col, int num) {
    // Check row
    for (int x = 0; x < N; x++) {
        if (grid[row][x] == num)
            return false;
    }
    // Check column
    for (int x = 0; x < N; x++) {
        if (grid[x][col] == num)
            return false;
    }
    // Check 3x3 subgrid
    int startRow = row - row % 3, startCol = col - col % 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (grid[i + startRow][j + startCol] == num)
                return false;
        }
    }
    return true;
}

// Backtracking solver
bool solveSudoku(int grid[N][N]) {
    int row, col;
    bool empty = false;

    // Find empty cell
    for (row = 0; row < N; row++) {
        for (col = 0; col < N; col++) {
            if (grid[row][col] == 0) {
                empty = true;
                break;
            }
        }
        if (empty) break;
    }

    // No empty cell = solved
    if (!empty)
        return true;

    // Try numbers 1–9
    for (int num = 1; num <= 9; num++) {
        if (isSafe(grid, row, col, num)) {
            grid[row][col] = num;

            if (solveSudoku(grid))
                return true;

            grid[row][col] = 0; // Backtrack
        }
    }
    return false;
}

int main() {
    int grid[N][N];

    cout << "Enter Sudoku grid (0 for empty cells):\n";
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> grid[i][j];
        }
    }

    if (solveSudoku(grid)) {
        cout << "\nSolved Sudoku:\n";
        printGrid(grid);
    } else {
        cout << "No solution exists.\n";
    }

    return 0;
}
