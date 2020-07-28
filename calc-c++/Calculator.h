#ifndef _CALCULATOR_
#define _CALCULATOR_

#include <vector>
#include <string>
#include <iostream>

// Calculator object contains vector operation methods (such as dot product)

class Calculator 
{
    public:
        std::vector<std::string> operations = {"dot_product"};
        float dot_product(std::vector<int>& v, std::vector<int>& v2);
        
        

};

#endif
