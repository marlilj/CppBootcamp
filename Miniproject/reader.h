#include <iostream>
#include <fstream>
#include <sstream>

using sudoku = int[9][9];

void read_csv(std::string file_name, sudoku &original_sudoku);