#include"main.h"


int main(int argc, char **argv) {

    if ( argc == 1 ) {
        std::cout << "No input argument provided. Exiting ..." << std::endl;
        return 1;
    } else if ( argc > 2) {
        std::cout << "Too many input arguments provided. Exiting ..." << std::endl;
        return 1;
    }

    std::string input = argv[1];

    if ((input.substr(input.find_last_of(".") + 1)) == "csv") {
        sudoku_t originalSudoku;
        // Try to parse csv sudoku, if wrong format, exit
        if (readCsv(argv[1], originalSudoku)) {
            sudokuSolver(originalSudoku);
        } else {
            std::cout << "Exiting..." << std::endl;
            return 1;
        }
    } else if (((input.substr(input.find_last_of(".") + 1)) == "txt")) {
        std::vector<std::string> sudokuInputList = readTxt(input);
        for (std::string s: sudokuInputList) {
            sudoku_t originalSudoku = {};
            if ( parseSudoku(s, originalSudoku) ) {
                sudokuSolver(originalSudoku);
            }
        }
    } else {
        std::cout << "Wrong file format..." << std::endl;
        return 1;
    }
    

    return 0;
}