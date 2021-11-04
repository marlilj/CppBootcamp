#include"brute_force.h"

int numberOfGuesses = 0;
 
bool bruteForceSearch(state_vector_t &_stateVector) {
    unsigned int row;
    unsigned int col;

    if (!findLowestPossibleSolutions(row, col, _stateVector)) {
        return true;
    }

    // Copy current state
    state_vector_t sudokuCopy = _stateVector;
    std::vector<int> options = _stateVector[row][col].possibilities;

    // Run over all options and call downstream values recursively
    for (int o : options ) {
        ::numberOfGuesses++;
        if (setValue(row, col, o, _stateVector)) {
            constraintPropagation(_stateVector);
            if ( bruteForceSearch(_stateVector) ) {
                return true;
            }
        }
        _stateVector = sudokuCopy;
    }

    // _stateVector = sudokuCopy;
    return false;
}

bool findLowestPossibleSolutions(unsigned int &row, unsigned int &col, const state_vector_t &_stateVector) {
    /* This function sets the value of row and col of a square with the least number of possible
     * values. If two possible values is found, the search stops.
     * The function returns true if a square with possible solutions is found,
     * it returns false when all squares has been set.
     */
    // find best square to start in
    unsigned int leastHypos = 9;
    bool returnVal = false;

    // make sure that they start with correct values
    row = 9;
    col = 9;

    for (int r = 0 ; r < SSIZE ; r++ ) {
        for ( int c = 0; c < SSIZE ; c++ ) {
            if (_stateVector[r][c].state == 0 && _stateVector[r][c].possibilities.size() < leastHypos) {
                leastHypos = _stateVector[r][c].possibilities.size();
                row = r;
                col = c;
            }

            if (leastHypos == 2) {
                break; // can't find less than 2
            }
        }
    }

    if (row != 9 && col != 9) {
        // A value with least possibles has been found
        returnVal = true;
    }

    return returnVal;
}