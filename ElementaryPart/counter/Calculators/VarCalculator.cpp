/*
Example : var(x) = 3 => x = 3
Use Example : 1 + x => 1 + 3 => 4
*/

#include "Calculators.h"

std::pair<std::string, double> DefineVariable(std::vector<std::pair<Token, std::string>> input)
{
    std::string name = input[1].second;
    double value = getNum(input[4].second);

    return {name, value};
}
