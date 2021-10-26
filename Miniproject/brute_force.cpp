#include"brute_force.h"

int numberOfGuesses = 0;
 
bool bruteForce(state_vector_t &_stateVector, int row, int col) {

    // If we have already parsed all squares, return true
    if ( row == 8 && col == 9 ) {
        return true;
    }

    // if we have finalized one row, skip to the next
    if ( col == 9 ) {
        row++;
        col = 0;
    }

    // If we already have the final value, move on to next square
    if ( _stateVector[row][col].size() == 1 ) {
        return bruteForce(_stateVector, row, col+1);
    }

    // Store all options
    std::vector<int> options = _stateVector[row][col];

    // Run over all options and call downstream values recursively
    for (int o : options ) {

        // If the values isn't set in the row, col or box assign it and proceed
        if ( (!valueInRow(o, row, col, _stateVector)
                && !valueInCol(o, col, row, _stateVector)
                && !valueInBox(o, row, col, _stateVector)) ) {
            _stateVector[row][col] = {o};
            ::numberOfGuesses++;
            if ( bruteForce(_stateVector, row, col+1) ) {
                return true;
            }
        }
    }

    // If we come here none of the assigned options worked downstream
    _stateVector[row][col] = options;
    return false;
}