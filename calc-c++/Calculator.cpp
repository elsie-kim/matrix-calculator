#include "Calculator.h"


// Calculates the dot product of two vectors v1 and v2

float Calculator::dot_product(std::vector<float>& v1, std::vector<float>& v2)
{
    float sum = 0;
    
    for (int i=0; i < v1.size(); i++)
    {
        sum += v1[i] * v2[i];
    }
    
    return sum;
}
