#include"printer.h"

void print(sudoku_t &sudokuPuzzle) {
    std::cout << "\n----------------------------" << std::endl;
    for (int i=0; i<SSIZE; i++) {
        std::cout << "| ";
            for (int j=0; j<SSIZE; j++) {
                std::cout << sudokuPuzzle[i][j] << " ";
                if ((j+1)%3 == 0) {
                    std::cout << " | ";
                }
            }
            std::cout << std::endl;
            if ((i+1)%3 == 0) {
                std::cout << "----------------------------" << std::endl;
            }
        }
}

void print(state_vector_t &intermediateState) {
    std::cout << "\n-------------------------------------------------------------------------------------------------" << std::endl;
    for (int row = 0 ; row < SSIZE; row++) {
        std::cout << "|\t";
        for (int col = 0;  col < SSIZE; col++ ) {
            square_t square = intermediateState[row][col];
            if (square.state == 0 ) {
                for (int x: square.possibilities) {
                    std::cout << x;
                }
            } else {
                std::cout <<square.state;
            }
            if ((col+1)%3 == 0) {
                std::cout << "\t|\t";
            } else {
                std::cout << "\t";
            }
        }
        std::cout << std::endl;
        if ((row+1)%3 == 0) {
            std::cout << "-------------------------------------------------------------------------------------------------" << std::endl;
        }
    }
}

void printLine(sudoku_t &sudokuPuzzle) {
    for (int i=0; i<SSIZE; i++) {
            for (int j=0; j<SSIZE; j++) {
                if (sudokuPuzzle[i][j] == 0) {
                    std::cout << '.';
                } else {
                    std::cout << sudokuPuzzle[i][j];
                }
            }
        }
    std::cout << std::endl;
}

void printLine(state_vector_t &intermediateState) {
    for (int row = 0 ; row < SSIZE; row++) {
        for (int col = 0;  col < SSIZE; col++ ) {
            if (intermediateState[row][col].state != 0) {
                std::cout << intermediateState[row][col].state;
            } else {
                std::cout << '.';
            }
        }
    }
    std::cout << std::endl;
}