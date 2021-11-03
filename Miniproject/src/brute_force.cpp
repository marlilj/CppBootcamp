#include"brute_force.h"

int numberOfGuesses = 0;
 
bool bruteForce(state_vector_t &_stateVector, const sudoku_t &_originalSudoku, int row, int col, int startRow, int startCol, int recursiveCounter) {
    ++recursiveCounter;

    // If we have already parsed all squares, return true
    if ( (row == startRow && col == startCol+1) && !(recursiveCounter==2) ) {
        return true;
    }

    // if we have finalized one row, skip to the next
    if ( col == 9 ) {
        row++;
        col = 0;
    }

    if (row == 9) {
        row = 0;
    }

    // If we already have the final value, move on to next square
    if ( _stateVector[row][col].state != 0 ) {
        return bruteForce(_stateVector, _originalSudoku, row, col+1, startRow, startCol, recursiveCounter);
    }

    // Copy current state
    state_vector_t sudokuCopy = _stateVector;
    std::vector<int> options = _stateVector[row][col].possibilities;

    // Run over all options and call downstream values recursively
    for (int o : options ) {

        if (setValue(row, col, o, _stateVector)) {
            if ( bruteForce(_stateVector, _originalSudoku, row, col+1, startRow, startCol, recursiveCounter) ) {
                return true;
            }
        }
        ::numberOfGuesses++;
        _stateVector = sudokuCopy;
    }

    _stateVector = sudokuCopy;
    return false;
}