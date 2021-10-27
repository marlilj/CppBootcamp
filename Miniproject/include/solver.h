#ifndef SOLVER
#define SOLVER

#include<iostream>
#include <algorithm>
#include <chrono>

#include"printer.h"
#include"variable_definitions.h"
#include"brute_force.h"

bool sudokuSolver(sudoku_t &originalSudoku, bool useBruteForce, bool prettyPrint);

bool constraintPropagation(state_vector_t &_stateVector, const sudoku_t &_originalSudoku);
bool sudokuIsSolved(state_vector_t &_stateVector);

void removeAndUpdatePeers(int _value, unsigned int row, unsigned int col, state_vector_t &_stateVector);
void checkUniqueValueAmongPeers(unsigned int row, unsigned int col, state_vector_t &_stateVector);

bool valueInRow(int _value, unsigned int row, unsigned int valueCol, state_vector_t &_stateVector);
bool valueInCol(int _value, unsigned int col, unsigned int valueRow, state_vector_t &_stateVector);
bool valueInBox(int _value, unsigned int row, unsigned int col, state_vector_t &_stateVector);

bool optionInRow(int _value, unsigned int row, unsigned int valueCol, state_vector_t &_stateVector);
bool optionInCol(int _value, unsigned int col, unsigned int valueRow, state_vector_t &_stateVector);
bool optionInBox(int _value, unsigned int row, unsigned int col, state_vector_t &_stateVector);

void removeFromRow(int _value, unsigned int row, unsigned int valueCol, state_vector_t &_stateVector);
void removeFromCol(int _value, unsigned int col, unsigned int valuRow, state_vector_t &_stateVector);
void removeFromBox(int _value, unsigned int row, unsigned int col, state_vector_t &_stateVector);

void prepareIntermediateState(state_vector_t &_stateVector, const sudoku_t &_originalSudoku);


#endif