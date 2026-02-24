/*
Most of the code was code by ChatGPT actually
*/
#include "Calculators.h"

static bool containsFunToken(const std::vector<std::pair<Token, std::string>>& v)
{
    for (auto& p : v) if (p.first == FUN) return true;
    return false;
}

std::vector<std::pair<Token, std::string>> FoldFunctionCalls(
    const std::vector<std::pair<Token, std::string>>& input,
    const std::vector<std::pair<Token, std::string>>& function,
    const std::map<std::string, double>& variables,
    Error& err)
{
    err = NO_ERROR;

    std::vector<std::pair<Token, std::string>> out;

    for (size_t i = 0; i < input.size(); ++i)
    {
        Token t = input[i].first;

        if (t == END)
        {
            out.push_back({END, "END"});
            break;
        }

        if (t != FUN)
        {
            out.push_back(input[i]);
            continue;
        }

        if (i + 1 >= input.size() || input[i + 1].first != LPARE)
        {
            err = ERROR_SYNTAX_ERROR;
            return {};
        }

        int depth = 0;
        size_t j = i + 1;
        for (; j < input.size(); ++j)
        {
            if (input[j].first == LPARE) depth++;
            else if (input[j].first == RPARE)
            {
                depth--;
                if (depth == 0) break;
            }
        }
        if (j >= input.size() || input[j].first != RPARE)
        {
            err = ERROR_MISSING_PARENTHESIS;
            return {};
        }

        std::vector<std::pair<Token, std::string>> argTokens;
        for (size_t k = i + 2; k < j; ++k) argTokens.push_back(input[k]);
        argTokens.push_back({END, "END"});

        if (containsFunToken(argTokens))
        {
            err = ERROR_INVALID_ARGUMENT;
            return {};
        }

        std::string argStr = CommenCalculate(argTokens, {}, variables);
        double arg = getNum(argStr);

        if (function.empty())
        {
            err = ERROR_INVALID_ARGUMENT;
            return {};
        }

        Error ferr = NO_ERROR;
        std::map<std::string, double> localVars;
        localVars["x"] = arg;

        double fval = CalculateFunction(function, localVars, ferr);
        if (ferr != NO_ERROR)
        {
            err = ferr;
            return {};
        }

        out.push_back({NUM, std::to_string(fval)});

        i = j;
    }

    if (out.empty() || out.back().first != END) out.push_back({END, "END"});
    return out;
}