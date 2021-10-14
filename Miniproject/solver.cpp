#include"solver.h"

void parse_input_sudoku(state_vector &_state_vector, const sudoku &_original_sudoku) {
    int value = 0;
    for (int row = 0 ; row < 9; row++) {
        for (int col = 0;  col < 9; col++ ) {
            value = _original_sudoku[row][col];
            if (value != 0) {
                remove_and_update_peers(value, row, col, _state_vector);
            } else {
                check_unique_value_among_peers(row, col, _state_vector);
            }
        }
    }
}

void remove_and_update_peers(int _value, unsigned int row, unsigned int col, state_vector &_state_vector) {
    remove_from_row(_value, row, col, _state_vector);
    // check_for_single_options_row(row, col, _state_vector);
    remove_from_col(_value, col, row, _state_vector);
    remove_from_box(_value, row, col, _state_vector);
}

void check_unique_value_among_peers(unsigned int row, unsigned int col, state_vector &_state_vector) {
    // Check if we don't already have only one solution
    if ( _state_vector[row][col].size() != 1 ) {
        // loop over all possible values in this square
        for ( int i = 0; i < _state_vector[row][col].size(); i++ ) {
            std::cout << "Checking for : " << _state_vector[row][col][i] << " in (" << row << ", " << col << ") square" << std::endl;
            // // If current value does only exist in this square, assign it and remove peers
            if ( value_in_row(_state_vector[row][col][i], row, col, _state_vector) ) {
                // if ( !option_in_row(_state_vector[row][col][i], row, col, _state_vector) ) {
                //     _state_vector[row][col]={_state_vector[row][col][i]};
                //     remove_and_update_peers(_state_vector[row][col][i], row, col, _state_vector);
                // } else {
                    _state_vector[row][col].erase(_state_vector[row][col].begin()+i);
                    --i; // since we are removing i we need to go back 1
                    if (_state_vector[row][col].size() == 1) {
                        remove_and_update_peers(_state_vector[row][col][0], row, col, _state_vector);
                    }
                // }
                std::cout << "\tFound in row" << std::endl;
            } else if ( value_in_col(_state_vector[row][col][i], col, row, _state_vector) ) {
                // if ( !option_in_col(_state_vector[row][col][i], col, row, _state_vector) ) {
                //     _state_vector[row][col]={_state_vector[row][col][i]};
                //     remove_and_update_peers(_state_vector[row][col][i], row, col, _state_vector);
                // } else {
                    _state_vector[row][col].erase(_state_vector[row][col].begin()+i);
                    --i; // since we are removing i we need to go back 1
                    if (_state_vector[row][col].size() == 1) {
                        remove_and_update_peers(_state_vector[row][col][0], row, col, _state_vector);
                    }
                // }
                std::cout << "\tFound in col" << std::endl;
            } else if ( value_in_box(_state_vector[row][col][i], row, col, _state_vector) ) {
                // if ( !option_in_box(_state_vector[row][col][i], row, col, _state_vector) ) {
                //     _state_vector[row][col]={_state_vector[row][col][i]};
                //     remove_and_update_peers(_state_vector[row][col][i], row, col, _state_vector);
                // } else {
                    _state_vector[row][col].erase(_state_vector[row][col].begin()+i);
                    --i; // since we are removing i we need to go back 1
                    if (_state_vector[row][col].size() == 1) {
                        remove_and_update_peers(_state_vector[row][col][0], row, col, _state_vector);
                    }
                // }
                std::cout << "\tFound in box" << std::endl;
            } else {
                std::cout << "\tNot found" << std::endl;
                std::cout << option_in_row(_state_vector[row][col][i], row, col, _state_vector) << ", " <<
                option_in_col(_state_vector[row][col][i], col, row, _state_vector) << ", "  <<
                option_in_box(_state_vector[row][col][i], row, col, _state_vector) << std::endl;
                if ( !option_in_row(_state_vector[row][col][i], row, col, _state_vector)
                    || !option_in_col(_state_vector[row][col][i], col, row, _state_vector)
                    || !option_in_box(_state_vector[row][col][i], row, col, _state_vector) ) {
                    _state_vector[row][col]={_state_vector[row][col][i]};
                    remove_and_update_peers(_state_vector[row][col][i], row, col, _state_vector);
                // _state_vector[row][col]={_state_vector[row][col][i]};
                //     remove_and_update_peers(_state_vector[row][col][i], row, col, _state_vector);
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
    for (int col = 0;  col < _state_vector[row].size(); col++ ) {
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
    for (int col = 0;  col < _state_vector[row].size(); col++ ) {
        if (col != value_col && _state_vector[row][col].size() != 1 ) {
                return_val = false;
                break;
        }
    }
    return return_val;
}

bool option_in_row(int _value, unsigned int row, unsigned int value_col, state_vector &_state_vector) {
    bool return_val = false;
    for (int col = 0;  col < _state_vector[row].size(); col++ ) {
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
    for (int col = 0;  col < _state_vector[row].size(); col++ ) {
        if (col != value_col) {
            for (int i=0; i < _state_vector[row][col].size(); i++) {
                if (_value == _state_vector[row][col][i]) {
                    _state_vector[row][col].erase(_state_vector[row][col].begin()+i);
                    if (_state_vector[row][col].size() == 1) {
                        remove_and_update_peers(_state_vector[row][col][0], row, col, _state_vector);
                    }
                }
            }
        }
    }
}

bool value_in_col(int _value, unsigned int col, unsigned int value_row, state_vector &_state_vector) {
    bool return_val = false;
    for (int row = 0;  row < _state_vector[col].size(); row++ ) {
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
    for (int row = 0;  row < _state_vector[col].size(); row++ ) {
        if ( row != value_row ) {
            for (int i=0; i < _state_vector[row][col].size(); i++) {
                if (_value == _state_vector[row][col][i]) {
                    _state_vector[row][col].erase(_state_vector[row][col].begin()+i);
                    if (_state_vector[row][col].size() == 1) {
                        remove_and_update_peers(_state_vector[row][col][0], row, col, _state_vector);
                    }
                }
            }
        }
    }
}

bool option_in_col(int _value, unsigned int col, unsigned int value_row, state_vector &_state_vector) {
    bool return_val = false;
    for (int row = 0;  row < _state_vector[col].size(); row++ ) {
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
                        // std::cout << "Erasing " << _value << " from ";
                        // std::cout << "(" << r << ", " << c << "), " << std::endl;
                        if (_state_vector[row][col].size() == 1) {
                            remove_and_update_peers(_state_vector[row][col][0], row, col, _state_vector);
                        }
                    }
                }
            }
        }
        // std::cout << std::endl;
    }
    // std::cout << "------------------" << std::endl;
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

void check_for_single_options_row(unsigned int row, unsigned int col, state_vector &_state_vector) {
    std::vector<int> values_to_check = _state_vector[row][col];
    std::vector<int>::iterator it;
    bool match_is_found = false;

    for (int v: values_to_check) {
        for ( int c = 0;  c < _state_vector[row].size(); c++ ) {
            if ( c != col ) {
                it = std::find(_state_vector[row][c].begin(), _state_vector[row][c].end(), v );
                if( it != _state_vector[row][c].end()) {
                    match_is_found = true;
                }
            }
        }
        if (!match_is_found) {
            _state_vector[row][col] = {v};
            break;
        }
    }
}

void prepare_intermediate_state(state_vector &_state_vector, const sudoku &_original_sudoku) {
    int value = 0;
    for (int row = 0 ; row < 9; row++) {
        for (int col = 0;  col < 9; col++ ) {
            value = _original_sudoku[row][col];
            if (value != 0) {
                _state_vector[row][col]={value};
            }
        }
    }
}