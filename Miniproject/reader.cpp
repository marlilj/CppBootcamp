#include"reader.h"

void read_csv(std::string file_name, sudoku &original_sudoku) {

    // TODO: Check what happens if file doesn't contain enough arguments
    // TODO: Maybe allow other sizes?
    // TODO: File doesn't exist?

    std::string line;
    std::ifstream fin;
    std::string word;

    std::cout << "Reading file: " << file_name << std::endl;
    fin.open(file_name);

    if (fin.is_open()){
        for (int i=0; i<SSIZE; i++) {
            getline(fin,line); // store the line in line
            std::stringstream ss(line); //
            for (int j=0; j<SSIZE; j++) {
                getline(ss, word, ',');
                original_sudoku[i][j] = std::stoi(word);
            }
        }
        fin.close();
    } else {
        std::cout << "Unable to open file" << std::endl;
    }
}