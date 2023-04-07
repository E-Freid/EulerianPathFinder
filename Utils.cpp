#include <iostream>
#include "Utils.h"

int Utils::Factorial(int i_Num) {
    int factorial = 1;

    if (i_Num < 0)
    {
       throw std::invalid_argument("Factorial of a negative number doesn't exist.");
    }

    else {
        for(int i = 1; i <= i_Num; ++i) {
            factorial *= i;
        }
    }

    return factorial;
}

