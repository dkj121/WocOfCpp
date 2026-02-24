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
    static std::vector<std::pair<Token, std::string>> function; // only one function allowed, stored as tokens for easy substitution; empty if no function defined

    while(true)
    {
        std::string input_string = InputReader();
        std::vector<std::pair<Token, std::string>> input_tokens = InputParse(input_string);
        if (input_tokens.empty())
        {
            continue;
        }

        std::pair<Token, std::string> type = TypeParse(input_tokens, variables);

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