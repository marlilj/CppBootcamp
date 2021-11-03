#include"solver.h"

bool sudokuSolver(sudoku_t &originalSudoku, bool useBruteForce, bool prettyPrint) {

    bool sudokuIsSolved = false;

    // Start timer for complete solver
    auto startProgram = std::chrono::high_resolution_clock::now();
    std::cout << "Input:                  ";
    ( prettyPrint ) ? print(originalSudoku) : printLine(originalSudoku);

    state_vector_t solutionSudoku;

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
                    if (solutionSudoku[row][col].state == 0 && solutionSudoku[row][col].possibilities.size() < leastHypos) {
                        leastHypos = solutionSudoku[row][col].possibilities.size();
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
                std::cout << "Couldn't solve puzzle with brute force starting from (" 
                          << rowLeastPossible << ", " << colLeastPossible << ")\n"
                          << "Testing to start from (0, 0)" << std::endl;
                if ( bruteForce(solutionSudoku, originalSudoku, 0, 0, 0, 0, 0) ) {
                    std::cout << "Brute force:            ";
                    ( prettyPrint ) ? print(solutionSudoku) : printLine(solutionSudoku);
                    std::cout << "Puzzle solved using brute force on top." << std::endl;
                    sudokuIsSolved = true;
                } else {
                    std::cout << "Couldn't solve puzzle" << std::endl;
                }
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

bool setValue(unsigned int row, unsigned int col, unsigned int value, state_vector_t &_stateVector) {
    bool returnValue = false;
    if ( (!valueInRow(value, row, col, _stateVector)
            && !valueInCol(value, row, col, _stateVector)
                && !valueInBox(value, row, col, _stateVector)) ) {
        _stateVector[row][col].state = value;
        _stateVector[row][col].possibilities.clear();
        returnValue = removeAndUpdatePeers(row, col, _stateVector);
    }
    return returnValue;
}

bool constraintPropagation(state_vector_t &_stateVector, const sudoku_t &_originalSudoku) {
    int value = 0;

    // Loop over the sudoku once for each square, if set remove peers, if not,
    // check if one possible solution exists only here, or remove entries that are impossible
    for (int row = 0 ; row < SSIZE; row++) {
        for (int col = 0;  col < SSIZE; col++ ) {
            value = _originalSudoku[row][col];
            if (_stateVector[row][col].state != 0) {
                removeAndUpdatePeers(row, col, _stateVector);
            } else {
                findAndSetUniqueValueAmongPeers(row, col, _stateVector);
            }
        }
    }
    return sudokuIsSolved(_stateVector);
}

bool sudokuIsSolved(state_vector_t &_stateVector) {
    bool solved = true;
    for (int row = 0 ; row < 9; row++) {
        for (int col = 0;  col < 9; col++ ) {
            if ( _stateVector[row][col].state == 0) {
                solved = false;
                break;
            }
        }
    }
    return solved;
}

bool removeAndUpdatePeers(unsigned int row, unsigned int col, state_vector_t &_stateVector) {
    bool returnVal = true;
    if (_stateVector[row][col].state != 0 && !_stateVector[row][col].peersRemoved) {
        bool rowReturn = removeFromRow(row, col, _stateVector);
        bool colReturn = removeFromCol(row, col, _stateVector);
        bool boxReturn = removeFromBox(row, col, _stateVector);
        returnVal = (rowReturn && colReturn && boxReturn);
        _stateVector[row][col].peersRemoved = true;
        if (rowReturn && colReturn && boxReturn) {
            returnVal = findAndSetUniqueValueAmongPeers(row, col, _stateVector);
        }
    }
    return returnVal;
}

bool findAndSetUniqueValueAmongPeers(unsigned int row, unsigned int col, state_vector_t &_stateVector) {
    /* This function takes a position row, col in _stateVector as input, and checks
     * all it's units ( row, column and box ) to find if there is any unique value.
     * If a unique value is found in any of the units, this value is set and removed
     * from it's peers.
     */
    bool returnVal = true;

    // Instantiate multimaps for holding possible values in all three units.
    std::multimap<int, int> rowPossibles;
    std::multimap<int, int> colPossibles;
    std::multimap<int, std::pair<int, int >> boxPossibles;

    // Call a function to populate the multimaps
    if (findPossibleValuesInRowAndCol(row, col, _stateVector, rowPossibles, colPossibles)
            && findPossibleValuesInBox(row, col, _stateVector, boxPossibles)) {

        // Loop over all values in rowPossibles to find uniques. If found. Set it and remove from peers.
        for( auto it = rowPossibles.begin(); it != rowPossibles.end() ; ++it ){

            // If the value in possibles is not already set, check if unique
            std::pair <std::multimap<int,int>::iterator, std::multimap<int,int>::iterator> comparison;
            comparison = rowPossibles.equal_range(it->first);
            // If the next element is only one place in memory away, it is unique
            auto comparisonFirst = comparison.first;
            if (++comparisonFirst == comparison.second) {
                unsigned int uniqueCol = comparison.first->second;
                if ( !setValue(row, uniqueCol, comparison.first->first,_stateVector)) {
                    returnVal = false;
                }
            }
        }

        // Loop over all values in colPossibles to find uniques. If found. Set it and remove from peers.
        for( auto it = colPossibles.begin(); it != colPossibles.end() ; ++it ){

            // If the value in possibles is not already set, check if unique
            std::pair <std::multimap<int,int>::iterator, std::multimap<int,int>::iterator> comparison;
            comparison = colPossibles.equal_range(it->first);
            // If the next element is only one place in memory away, it is unique
            auto comparisonFirst = comparison.first;
            if (++comparisonFirst == comparison.second) {
                unsigned int uniqueRow = comparison.first->second;
                if ( !setValue(uniqueRow, col, comparison.first->first,_stateVector) ) {
                    returnVal = false;
                }
            }
        }


        // Loop over all values in boxPossibles
        for( auto it = boxPossibles.begin(); it != boxPossibles.end() ; ++it ){
            // If the value in possibles is not already set, check if unique
            auto comparison = boxPossibles.equal_range(it->first);
            // If the next element is only one place in memory away, it is unique
            auto comparisonFirst = comparison.first;
            if (++comparisonFirst == comparison.second) {
                auto uniqueBox = comparison.first->second;
                if ( !setValue(std::get<0>(uniqueBox), std::get<1>(uniqueBox), comparison.first->first,_stateVector) ) {
                    returnVal = false;
                }
            }
        }
    }
    return returnVal = returnVal;
}

bool findPossibleValuesInRowAndCol(unsigned int row, unsigned int col, state_vector_t &_stateVector,
    std::multimap<int, int> &rowPossibles, std::multimap<int, int> &colPossibles) {
    bool returnVal = true;
    // Append all possible values to a multimap
    for (int i = 0 ; i < SSIZE ; i++) {
        // If a value is already set, make sure that the peers possibles are up 
        // to date and erase them from rowValues/colValues if they already have
        // been added
        if (i != col && _stateVector[row][i].state != 0) {
            if (!removeAndUpdatePeers(row, i, _stateVector)) {
                returnVal = false;
            }
            rowPossibles.erase(_stateVector[row][i].state);
        }
        if (i != row && _stateVector[i][col].state != 0) {
            if (!removeAndUpdatePeers(i, col, _stateVector)) {
                returnVal = false;
            }
            colPossibles.erase(_stateVector[i][col].state);
        }

        // Add all possible values to the correct multimap
        for (int possibleValue: _stateVector[row][i].possibilities) {
            rowPossibles.insert({possibleValue, i});
        }
        for (int possibleValue: _stateVector[i][col].possibilities) {
            colPossibles.insert({possibleValue, i});
        }
    }
    return returnVal;
}

bool findPossibleValuesInBox(unsigned int row, unsigned int col, state_vector_t &_stateVector,
                             std::multimap<int, std::pair<int, int>> &boxPossibles) {
    bool returnVal = true;
    int start_row = row - row % 3;
    int start_col = col - col % 3;
    int _value = _stateVector[row][col].state;
    for (int r = start_row; r < start_row+3; r++) {
        for (int c = start_col; c < start_col+3; c++) {
            // If a value is already set, make sure that the peers possibles are up 
            // to date and erase them from boxPossibles if they already have
            // been added
            if (_stateVector[r][c].state != 0) {
                if (!removeAndUpdatePeers(r, c, _stateVector)) {
                    returnVal = false;
                }
                boxPossibles.erase(_stateVector[r][c].state);
            }

            // Add all possible values to the correct multimap
            for (int possibleValue: _stateVector[r][c].possibilities) {
                boxPossibles.insert({possibleValue, {r,c}});
            }
        }
    }
    return returnVal;
}

bool valueInRow(int _value, unsigned int row, unsigned int valueCol, state_vector_t &_stateVector) {
    bool return_val = false;
    for (int col = 0;  col < SSIZE; col++ ) {
        if (col != valueCol && _stateVector[row][col].state != 0 ) {
            if (_value == _stateVector[row][col].state) {
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
        if (col != valueCol && _stateVector[row][col].state == 0 ) {
                return_val = false;
                break;
        }
    }
    return return_val;
}

bool removeFromRow(unsigned int row, unsigned int valueCol, state_vector_t &_stateVector) {
    bool returnVal = true;
    int _value = _stateVector[row][valueCol].state;
    for (int col = 0;  col < SSIZE; col++ ) {
        if (col != valueCol && _stateVector[row][col].state == 0) {
            returnVal = removePossibleValue(row, col, _value, _stateVector);
        }
    }
    return returnVal;
}

bool removePossibleValue(unsigned int row, unsigned int col, unsigned int _value, state_vector_t &_stateVector) {
    bool returnVal = true;
    const auto removeExp = std::remove_if(_stateVector[row][col].possibilities.begin(),
        _stateVector[row][col].possibilities.end(),
        [_value](const int &i){ return i == _value ; });
    if (removeExp != _stateVector[row][col].possibilities.end()) {
        _stateVector[row][col].possibilities.erase( removeExp, _stateVector[row][col].possibilities.end());
        if (_stateVector[row][col].possibilities.size() == 1) {
            if (!setValue(row, col, _stateVector[row][col].possibilities[0],_stateVector)) {
                // _stateVector[row][col].possibilities.push_back(_value);
                returnVal = false;
            }
        }
    }
    return returnVal;
}

bool valueInCol(int _value, unsigned int valueRow, unsigned int col, state_vector_t &_stateVector) {
    bool return_val = false;
    for (int row = 0;  row < SSIZE; row++ ) {
        if ( row != valueRow  && _stateVector[row][col].state != 0 ) {
            if (_value == _stateVector[row][col].state) {
                return_val = true;
                break;
            }
        }
    }
    return return_val;
}

bool removeFromCol(unsigned int valueRow, unsigned int col, state_vector_t &_stateVector) {
    bool returnVal = true;
    int _value = _stateVector[valueRow][col].state;
    for (int row = 0;  row < SSIZE; row++ ) {
        if ( row != valueRow && _stateVector[row][col].state == 0) {
            returnVal = removePossibleValue(row, col, _value, _stateVector);
        }
    }
    return returnVal;
}

bool removeFromBox(unsigned int row, unsigned int col, state_vector_t &_stateVector) {
    bool returnVal = true;
    int start_row = row - row % 3;
    int start_col = col - col % 3;
    int _value = _stateVector[row][col].state;
    for (int r = start_row; r < start_row+3; r++) {
        for (int c = start_col; c < start_col+3; c++) {
            if (!(r == row && c == col) ) {
                returnVal = removePossibleValue(r, c, _value, _stateVector);
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
            if (!(r == row && c == col) && _stateVector[r][c].state != 0) {
                if (_value == _stateVector[r][c].state) {
                    return_val = true;
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
                _stateVector[row][col].state = value;
                _stateVector[row][col].possibilities.clear();
            }
        }
    }
}