#include "Tokens/Tokens.h"
#include "Errors/Errors.h"
#include "Parses/Parses.h"
#include "Reader/Reader.h"
#include "Calculators/Calculators.h"
#include <iostream>
#include <vector>
#include <map>

int main(int argc, char** argv)
{
    std::map<std::string, double> variables;
    std::map<std::string, std::pair<std::vector<std::string>, std::vector<Token>>> function;
    while(true)
    {
        std::string input_string = InputReader();
        std::vector<std::pair<Token, std::string>> input_tokens = InputParse(input_string);
        try
        {
            Token input_type = TypeParse(input_tokens);
        }
        catch(Error e)
        {
            std::cout << GetErrorMessage(e) << std::endl;
        }
        
    }
    return 0;
}
