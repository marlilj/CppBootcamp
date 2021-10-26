#include"solver.h"

bool sudokuSolver(sudoku_t &originalSudoku, bool useBruteForce, bool prettyPrint) {

    bool sudokuIsSolved = false;

    // Start timer for complete solver
    auto startProgram = std::chrono::high_resolution_clock::now();
    ( prettyPrint ) ? print(originalSudoku) : printLine(originalSudoku);

    state_vector_t solutionSudoku;

    // Populate solutionSudoku with [1,9] on all squares
    for (int row=0; row<SSIZE; row++) {
        for (int col=0; col<SSIZE; col++) {
            solutionSudoku[row][col] = {1,2,3,4,5,6,7,8,9};
        }
    }

    // Replace possible solutions with correct values from input sudoku
    prepareIntermediateState(solutionSudoku, originalSudoku);

    // Run constraint propagation, if sudoku is solved, print and exit
    if ( constraintPropagation(solutionSudoku, originalSudoku) ) {
        ( prettyPrint ) ? print(solutionSudoku) : printLine(solutionSudoku);
        std::cout << "Solved puzzle after constraint propagation" << std::endl;
        sudokuIsSolved = true;
    // If not entirely solved, start brute forcing on remaining possible solutions
    } else {
        if ( prettyPrint ) {
            std::cout << "Printing puzzle after constraint propagation:" << std::endl;
            print(solutionSudoku);
        }

        if (useBruteForce) {

            // Start timer for bruteforce
            auto startBruteForce = std::chrono::high_resolution_clock::now();
            if ( bruteForce(solutionSudoku, 0, 0) ) {
                ( prettyPrint ) ? print(solutionSudoku) : printLine(solutionSudoku);
                std::cout << "Puzzle solved using brute force on top." << std::endl;
                sudokuIsSolved = true;
            } else {
                std::cout << "Couldn't solve puzzle with brute force either." << std::endl;
            }
            // End timer for bruteforce
            auto endBruteForce = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endBruteForce - startBruteForce);

            std::cout << "Execution time for brute force (ms): " << duration.count() << std::endl;

        }

    }

    // End timer for complete program
    auto endProgram = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endProgram - startProgram);
    std::cout << "Total execution time (ms): " << duration.count() << std::endl;

    return sudokuIsSolved;
}

bool constraintPropagation(state_vector_t &_stateVector, const sudoku_t &_originalSudoku) {
    int value = 0;

    // Loop over the sudoku once for each square, if set remove peers, if not,
    // check if one possible solution exists only here, or remove entries that are impossible
    for (int row = 0 ; row < SSIZE; row++) {
        for (int col = 0;  col < SSIZE; col++ ) {
            value = _originalSudoku[row][col];
            if (value != 0) {
                removeAndUpdatePeers(value, row, col, _stateVector);
            } else {
                checkUniqueValueAmongPeers(row, col, _stateVector);
            }
        }
    }
    return sudokuIsSolved(_stateVector);
}

bool sudokuIsSolved(state_vector_t &_stateVector) {
    bool solved = true;
    for (int row = 0 ; row < 9; row++) {
        for (int col = 0;  col < 9; col++ ) {
            if ( _stateVector[row][col].size() > 1 ) {
                solved = false;
                break;
            }
        }
    }
    return solved;
}

void removeAndUpdatePeers(int _value, unsigned int row, unsigned int col, state_vector_t &_stateVector) {
    removeFromRow(_value, row, col, _stateVector);
    removeFromCol(_value, col, row, _stateVector);
    removeFromBox(_value, row, col, _stateVector);
}

