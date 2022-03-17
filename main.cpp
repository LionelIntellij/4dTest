#include <iostream>
#include "JsonParser.h"


int main(int argc, char** argv)
{

    if (argc < 2)
    {
        printf("usage: %s only json text is necessary\n please check your arguement", argv[0]);
        return 1;
    }
    
    JsonParser parser(argv[1]);
    if (parser.parse())
    {
        std::cout << "Parsed sussesfully " << std::endl;
        std::cout << "your Json is valid " << std::endl;
    }
    else 
    {
            std::cout << "your Json is not valid " << std::endl;
            std::string error = parser.getError();
            if (!error.empty())
            {
                std::cout << error << std::endl;
            }
    }
    
    return 0;
}
