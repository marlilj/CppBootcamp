#include"printer.h"

void print(sudoku &sudoku_puzzle) {
    std::cout << "----------------------------" << std::endl;
    for (int i=0; i<9; i++) {
        std::cout << "| ";
            for (int j=0; j<9; j++) {
                std::cout << sudoku_puzzle[i][j] << " ";
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

void print(state_vector &intermediate_state) {
    std::cout << "-------------------------------------------------------------------------------------------------" << std::endl;
    for (int row = 0 ; row < intermediate_state.size(); row++) {
        std::cout << "|\t";
        for (int col = 0;  col < intermediate_state[row].size(); col++ ) {
            for (int x: intermediate_state[row][col]) {
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