#ifndef READER
#define READER

#include"variable_definitions.h"
#include <iostream>
#include <fstream>
#include <sstream>

bool read_csv(std::string file_name, sudoku &original_sudoku);
std::vector<std::string> read_txt(std::string file_name);
bool parse_sudoku(std::string _sudoku_string, sudoku &_sudoku_array);

#endif