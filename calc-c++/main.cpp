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

// handles vector inputs (when "-v" is used)
std::vector<std::vector<int>> vector_handler(int argc, char* argv[])
{
    std::string x;
    std::vector<int> v1, v2;
    int a; 
        
    	// put each component of vector 1 into vector v1
        for (int i=4; i < argc; i++)
        {
            x = argv[i];
	    // collecting each component until the indicator for vector 2 appears
            if (x.compare("-v2") != 0)
            {
		// type case integer and add component to vector
                v1.push_back(std::stof(x));
            } else 
            {
		// a is the index of "-v2"
                a = i;
                break;
            }
        }
        
	// put each component of vector 2 into vector v2
	for (int i=a+1; i < argc; i++)
        {
		
		x = argv[i];

		v2.push_back(std::stof(x));
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
    
    // checking for "-v", which indicates vector operation
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
