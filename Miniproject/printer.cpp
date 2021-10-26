#include"printer.h"

void print(sudoku_t &sudokuPuzzle) {
    std::cout << "----------------------------" << std::endl;
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
    std::cout << "-------------------------------------------------------------------------------------------------" << std::endl;
    for (int row = 0 ; row < SSIZE; row++) {
        std::cout << "|\t";
        for (int col = 0;  col < SSIZE; col++ ) {
            for (int x: intermediateState[row][col]) {
                std::cout << x;
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