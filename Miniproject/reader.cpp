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

std::vector<std::string> read_txt(std::string file_name) {
    /*
     * This function read input files on below format
     *
     * 4.....8.5.3..........7......2.....6.....8.4......1.......6.3.7.5..2.....1.4......
     * 52...6.........7.13...........4..8..6......5...........418.........3..2...87.....
     * 6.....8.3.4.7.................5.4.7.3..2.....1.6.......2.....5.....8.6......1....
     */

    std::vector<std::string> sudoku_vector = {};

    std::string line;
    std::ifstream fin;
    std::string word;

    std::cout << "Reading file: " << file_name << std::endl;
    fin.open(file_name);

    if (fin.is_open()) {
        // Find all lines in file
        while (getline(fin,line) ) {
            sudoku_vector.push_back(line);
        }
        fin.close();
    } else {
        std::cout << "Unable to open file" << std::endl;
    }

    return sudoku_vector;
}

bool parse_sudoku(std::string _sudoku_string, sudoku &_sudoku_array) {
    /*
     * This function parses a string of below format into int[SSIZE][SSIZE] with
     * . replaced by 0
     *
     * 4.....8.5.3..........7......2.....6.....8.4......1.......6.3.7.5..2.....1.4......
     */
    bool return_value = false;
    unsigned int i = 0;
    unsigned int j = 0;
    unsigned int total_count = 0;
    for(char l : _sudoku_string) {
        // If the number is in the correct range, add it
        if ( l == '.') {
            _sudoku_array[i][j] = 0;
            total_count++;
        } else {
        int number = l - '0';
            if ( number > 0 && number < 10 ) {
                    _sudoku_array[i][j] = number;
                    total_count++;
            } else {
                std::cout << "Element (" << i << "," << j << ") is out of range [0,9], hence neglected" << std::endl;
            }
        }
        j++;
        if (j % 9 == 0) {
            j = 0;
            i++;
        }
    }

    if ( total_count == SSIZE*SSIZE) {
        return_value = true;
    }

    return return_value;
}