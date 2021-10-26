#ifndef PRINTER
#define PRINTER

#include<iostream>
#include"variable_definitions.h"

void print(sudoku_t &sudokuPuzzle);
void print(state_vector_t &intermediateState);
void printLine(sudoku_t &sudokuPuzzle);
void printLine(state_vector_t &intermediateState);

#endif