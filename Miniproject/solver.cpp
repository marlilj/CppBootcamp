#include"solver.h"

bool constraint_propagation(state_vector &_state_vector, const sudoku &_original_sudoku) {
    int value = 0;

    // Loop over the sudoku once for each square, if set remove peers, if not,
    // check if one possible solution exists only here, or remove entries that are impossible
    for (int row = 0 ; row < SSIZE; row++) {
        for (int col = 0;  col < SSIZE; col++ ) {
            value = _original_sudoku[row][col];
            if (value != 0) {
                remove_and_update_peers(value, row, col, _state_vector);
            } else {
                check_unique_value_among_peers(row, col, _state_vector);
            }
        }
    }
    return sudoku_is_solved(_state_vector);
}

bool sudoku_is_solved(state_vector &_state_vector) {
    bool solved = true;
    for (int row = 0 ; row < 9; row++) {
        for (int col = 0;  col < 9; col++ ) {
            if ( _state_vector[row][col].size() > 1 ) {
                solved = false;
                break;
            }
        }
    }
    return solved;
}

void remove_and_update_peers(int _value, unsigned int row, unsigned int col, state_vector &_state_vector) {
    remove_from_row(_value, row, col, _state_vector);
    remove_from_col(_value, col, row, _state_vector);
    remove_from_box(_value, row, col, _state_vector);
}

void check_unique_value_among_peers(unsigned int row, unsigned int col, state_vector &_state_vector) {
    // Check if we don't already have only one solution
    if ( _state_vector[row][col].size() != 1 ) {
        // loop over all possible values in this square
        for ( int i = 0; i < _state_vector[row][col].size(); i++ ) {
            if ( value_in_row(_state_vector[row][col][i], row, col, _state_vector) ) {
                    _state_vector[row][col].erase(_state_vector[row][col].begin()+i);
                    --i; // since we are removing i we need to go back 1
                    if (_state_vector[row][col].size() == 1) {
                        remove_and_update_peers(_state_vector[row][col][0], row, col, _state_vector);
                    }
            } else if ( value_in_col(_state_vector[row][col][i], col, row, _state_vector) ) {
                    _state_vector[row][col].erase(_state_vector[row][col].begin()+i);
                    --i; // since we are removing i we need to go back 1
                    if (_state_vector[row][col].size() == 1) {
                        remove_and_update_peers(_state_vector[row][col][0], row, col, _state_vector);
                    }
            } else if ( value_in_box(_state_vector[row][col][i], row, col, _state_vector) ) {
                    _state_vector[row][col].erase(_state_vector[row][col].begin()+i);
                    --i; // since we are removing i we need to go back 1
                    if (_state_vector[row][col].size() == 1) {
                        remove_and_update_peers(_state_vector[row][col][0], row, col, _state_vector);
                    }
            } else {
                if ( !option_in_row(_state_vector[row][col][i], row, col, _state_vector)
                    || !option_in_col(_state_vector[row][col][i], col, row, _state_vector)
                    || !option_in_box(_state_vector[row][col][i], row, col, _state_vector) ) {
                    _state_vector[row][col]={_state_vector[row][col][i]};
                    remove_and_update_peers(_state_vector[row][col][0], row, col, _state_vector);
                    break;
                }
            }
        }
    // then remove it's peers
    } else {
        remove_and_update_peers(_state_vector[row][col][0], row, col, _state_vector);
    }
}

bool value_in_row(int _value, unsigned int row, unsigned int value_col, state_vector &_state_vector) {
    bool return_val = false;
    for (int col = 0;  col < SSIZE; col++ ) {
        if (col != value_col && _state_vector[row][col].size() == 1 ) {
            if (_value == _state_vector[row][col][0]) {
                return_val = true;
                break;
            }
        }
    }
    return return_val;
}

bool row_is_final(unsigned int row, unsigned int value_col, state_vector &_state_vector) {
    bool return_val = true;
    for (int col = 0;  col < SSIZE; col++ ) {
        if (col != value_col && _state_vector[row][col].size() != 1 ) {
                return_val = false;
                break;
        }
    }
    return return_val;
}

bool option_in_row(int _value, unsigned int row, unsigned int value_col, state_vector &_state_vector) {
    bool return_val = false;
    for (int col = 0;  col < SSIZE; col++ ) {
        if (col != value_col && _state_vector[row][col].size() > 1) {
            for (int i=0; i < _state_vector[row][col].size(); i++) {
                if (_value == _state_vector[row][col][i]) {
                    return_val = true;
                    break;
                }
            }
        }
    }
    return return_val;
}

