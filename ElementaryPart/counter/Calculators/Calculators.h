#ifndef CALCULATORS_H
#define CALCULATORS_H

#include <string>
#include <vector>
#include "../Tokens/Tokens.h"
#include "../Errors/Errors.h"

std::string CommenCalculate(std::vector<std::pair<Token, std::string>> input);
std::string FunctionCalculate(std::vector<std::pair<Token, std::string>> function);
std::pair<std::string, double> DefineVariable(std::vector<std::pair<Token, std::string>> input);
std::vector<std::pair<Token, std::string>> DefineFunction(std::vector<std::pair<Token, std::string>> input);

#endif