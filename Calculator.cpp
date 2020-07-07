#include "Calculator.h"

#include <iostream>

int Calculator::dot_product(std::vector<int>& v1, std::vector<int>& v2)
{
    int sum = 0;
    
    for (int i=0; i < v1.size(); i++)
    {
        sum += v1[i] * v2[i];
    }
    
    return sum;
}
