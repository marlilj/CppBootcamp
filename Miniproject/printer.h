#include<iostream>
#include<vector>

using sudoku = int[9][9];
using state_vector = std::vector<std::vector<std::vector<int>>>;

void print(sudoku &sudoku_puzzle);
void print(state_vector &intermediate_state);