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
    auto start_program = std::chrono::high_resolution_clock::now();
    std::cout << "argc:" << argc << std::endl;
    for (int i=0; i<argc; i++) {
        std::cout << "argv: " << argv[i] << std::endl;
    }
    sudoku original_sudoku;
    read_csv(argv[1], original_sudoku);
    std::cout << "Printing original Sudoku:" << std::endl;
    print(original_sudoku);
    
    state_vector solution_sudoku(9, std::vector<std::vector<int>> (9,{1,2,3,4,5,6,7,8,9}));
    prepare_intermediate_state(solution_sudoku, original_sudoku);
    std::cout << "Printing after preparation: " << std::endl;
    print(solution_sudoku);

    if ( constraint_propagation(solution_sudoku, original_sudoku) ) {
        std::cout << "Solved puzzle after constraint propagation:" << std::endl;
        print(solution_sudoku);
    } else {
        std::cout << "Printing puzzle after constraint propagation:" << std::endl;
        print(solution_sudoku);
        auto start_brute_force = std::chrono::high_resolution_clock::now();
        if ( brute_force(solution_sudoku, 0, 0) ) {
            std::cout << "Solved puzzle after using brute force on top. Solution:" << std::endl;
        } else {
            std::cout << "Couldn't solve puzzle with brute force either. We cam this far:" << std::endl;
        }
        auto end_brute_force = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_brute_force - start_brute_force);
        print(solution_sudoku);
        std::cout << "Execution time for brute force (ms): " << duration.count() << std::endl;
    }
    auto end_program = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_program - start_program);
    std::cout << "Total execution time (ms): " << duration.count() << std::endl;
}