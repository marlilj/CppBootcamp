#ifndef SOLVER
#define SOLVER

#include<iostream>
#include <algorithm>
#include <chrono>
#include <map>
#include <set>

#include"printer.h"
#include"variable_definitions.h"
#include"brute_force.h"

bool sudokuSolver(sudoku_t &originalSudoku, bool useBruteForce, bool prettyPrint);

bool constraintPropagation(state_vector_t &_stateVector);
bool sudokuIsSolved(state_vector_t &_stateVector);

bool setValue(unsigned int row, unsigned int col, unsigned int value, state_vector_t &_stateVector);
bool removeAndUpdatePeers(unsigned int row, unsigned int col, state_vector_t &_stateVector);
bool findAndSetUniqueValueAmongPeers(unsigned int row, unsigned int col, state_vector_t &_stateVector);

bool valueInRow(int _value, unsigned int row, unsigned int valueCol, state_vector_t &_stateVector);
bool valueInCol(int _value, unsigned int valueRow, unsigned int col, state_vector_t &_stateVector);
bool valueInBox(int _value, unsigned int row, unsigned int col, state_vector_t &_stateVector);

bool removeFromRow(unsigned int row, unsigned int valueCol, state_vector_t &_stateVector);
bool removeFromCol(unsigned int valueRow, unsigned int col, state_vector_t &_stateVector);
bool removeFromBox(unsigned int row, unsigned int col, state_vector_t &_stateVector);

bool removePossibleValue(unsigned int row, unsigned int col, unsigned int _value, state_vector_t &_stateVector);
bool findPossibleValuesInRowAndCol(unsigned int row, unsigned int col, state_vector_t &_stateVector,
    std::multimap<int, int> &rowPossibles, std::multimap<int, int> &colPossibles);
bool findPossibleValuesInBox(unsigned int row, unsigned int col, state_vector_t &_stateVector,
    std::multimap<int, std::pair<int, int>> &boxPossibles);

void prepareIntermediateState(state_vector_t &_stateVector, const sudoku_t &_originalSudoku);


#endif