void checkUniqueValueAmongPeers(unsigned int row, unsigned int col, state_vector_t &_stateVector) {
    // Check if we don't already have only one solution
    if ( _stateVector[row][col].size() != 1 ) {
        // loop over all possible values in this square
        for ( int i = 0; i < _stateVector[row][col].size(); i++ ) {
            if ( valueInRow(_stateVector[row][col][i], row, col, _stateVector) ) {
                    _stateVector[row][col].erase(_stateVector[row][col].begin()+i);
                    --i; // since we are removing i we need to go back 1
                    if (_stateVector[row][col].size() == 1) {
                        removeAndUpdatePeers(_stateVector[row][col][0], row, col, _stateVector);
                    }
            } else if ( valueInCol(_stateVector[row][col][i], col, row, _stateVector) ) {
                    _stateVector[row][col].erase(_stateVector[row][col].begin()+i);
                    --i; // since we are removing i we need to go back 1
                    if (_stateVector[row][col].size() == 1) {
                        removeAndUpdatePeers(_stateVector[row][col][0], row, col, _stateVector);
                    }
            } else if ( valueInBox(_stateVector[row][col][i], row, col, _stateVector) ) {
                    _stateVector[row][col].erase(_stateVector[row][col].begin()+i);
                    --i; // since we are removing i we need to go back 1
                    if (_stateVector[row][col].size() == 1) {
                        removeAndUpdatePeers(_stateVector[row][col][0], row, col, _stateVector);
                    }
            } else {
                if ( !optionInRow(_stateVector[row][col][i], row, col, _stateVector)
                    || !optionInCol(_stateVector[row][col][i], col, row, _stateVector)
                    || !optionInBox(_stateVector[row][col][i], row, col, _stateVector) ) {
                    _stateVector[row][col]={_stateVector[row][col][i]};
                    removeAndUpdatePeers(_stateVector[row][col][0], row, col, _stateVector);
                    break;
                }
            }
        }
    // then remove it's peers
    } else {
        removeAndUpdatePeers(_stateVector[row][col][0], row, col, _stateVector);
    }
}

bool valueInRow(int _value, unsigned int row, unsigned int valueCol, state_vector_t &_stateVector) {
    bool return_val = false;
    for (int col = 0;  col < SSIZE; col++ ) {
        if (col != valueCol && _stateVector[row][col].size() == 1 ) {
            if (_value == _stateVector[row][col][0]) {
                return_val = true;
                break;
            }
        }
    }
    return return_val;
}

bool rowIsFinal(unsigned int row, unsigned int valueCol, state_vector_t &_stateVector) {
    bool return_val = true;
    for (int col = 0;  col < SSIZE; col++ ) {
        if (col != valueCol && _stateVector[row][col].size() != 1 ) {
                return_val = false;
                break;
        }
    }
    return return_val;
}

bool optionInRow(int _value, unsigned int row, unsigned int valueCol, state_vector_t &_stateVector) {
    bool return_val = false;
    for (int col = 0;  col < SSIZE; col++ ) {
        if (col != valueCol && _stateVector[row][col].size() > 1) {
            for (int i=0; i < _stateVector[row][col].size(); i++) {
                if (_value == _stateVector[row][col][i]) {
                    return_val = true;
                    break;
                }
            }
        }
    }
    return return_val;
}

void removeFromRow(int _value, unsigned int row, unsigned int valueCol, state_vector_t &_stateVector) {
    for (int col = 0;  col < SSIZE; col++ ) {
        if (col != valueCol && _stateVector[row][col].size() > 1) {
            for (int i=0; i < _stateVector[row][col].size(); i++) {
                if (_value == _stateVector[row][col][i]) {
                    _stateVector[row][col].erase(_stateVector[row][col].begin()+i);
                    --i;
                    if (_stateVector[row][col].size() == 1) {
                        removeAndUpdatePeers(_stateVector[row][col][0], row, col, _stateVector);
                    } else {
                        checkUniqueValueAmongPeers(row, col, _stateVector);
                    }
                }
            }
            checkUniqueValueAmongPeers(row, col, _stateVector);
        }
    }
}

bool valueInCol(int _value, unsigned int col, unsigned int valueRow, state_vector_t &_stateVector) {
    bool return_val = false;
    for (int row = 0;  row < SSIZE; row++ ) {
        if ( row != valueRow  && _stateVector[row][col].size() == 1 ) {
            if (_value == _stateVector[row][col][0]) {
                return_val = true;
                break;
            }
        }
    }
    return return_val;
}

