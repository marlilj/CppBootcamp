#include"brute_force.h"
 
bool brute_force(state_vector &_state_vector, int row, int col) {

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
    if ( _state_vector[row][col].size() == 1 ) {
        return brute_force(_state_vector, row, col+1);
    }

    // Store all options
    std::vector<int> options = _state_vector[row][col];

    // Run over all options and call downstream values recursively
    for (int o : options ) {

        // If the values isn't set in the row, col or box assign it and proceed
        if ( (!value_in_row(o, row, col, _state_vector)
                && !value_in_col(o, col, row, _state_vector)
                && !value_in_box(o, row, col, _state_vector)) ) {
            _state_vector[row][col] = {o};
            if ( brute_force(_state_vector, row, col+1) ) {
                return true;
            }
        }
    }

    // If we come here none of the assigned options worked downstream
    _state_vector[row][col] = options;
    return false;
}