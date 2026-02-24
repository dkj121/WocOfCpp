#ifndef CALCULATORS_H
#define CALCULATORS_H

#include <string>
#include <vector>
#include <map>
#include "../Tokens/Tokens.h"
#include "../Errors/Errors.h"

std::string CommenCalculate(const std::vector<std::pair<Token, std::string>> input,
                            const std::vector<std::pair<Token, std::string>> function,
                            const std::map<std::string, double> variables);

double CalculateFunction(const std::vector<std::pair<Token, std::string>> function,
                         const std::map<std::string, double>& variables,
                         Error& err);

std::pair<std::string, double> DefineVariable(std::vector<std::pair<Token, std::string>> input,
                                             const std::map<std::string, double>& variables);

std::vector<std::pair<Token, std::string>> DefineFunction(std::vector<std::pair<Token, std::string>> input);

std::vector<std::pair<Token, std::string>> FoldFunctionCalls(
    const std::vector<std::pair<Token, std::string>>& input,
    const std::vector<std::pair<Token, std::string>>& function,
    const std::map<std::string, double>& variables,
    Error& err);

#endif