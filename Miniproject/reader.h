#ifndef READER
#define READER

#include"variable_definitions.h"
#include <iostream>
#include <fstream>
#include <sstream>

bool read_csv(std::string file_name, sudoku &original_sudoku);

#endif