#include"reader.h"

bool read_csv(std::string file_name, sudoku &original_sudoku) {
    /*
     * This function parses input files on below format
     *
     *  3, 0, 6, 5, 0, 8, 4, 0, 0
     *  5, 2, 0, 0, 0, 0, 0, 0, 0
     *  0, 8, 7, 0, 0, 0, 0, 3, 1
     *  0, 0, 3, 0, 1, 0, 0, 8, 0
     *  9, 0, 0, 8, 6, 3, 0, 0, 5
     *  0, 5, 0, 0, 9, 0, 6, 0, 0
     *  1, 3, 0, 0, 0, 0, 2, 5, 0
     *  0, 0, 0, 0, 0, 0, 0, 7, 4
     *  0, 0, 5, 2, 0, 6, 3, 0, 0
     */

    bool return_val = false;

    std::string line;
    std::ifstream fin;
    std::string word;

    std::cout << "Reading file: " << file_name << std::endl;
    fin.open(file_name);

    unsigned int i = 0;
    unsigned int j = 0;
    unsigned int total_count = 0;

    if (fin.is_open()) {

        // Find all lines in file
        while (getline(fin,line) ) {
            std::stringstream ss(line);
            j = 0;
            // Find all strings split on ,
            while ( getline(ss, word, ',') ) {
                try {
                    // If the number is in the correct range, add it
                    if ( std::stoi(word) >= 0 && std::stoi(word) < 10 ) {
                            original_sudoku[i][j] = std::stoi(word);
                            total_count++;
                    } else {
                        std::cout << "Element (" << i << "," << j << ") is out of range [0,9], hence neglected" << std::endl;
                    }
                } catch ( const std::invalid_argument &e) {
                        std::cout << "Invalid argument (" << i << "," << j << "): " << word << std::endl;
                }
                j++;
            }
            i++;
        }
        fin.close();

        // If we have the correct number of inputs, set return value to true
        if ( total_count == SSIZE*SSIZE ) {
            return_val = true;
        } else {
            std::cout << "Correctly parsed input sudoku is of wrong size" << std::endl;
        }
    } else {
        std::cout << "Unable to open file" << std::endl;
    }

    return return_val;
}