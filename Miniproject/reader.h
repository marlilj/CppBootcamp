#ifndef READER
#define READER

#include"variable_definitions.h"
#include <iostream>
#include <fstream>
#include <sstream>

bool readCsv(std::string fileName, sudoku_t &originalSudoku);
std::vector<std::string> readTxt(std::string fileName);
bool parseSudoku(std::string _sudokuString, sudoku_t &_sudokuArray);

#endif