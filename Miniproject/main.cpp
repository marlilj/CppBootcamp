#include"main.h"


int main(int argc, char **argv) {
    auto start_program = std::chrono::high_resolution_clock::now();

    if ( argc == 1 ) {
        std::cout << "No input argument provided. Exiting ..." << std::endl;
        return 1;
    } else if ( argc > 2) {
        std::cout << "Too many input arguments provided. Exiting ..." << std::endl;
        return 1;
    }

    sudoku original_sudoku;
    // Try to parse sudoku, if wrong format, exit
    if (read_csv(argv[1], original_sudoku)) {

        // Start timer for complete program
        std::cout << "Printing original Sudoku:" << std::endl;
        print(original_sudoku);

        state_vector solution_sudoku;

        // Populate solution_sudoku with [1,9] on all squares
        for (int row=0; row<SSIZE; row++) {
            for (int col=0; col<SSIZE; col++) {
                solution_sudoku[row][col] = {1,2,3,4,5,6,7,8,9};
            }
        }

        // Replace possible solutions with correct values from input sudoku
        prepare_intermediate_state(solution_sudoku, original_sudoku);

        // Run constraint propagation, if sudoku is solved, print and exit
        if ( constraint_propagation(solution_sudoku, original_sudoku) ) {
            std::cout << "Solved puzzle after constraint propagation:" << std::endl;
            print(solution_sudoku);
        // If not entirely solved, start brute forcing on remaining possible solutions
        } else {
            std::cout << "Printing puzzle after constraint propagation:" << std::endl;
            print(solution_sudoku);

            // Start timer for bruteforce
            auto start_brute_force = std::chrono::high_resolution_clock::now();
            if ( brute_force(solution_sudoku, 0, 0) ) {
                std::cout << "Solved puzzle after using brute force on top. Solution:" << std::endl;
            } else {
                std::cout << "Couldn't solve puzzle with brute force either. We cam this far:" << std::endl;
            }
            // End timer for bruteforce
            auto end_brute_force = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_brute_force - start_brute_force);

            print(solution_sudoku);
            std::cout << "Execution time for brute force (ms): " << duration.count() << std::endl;
        }

        // End timer for complete program
        auto end_program = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_program - start_program);
        std::cout << "Total execution time (ms): " << duration.count() << std::endl;
    } else {
        std::cout << "Exiting..." << std::endl;
        return 1;
    }

    return 0;
}