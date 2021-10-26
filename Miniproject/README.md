# This is the README file for Miniproject

The code is compiled using below command, in the Miniproject/ folder.

´´´
g++ main.cpp solver.cpp printer.cpp reader.cpp brute_force.cpp variable_definitions.h -o main
´´´

the program is called using
´´´
./main <path_to_file>
´´´

Supported formats are a .csv and .txt.

.csv file as below with 0 for empty square
´´´
3, 0, 6, 5, 0, 8, 4, 0, 0
5, 2, 0, 0, 0, 0, 0, 0, 0
0, 8, 7, 0, 0, 0, 0, 3, 1
0, 0, 3, 0, 1, 0, 0, 8, 0
9, 0, 0, 8, 6, 3, 0, 0, 5
0, 5, 0, 0, 9, 0, 6, 0, 0
1, 3, 0, 0, 0, 0, 2, 5, 0
0, 0, 0, 0, 0, 0, 0, 7, 4
0, 0, 5, 2, 0, 6, 3, 0, 0
´´´

.txt file with one sudoku per line and . for empty square
´´´
4.....8.5.3..........7......2.....6.....8.4......1.......6.3.7.5..2.....1.4......
52...6.........7.13...........4..8..6......5...........418.........3..2...87.....
6.....8.3.4.7.................5.4.7.3..2.....1.6.......2.....5.....8.6......1....
´´´

in main.cpp you may set two flags to decide if brute force is allowed and if
sudokus should be pretty printed with intermediate constraint propagation step
or just on one line. Below values are set by default.
´´´
// VARIABLES SET BY USER
bool useBruteForce = true;
bool prettyPrint = false;
´´´