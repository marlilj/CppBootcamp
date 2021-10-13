#include"solver.h"

void parse_input_sudoku(state_vector &_state_vector, const sudoku &_original_sudoku) {
    int value = 0;
    for (int row = 0 ; row < 9; row++) {
        for (int col = 0;  col < 9; col++ ) {
            value = _original_sudoku[row][col];
            if (value != 0) {
                remove_and_update_peers(value, row, col, _state_vector);
            }
        }
    }
}

void remove_and_update_peers(int _value, unsigned int row, unsigned int col, state_vector &_state_vector) {
    remove_from_row(_value, row, col, _state_vector);
    check_for_single_options_row(row, col, _state_vector);
    remove_from_col(_value, col, row, _state_vector);
    remove_from_box(_value, row, col, _state_vector);
}

void remove_from_row(int _value, unsigned int row, unsigned int value_col, state_vector &_state_vector) {
    for (int col = 0;  col < _state_vector[row].size(); col++ ) {
        if (col != value_col) {
            for (int i=0; i < _state_vector[row][col].size(); i++) {
                if (_value == _state_vector[row][col][i]) {
                    _state_vector[row][col].erase(_state_vector[row][col].begin()+i);
                    // print(_state_vector);
                }
            }
        }
    }
}

void remove_from_col(int _value, unsigned int col, unsigned int value_row, state_vector &_state_vector) {
    for (int row = 0;  row < _state_vector[col].size(); row++ ) {
        if ( row != value_row ) {
            for (int i=0; i < _state_vector[row][col].size(); i++) {
                if (_value == _state_vector[row][col][i]) {
                    _state_vector[row][col].erase(_state_vector[row][col].begin()+i);
                }
            }
        }
    }
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
                        std::cout << "Erasing " << _value << " from ";
                        std::cout << "(" << r << ", " << c << "), " << std::endl;
                    }
                }
            }
        }
        std::cout << std::endl;
    }
    std::cout << "------------------" << std::endl;
}

void check_for_single_options_row(unsigned int row, unsigned int col, state_vector &_state_vector) {
    //// START WITH THIS ..
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