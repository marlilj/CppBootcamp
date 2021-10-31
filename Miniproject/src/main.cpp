#include"reader.h"
#include"printer.h"
#include"solver.h"
#include<vector>
#include<iostream>
#include"variable_definitions.h"

extern int numberOfGuesses;

int main(int argc, char **argv) {

    // VARIABLES SET BY USER
    bool useBruteForce = true;
    bool prettyPrint = false;

    if ( argc == 1 ) {
        std::cout << "No input argument provided. Exiting ..." << std::endl;
        return 1;
    } else if ( argc > 2) {
        std::cout << "Too many input arguments provided. Exiting ..." << std::endl;
        return 1;
    }
    auto startProgram = std::chrono::high_resolution_clock::now();
    std::string input = argv[1];

    if ((input.substr(input.find_last_of(".") + 1)) == "csv") {
        sudoku_t originalSudoku;
        // Try to parse csv sudoku, if wrong format, exit
        if (readCsv(argv[1], originalSudoku)) {
            sudokuSolver(originalSudoku, useBruteForce, prettyPrint);
        } else {
            std::cout << "Exiting..." << std::endl;
            return 1;
        }
    } else if (((input.substr(input.find_last_of(".") + 1)) == "txt")) {
        std::vector<std::string> sudokuInputList = readTxt(input);
        int numberOfSudokus = sudokuInputList.size();
        int numberSolvedSudokus = 0;
        for (std::string s: sudokuInputList) {
            sudoku_t originalSudoku = {};

            // Reset brute force counter
            ::numberOfGuesses = 0;
            if ( parseSudoku(s, originalSudoku) ) {
                if (sudokuSolver(originalSudoku, useBruteForce, prettyPrint)) {
                    numberSolvedSudokus++;
                }
                std::cout << "Number of guesses in brute force was:  " << ::numberOfGuesses << std::endl << std::endl;
            }
        }
        std::cout << "Solved " << numberSolvedSudokus << " of " << numberOfSudokus << std::endl;
    } else {
        std::cout << "Wrong file format..." << std::endl;
        return 1;
    }
    auto endProgram = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endProgram - startProgram);
    std::cout << "Total program execution time (ms): " << duration.count() << std::endl;
    

    return 0;
}