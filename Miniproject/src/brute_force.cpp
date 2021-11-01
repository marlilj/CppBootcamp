#include"brute_force.h"

int numberOfGuesses = 0;
 
bool bruteForce(state_vector_t &_stateVector, const sudoku_t &_originalSudoku, int row, int col, int startRow, int startCol, int recursiveCounter) {
    ++recursiveCounter;
    // print(_stateVector);

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
    if ( _stateVector[row][col].size() == 1 ) {
        return bruteForce(_stateVector, _originalSudoku, row, col+1, startRow, startCol, recursiveCounter);
    }

    // Copy current state
    state_vector_t sudoku_copy;
    for (int row = 0 ; row < SSIZE ; row++ ) {
        for ( int col = 0; col < SSIZE ; col++ ) {
            sudoku_copy[row][col] = _stateVector[row][col];
        }
    }
    std::vector<int> options = _stateVector[row][col];

    // Run over all options and call downstream values recursively
    for (int o : options ) {

        // If the values isn't set in the row, col or box assign it and proceed
        if ( (!valueInRow(o, row, col, _stateVector)
                && !valueInCol(o, col, row, _stateVector)
                && !valueInBox(o, row, col, _stateVector)) ) {
            _stateVector[row][col] = {o};
            ::numberOfGuesses++;
            removeAndUpdatePeers(o, row, col, _stateVector);
            if ( bruteForce(_stateVector, _originalSudoku, row, col+1, startRow, startCol, recursiveCounter) ) {
                return true;
            }
            // set all values back to how they were
            for (int row = 0 ; row < SSIZE ; row++ ) {
                for ( int col = 0; col < SSIZE ; col++ ) {
                    _stateVector[row][col] = sudoku_copy[row][col];
                }
            }
        }
    }

    // If we come here none of the assigned options worked downstream
    for (int row = 0 ; row < SSIZE ; row++ ) {
        for ( int col = 0; col < SSIZE ; col++ ) {
            _stateVector[row][col] = sudoku_copy[row][col];
        }
    }
    return false;
}