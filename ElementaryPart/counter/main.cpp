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
    static std::vector<std::pair<Token, std::string>> function;
    while(true)
    {
        std::string input_string = InputReader();
        std::vector<std::pair<Token, std::string>> input_tokens = InputParse(input_string);
        if (input_tokens.empty())
        {
            continue;
        }

        std::pair<Token, std::string> type = TypeParse(input_tokens);

        if (type.first == NUM || type.first == NUL || type.first == PLUS || type.first == MINU || type.first == UNKNOWN)
        {
            std::string result = CommenCalculate(input_tokens, function, variables);
            std::cout << result << std::endl;
        }
        else if (type.first == FUNDEF)
        {
            std::vector<std::pair<Token, std::string>> function = DefineFunction(input_tokens);
            std::cout << "Function defined successfully." << std::endl;
        }
        else if (type.first == VARDEF)
        {
            std::pair<std::string, double> result = DefineVariable(input_tokens);
            variables[result.first] = result.second;
        }
        else
        {
            std::cout << type.second << std::endl;
            continue;
        }
    }
    return 0;
}
