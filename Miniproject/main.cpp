#include"main.h"

/* 
    0. Understand how the arguments are read
    1. read in one .csv file with a sudoku, 0 displays empty slots
    2. solve it using some algorithm and store in another 
    3. print the solved sudoku to console

    -- start with reading in one csv file and store in array in dynamic memory.
    -- make a print function that can be used for debugging also
    -- understand what solvers there are that can be used and decide on one
    -- implement it
*/

int main(int argc, char **argv) {
    std::cout << "argc:" << argc << std::endl;
    for (int i=0; i<argc; i++) {
        std::cout << "argv: " << argv[i] << std::endl;
    }
    sudoku original_sudoku;
    read_csv(argv[1], original_sudoku);
    std::cout << "Printing original Sudoku:" << std::endl;
    print(original_sudoku);
    
    std::cout << "Printing initial intermediate state:" << std::endl;
    state_vector intermedate_state(9, std::vector<std::vector<int>> (9,{1,2,3,4,5,6,7,8,9}));
    print(intermedate_state);
    prepare_intermediate_state(intermedate_state, original_sudoku);

    std::cout << "Printing after preparation: " << std::endl;
    print(intermedate_state);

    parse_input_sudoku(intermedate_state, original_sudoku);
    std::cout << "Printing intermediate state after parsing:" << std::endl;
    print(intermedate_state);

}