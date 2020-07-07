#include <iostream> 
#include <vector>

#include "Calculator.h"

std::ostream& operator << (std::ostream& output, std::vector<int> v)
{
    std::string output_line = "(" + v[0];
    for (int i=1; i < v.size(); i++)
    {
        output_line += ", " + v[i];
    }
    output_line += ")";
    
    output << output_line;
    return output;
};

int main()
{
    std::vector<int> v1 = {1, 4};
    std::vector<int> v2 = {3, 2};
    
    std::vector<int> v3 = {1, 2, 3};
    std::vector<int> v4 = {1, 5 ,7};
    
    Calculator calc;
    
    std::cout << calc.dot_product(v1, v2) << std::endl;
    std::cout << calc.dot_product(v3, v4) << std::endl;
    
}
