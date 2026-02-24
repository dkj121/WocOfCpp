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
    static std::map<std::string, double> variables;
    // only one function allowed, stored as tokens for easy substitution; empty if no function defined
    static std::vector<std::pair<Token, std::string>> function; 
    while(true)
    {
        std::string input_string = InputReader();  // read input from user as a string
        // from string to tokens, also checks for syntax errors and returns an empty vector if any are found
        std::vector<std::pair<Token, std::string>> input_tokens = InputParse(input_string); 
        if (input_tokens.empty())
        {
            continue;
        }
/*
    determine if the input is a function definition, variable definition, or calculation;
    also checks for errors like undefined variables and returns UNKNOWN if any are found
*/      
        std::pair<Token, std::string> type = TypeParse(input_tokens, variables); 
        // calculate and print the result, or print an error message if any errors are found
        if (type.first == FUNDEF)
        {
            function = DefineFunction(input_tokens);
            std::cout << "Function defined successfully." << std::endl;
            continue;
        }
        else if (type.first == VARDEF)
        {
            auto result = DefineVariable(input_tokens, variables);
            variables[result.first] = result.second;
            std::cout << result.first << " = " << result.second << std::endl;
            continue;
        }

        Error err = NO_ERROR;
        auto folded = FoldFunctionCalls(input_tokens, function, variables, err);
        if (err != NO_ERROR)
        {
            std::cout << GetErrorMessage(err) << std::endl;
            continue;
        }

        std::string result = CommenCalculate(folded, function, variables);
        std::cout << result << std::endl;
    }
    return 0;
}