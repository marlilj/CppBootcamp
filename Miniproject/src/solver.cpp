#include"solver.h"

bool sudokuSolver(sudoku_t &originalSudoku, bool useBruteForce, bool prettyPrint) {

    bool sudokuIsSolved = false;

    // Start timer for complete solver
    auto startProgram = std::chrono::high_resolution_clock::now();
    std::cout << "Input:                  ";
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
        std::cout << "Constraint propagation: ";
        ( prettyPrint ) ? print(solutionSudoku) : printLine(solutionSudoku);
        std::cout << "Solved puzzle after constraint propagation" << std::endl;
        sudokuIsSolved = true;
    // If not entirely solved, start brute forcing on remaining possible solutions
    } else {
        if ( prettyPrint ) {
            std::cout << "Printing puzzle after constraint propagation:";
            print(solutionSudoku);
        } else {
            std::cout << "Constraint propagation: ";
            printLine(solutionSudoku);
        }

        if (useBruteForce) {

            // find best square to start in
            unsigned int rowLeastPossible = 9;
            unsigned int colLeastPossible = 9;
            unsigned int leastHypos = 9;

            for (int row = 0 ; row < SSIZE ; row++ ) {
                for ( int col = 0; col < SSIZE ; col++ ) {
                    if (1 < solutionSudoku[row][col].size() && solutionSudoku[row][col].size() < leastHypos) {
                        leastHypos = solutionSudoku[row][col].size();
                        rowLeastPossible = row;
                        colLeastPossible = col;
                    }

                    if (leastHypos == 2) {
                        break; // can't find less than 2
                    }
                }
            }

            // Start timer for bruteforce
            auto startBruteForce = std::chrono::high_resolution_clock::now();
            if ( bruteForce(solutionSudoku, originalSudoku, rowLeastPossible, colLeastPossible, rowLeastPossible, colLeastPossible, 0) ) {
                std::cout << "Brute force:            ";
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
            if ( _stateVector[row][col].size() > 1 || _stateVector[row][col].size() == 0 ) {
                solved = false;
                break;
            }
        }
    }
    return solved;
}

bool removeAndUpdatePeers(int _value, unsigned int row, unsigned int col, state_vector_t &_stateVector) {
    bool returnVal = false;
    returnVal = returnVal || removeFromRow(_value, row, col, _stateVector);
    returnVal = returnVal || removeFromCol(_value, col, row, _stateVector);
    returnVal = returnVal || removeFromBox(_value, row, col, _stateVector);
    return returnVal;
}

void checkUniqueValueAmongPeers(unsigned int row, unsigned int col, state_vector_t &_stateVector) {
    // Check if we don't already have only one solution
    if ( _stateVector[row][col].size() > 1 ) {
        // loop over all possible values in this square
        for ( int i = 0; i < _stateVector[row][col].size(); i++ ) {
            if (_stateVector[row][col].size() == 1) {
                break; // done
            }
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
                    std::vector<int> options = _stateVector[row][col];
                    _stateVector[row][col]={_stateVector[row][col][i]};
                    if (removeAndUpdatePeers(_stateVector[row][col][0], row, col, _stateVector) ) {
                        break;
                    } else {
                        _stateVector[row][col] = options;
                    }
                }
            }
        }
    // then remove it's peers
    } else if (_stateVector[row][col].size() == 1) {
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

bool removeFromRow(int _value, unsigned int row, unsigned int valueCol, state_vector_t &_stateVector) {
    bool returnVal = false;
    for (int col = 0;  col < SSIZE; col++ ) {
        if (col != valueCol && _stateVector[row][col].size() > 1) {
            const auto removeExp = std::remove_if(_stateVector[row][col].begin(), _stateVector[row][col].end(),
                [_value](const int &i){ return i == _value ; });
            if (removeExp != _stateVector[row][col].end()) {
                _stateVector[row][col].erase( removeExp, _stateVector[row][col].end());
                if (_stateVector[row][col].size() < 1) {
                    returnVal = false;
                    break;
                } else {
                    returnVal = true;
                }
            }
            checkUniqueValueAmongPeers(row, col, _stateVector);
            if (_stateVector[row][col].size() == 1 ) {
                removeAndUpdatePeers(_stateVector[row][col][0], row, col, _stateVector);
            }
        }
    }
    return returnVal;
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

bool removeFromCol(int _value, unsigned int col, unsigned int valueRow, state_vector_t &_stateVector) {
    bool returnVal = false;
    for (int row = 0;  row < SSIZE; row++ ) {
        if ( row != valueRow && _stateVector[row][col].size() > 1) {
            const auto removeExp = std::remove_if(_stateVector[row][col].begin(), _stateVector[row][col].end(),
                [_value](const int &i){ return i == _value ; });
            if (removeExp != _stateVector[row][col].end()) {
                _stateVector[row][col].erase(removeExp, _stateVector[row][col].end());
                if (_stateVector[row][col].size() < 1) {
                    returnVal = false;
                    break;
                } else {
                    returnVal = true;
                }
            }
            checkUniqueValueAmongPeers(row, col, _stateVector);
            if (_stateVector[row][col].size() == 1 ) {
                removeAndUpdatePeers(_stateVector[row][col][0], row, col, _stateVector);
            }
        }
    }
    return returnVal;
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

bool removeFromBox(int _value, unsigned int row, unsigned int col, state_vector_t &_stateVector) {
    bool returnVal = false;
    int start_row = row - row % 3;
    int start_col = col - col % 3;
    for (int r = start_row; r < start_row+3; r++) {
        for (int c = start_col; c < start_col+3; c++) {
            if (!(r == row && c == col)) {
                const auto removeExp = std::remove_if(_stateVector[r][c].begin(), _stateVector[r][c].end(),
                    [_value](const int &i){ return i == _value ; });

                if (removeExp != _stateVector[r][c].end()) {
                    _stateVector[r][c].erase(removeExp, _stateVector[r][c].end());
                    if (_stateVector[r][c].size() < 1) {
                        returnVal = false;
                        break;
                    } else {
                        returnVal = true;
                    }
                }
                if (_stateVector[r][c].size() > 1 ) {
                    // removeAndUpdatePeers(_stateVector[r][c][0], r, c, _stateVector);
                    checkUniqueValueAmongPeers(r, c, _stateVector);
                }
            }
        }
    }
    return returnVal;
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