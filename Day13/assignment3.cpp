#include <set>
#include <stdlib.h>
#include <iostream>
#include <iterator>
#include <vector>
#include <tuple>

std::tuple<int, int> boundary_binary_search(int value, std::vector<int> const &sequence) {
    int low=0;
    int low_prev = -1;
    int high = sequence.size()-1;
    int high_prev = -1;;
    int mid = -1;

    std::tuple<int,int> return_value;

    if (value < sequence[low]) {
        std::cout << "Value is below lowest value in sequence" << std::endl;
        return_value = std::make_tuple(-1, 0);
    } else if (value > sequence[high]) {
        std::cout << "Value is higher than biggest value in sequence" << std::endl;
        return_value = std::make_tuple(high, -1);
    } else if ( value==sequence[high] || value==sequence[low] ) {
        return_value = std::make_tuple(value, value);
    } else {
        while ( !(low == low_prev) && !(high == high_prev) ) {
            mid = low + (high-low)/2;
            if (sequence[low] < value && value < sequence[mid]) {
                high_prev = high;
                high = mid;
            } else if ( sequence[high] > value && value > sequence[mid] ) {
                low_prev = low;
                low = mid;
            } else if (sequence[mid] == value) {
                low_prev = low;
                high_prev = high;
                low = mid;
                high = mid;
            }            
        }
        return_value = std::make_tuple(sequence[low], sequence[high]);
    }
    return return_value;    
}

int main(int argc, char * argv[]) {

    std::multiset<int> sequence_set;

    for (unsigned int i = 0; i < 1024; i++) {
        sequence_set.insert(std::rand() % 10000);
    }

    std::vector<int> sequence_vector(sequence_set.begin(), sequence_set.end());

    std::cout << "Printing sequence: " << std::endl;
    for (int s: sequence_vector) {
        std::cout << s << " ";
    }
    std::cout << std::endl << std::endl;

    int random_number = std::rand() % *(sequence_set.rbegin());
    std::tuple<int,int> b = boundary_binary_search(random_number, sequence_vector);
    std::cout << "The new random number is " << random_number << std::endl;
    std::cout << "The upper bound in sequence is " << std::get<0>(b) << std::endl;
    std::cout << "The lower bound in sequence is " << std::get<1>(b) << std::endl;
}