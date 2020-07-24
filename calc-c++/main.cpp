#include <iostream> 
#include <vector>
#include <type_traits>
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

std::vector<std::vector<int>> vector_handler(int argc, char* argv[])
{
    std::string x;
    std::vector<int> v1, v2;
    int a;
        
        for (int i=4; i < argc; i++)
        {
            x = argv[i];
            if (x.compare("-v2") != 0)
            {
                v1.push_back(std::stoi(x));
            } else 
            {
                a = i;
                break;
            }
        }
        
        for (int i=a+1; i < argc; i++)
        {
            x = argv[i];

            v2.push_back(std::stoi(x));
        }
    
//         for (int i=0; i < v1.size(); i++)
//         {
//             std::cout << v1[i] << "\t" << v2[i] << std::endl;
//         }
        return {v1, v2};
}

int main(int argc, char* argv[])
{
//     std::vector<int> v1 = {1, 4};
//     std::vector<int> v2 = {3, 2};
//     
//     std::vector<int> v3 = {1, 2, 3};
//     std::vector<int> v4 = {1, 5 ,7};
    Calculator calc;
    
    int operation = std::stoi(argv[2]); // user-specified operation

    std::string x = argv[1];
    
    if (x.compare("-v") == 0)
    {
        std::vector<std::vector<int>> vectors = vector_handler(argc, argv);
        
        switch(operation)
        {
            case 0:
                std::cout << calc.dot_product(vectors[0], vectors[1]) << std::endl;
        }
        
    } 
    
}