void remove_from_row(int _value, unsigned int row, unsigned int value_col, state_vector &_state_vector) {
    for (int col = 0;  col < SSIZE; col++ ) {
        if (col != value_col) {
            for (int i=0; i < _state_vector[row][col].size(); i++) {
                if (_value == _state_vector[row][col][i]) {
                    _state_vector[row][col].erase(_state_vector[row][col].begin()+i);
                    --i;
                    if (_state_vector[row][col].size() == 1) {
                        remove_and_update_peers(_state_vector[row][col][0], row, col, _state_vector);
                    } else {
                        check_unique_value_among_peers(row, col, _state_vector);
                    }
                }
            }
        }
    }
}

bool value_in_col(int _value, unsigned int col, unsigned int value_row, state_vector &_state_vector) {
    bool return_val = false;
    for (int row = 0;  row < SSIZE; row++ ) {
        if ( row != value_row  && _state_vector[row][col].size() == 1 ) {
            if (_value == _state_vector[row][col][0]) {
                return_val = true;
                break;
            }
        }
    }
    return return_val;
}

void remove_from_col(int _value, unsigned int col, unsigned int value_row, state_vector &_state_vector) {
    for (int row = 0;  row < SSIZE; row++ ) {
        if ( row != value_row ) {
            for (int i=0; i < _state_vector[row][col].size(); i++) {
                if (_value == _state_vector[row][col][i]) {
                    _state_vector[row][col].erase(_state_vector[row][col].begin()+i);
                    --i;
                    if (_state_vector[row][col].size() == 1) {
                        remove_and_update_peers(_state_vector[row][col][0], row, col, _state_vector);
                    } else {
                        check_unique_value_among_peers(row, col, _state_vector);
                    }
                }
            }
        }
    }
}

bool option_in_col(int _value, unsigned int col, unsigned int value_row, state_vector &_state_vector) {
    bool return_val = false;
    for (int row = 0;  row < SSIZE; row++ ) {
        if ( row != value_row && _state_vector[row][col].size() > 1) {
            for (int i=0; i < _state_vector[row][col].size(); i++) {
                if (_value == _state_vector[row][col][i]) {
                    return_val = true;
                    break;
                }
            }
        }
    }
    return return_val;
}

void remove_from_box(int _value, unsigned int row, unsigned int col, state_vector &_state_vector) {
    int start_row = row - row % 3;
    int start_col = col - col % 3;
    for (int r = start_row; r < start_row+3; r++) {
        for (int c = start_col; c < start_col+3; c++) {
            if (!(r == row && c == col)) {
                for (int i=0; i < _state_vector[r][c].size(); i++) {
                    if (_value == _state_vector[r][c][i]) {
                        _state_vector[r][c].erase(_state_vector[r][c].begin()+i);
                        --i;
                        if (_state_vector[row][col].size() == 1) {
                            remove_and_update_peers(_state_vector[row][col][0], row, col, _state_vector);
                        } else {
                            check_unique_value_among_peers(row, col, _state_vector);
                        }
                    }
                }
            }
        }
    }
}

bool value_in_box(int _value, unsigned int row, unsigned int col, state_vector &_state_vector) {
    bool return_val = false;
    int start_row = row - row % 3;
    int start_col = col - col % 3;
    for (int r = start_row; r < start_row+3; r++) {
        for (int c = start_col; c < start_col+3; c++) {
            if (!(r == row && c == col) && _state_vector[r][c].size() == 1) {
                if (_value == _state_vector[r][c][0]) {
                    return_val = true;
                }
            }
        }
    }
    return return_val;
}

bool option_in_box(int _value, unsigned int row, unsigned int col, state_vector &_state_vector) {
    bool return_val = false;
    int start_row = row - row % 3;
    int start_col = col - col % 3;
    for (int r = start_row; r < start_row+3; r++) {
        for (int c = start_col; c < start_col+3; c++) {
            if (!(r == row && c == col) && _state_vector[r][c].size() > 1) {
                for (int i=0; i < _state_vector[r][c].size(); i++) {
                    if (_value == _state_vector[r][c][i]) {
                        return_val = true;
                    }
                }
            }
        }
    }
    return return_val;
}

void prepare_intermediate_state(state_vector &_state_vector, const sudoku &_original_sudoku) {
    int value = 0;
    for (int row = 0 ; row < SSIZE; row++) {
        for (int col = 0;  col < SSIZE; col++ ) {
            value = _original_sudoku[row][col];
            if (value != 0) {
                _state_vector[row][col]={value};
            }
        }
    }
}