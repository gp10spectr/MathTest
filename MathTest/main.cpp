#include "MathTest.h"
#include <iostream>

int main() {
    std::cout << "--- Test 1: 5 random questions between [1, 100] --\n";
    MathTest t1(5);
    t1.run();

    std::cout << "\n--- Test 1: 3 questions, between [10, 20], operation '+' --\n";
    MathTest t2(3, 10, 20, '+');
    t2.run();

    std::cout << "\n--- Test 3: 4 questions, between [1, 9], operation '*' ---\n";
    MathTest t3(4, 1, 9, '*');
    t3.run();

    return 0;
}
