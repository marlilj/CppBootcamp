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
        sudoku original_sudoku;
        // Try to parse csv sudoku, if wrong format, exit
        if (read_csv(argv[1], original_sudoku)) {
            sudokuSolver(original_sudoku);
        } else {
            std::cout << "Exiting..." << std::endl;
            return 1;
        }
    } else if (((input.substr(input.find_last_of(".") + 1)) == "txt")) {
        std::vector<std::string> sudoku_input_list = read_txt(input);
        for (std::string s: sudoku_input_list) {
            sudoku original_sudoku = {};
            if ( parse_sudoku(s, original_sudoku) ) {
                sudokuSolver(original_sudoku);
            }
        }
    } else {
        std::cout << "Wrong file format..." << std::endl;
        return 1;
    }
    

    return 0;
}