void removeFromCol(int _value, unsigned int col, unsigned int valueRow, state_vector_t &_stateVector) {
    for (int row = 0;  row < SSIZE; row++ ) {
        if ( row != valueRow && _stateVector[row][col].size() > 1) {
            for (int i=0; i < _stateVector[row][col].size(); i++) {
                if (_value == _stateVector[row][col][i]) {
                    _stateVector[row][col].erase(_stateVector[row][col].begin()+i);
                    --i;
                    if (_stateVector[row][col].size() == 1) {
                        removeAndUpdatePeers(_stateVector[row][col][0], row, col, _stateVector);
                    } else {
                        checkUniqueValueAmongPeers(row, col, _stateVector);
                    }
                }
            }
            checkUniqueValueAmongPeers(row, col, _stateVector);
        }
    }
}

bool optionInCol(int _value, unsigned int col, unsigned int valueRow, state_vector_t &_stateVector) {
    bool return_val = false;
    for (int row = 0;  row < SSIZE; row++ ) {
        if ( row != valueRow && _stateVector[row][col].size() > 1) {
            for (int i=0; i < _stateVector[row][col].size(); i++) {
                if (_value == _stateVector[row][col][i]) {
                    return_val = true;
                    break;
                }
            }
        }
    }
    return return_val;
}

void removeFromBox(int _value, unsigned int row, unsigned int col, state_vector_t &_stateVector) {
    int start_row = row - row % 3;
    int start_col = col - col % 3;
    for (int r = start_row; r < start_row+3; r++) {
        for (int c = start_col; c < start_col+3; c++) {
            if (!(r == row && c == col)) {
                for (int i=0; i < _stateVector[r][c].size(); i++) {
                    if (_value == _stateVector[r][c][i]) {
                        _stateVector[r][c].erase(_stateVector[r][c].begin()+i);
                        --i;
                        if (_stateVector[r][c].size() == 1) {
                            removeAndUpdatePeers(_stateVector[r][c][0], r, c, _stateVector);
                        } else {
                            checkUniqueValueAmongPeers(r, c, _stateVector);
                        }
                    }
                }
                if (_stateVector[r][c].size() > 1) {
                    checkUniqueValueAmongPeers(r, c, _stateVector);
                }
            }
        }
    }
}

bool valueInBox(int _value, unsigned int row, unsigned int col, state_vector_t &_stateVector) {
    bool return_val = false;
    int start_row = row - row % 3;
    int start_col = col - col % 3;
    for (int r = start_row; r < start_row+3; r++) {
        for (int c = start_col; c < start_col+3; c++) {
            if (!(r == row && c == col) && _stateVector[r][c].size() == 1) {
                if (_value == _stateVector[r][c][0]) {
                    return_val = true;
                }
            }
        }
    }
    return return_val;
}

bool optionInBox(int _value, unsigned int row, unsigned int col, state_vector_t &_stateVector) {
    bool return_val = false;
    int start_row = row - row % 3;
    int start_col = col - col % 3;
    for (int r = start_row; r < start_row+3; r++) {
        for (int c = start_col; c < start_col+3; c++) {
            if (!(r == row && c == col) && _stateVector[r][c].size() > 1) {
                for (int i=0; i < _stateVector[r][c].size(); i++) {
                    if (_value == _stateVector[r][c][i]) {
                        return_val = true;
                    }
                }
            }
        }
    }
    return return_val;
}

void prepareIntermediateState(state_vector_t &_stateVector, const sudoku_t &_originalSudoku) {
    int value = 0;
    for (int row = 0 ; row < SSIZE; row++) {
        for (int col = 0;  col < SSIZE; col++ ) {
            value = _originalSudoku[row][col];
            if (value != 0) {
                _stateVector[row][col]={value};
            }
        }
    }
}