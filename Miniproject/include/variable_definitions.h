#ifndef VARIABLES
#define VARIABLES

#include<vector>
#include<array>

const int SSIZE = 9; // SudokuSIZE

typedef struct {
    std::vector<int> possibilities = {1,2,3,4,5,6,7,8,9};
    int state = 0;
    bool peersRemoved = false;

} square_t;

using sudoku_t = std::array<std::array<int, SSIZE> ,SSIZE>;

using state_vector_t = std::array<std::array<square_t, SSIZE>, SSIZE>;

class SudokuPuzzle {
    sudoku_t inputSudoku;
    state_vector_t solutionSudoku;
    std::pair <int, int> lowestPossibilities;
    bool solved = false;
};


#endif