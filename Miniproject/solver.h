#ifndef SOLVER
#define SOLVER

#include<vector>
#include<iostream>
#include <algorithm>

#include"printer.h"

using sudoku = int[9][9];
using state_vector = std::vector<std::vector<std::vector<int>>>;

bool constraint_propagation(state_vector &_state_vector, const sudoku &_original_sudoku);
bool sudoku_is_solved(state_vector &_state_vector);

void remove_and_update_peers(int _value, unsigned int row, unsigned int col, state_vector &_state_vector);
void check_unique_value_among_peers(unsigned int row, unsigned int col, state_vector &_state_vector);

bool value_in_row(int _value, unsigned int row, unsigned int value_col, state_vector &_state_vector);
bool value_in_col(int _value, unsigned int col, unsigned int value_row, state_vector &_state_vector);
bool value_in_box(int _value, unsigned int row, unsigned int col, state_vector &_state_vector);

bool option_in_row(int _value, unsigned int row, unsigned int value_col, state_vector &_state_vector);
bool option_in_col(int _value, unsigned int col, unsigned int value_row, state_vector &_state_vector);
bool option_in_box(int _value, unsigned int row, unsigned int col, state_vector &_state_vector);

void remove_from_row(int _value, unsigned int row, unsigned int value_col, state_vector &_state_vector);
void remove_from_col(int _value, unsigned int col, unsigned int value_row, state_vector &_state_vector);
void remove_from_box(int _value, unsigned int row, unsigned int col, state_vector &_state_vector);

void prepare_intermediate_state(state_vector &_state_vector, const sudoku &_original_sudoku);


#endif