/* 
Parse the input string into a vector of pairs of tokens 
and their corresponding string representations.
*/
#include "Parses.h"

std::vector<std::pair<Token, std::string>> InputParse(std::string input)
{
    std::vector<std::pair<Token, std::string>> token_input;
    while (!input.empty())
    {
        if (input.substr(0, 1) == " ")
        {
            input.erase(0, 1);
        }
        else if (input.substr(0, 3) == "sin")
        {
            token_input.push_back({SIN, "sin"});
            input.erase(0, 3);
        }
        else if (input.substr(0, 3) == "cos")
        {
            token_input.push_back({COS, "cos"});
            input.erase(0, 3);
        }
        else if (input.substr(0, 3) == "tan")
        {
            token_input.push_back({TAN, "tan"});
            input.erase(0, 3);
        }
        else if (input.substr(0, 3) == "fun")
        {
            token_input.push_back({FUN, "fun"});
            input.erase(0, 3);
        }
        else if (input.substr(0, 3) == "var")
        {
            token_input.push_back({VAR, "var"});
            input.erase(0, 3);
        }
        else if (input.substr(0, 1) == "=")
        {
            if (input.substr(0, 2) == "==")
            {
                token_input.push_back({EQUAL_EQUAL, "=="});
                input.erase(0, 2);
            }
            else
            {
                token_input.push_back({EQUAL, "="});
                input.erase(0, 1);
            }
        }
        else if (input.substr(0, 1) == "!")
        {
            if (input.substr(0, 2) == "!=")
            {
                token_input.push_back({BANG_EQUAL, "!="});
                input.erase(0, 2);
            }
            else
            {
                token_input.push_back({BANG, "!"});
                input.erase(0, 1);
            }
        }
        else if (input.substr(0, 2) == "&&")
        {
            token_input.push_back({AND, "&&"});
            input.erase(0, 2);
        }
        else if (input.substr(0, 2) == "||")
        {
            token_input.push_back({OR, "||"});
            input.erase(0, 2);
        }
        else if (input.substr(0, 1) == ">")
        {
            if (input.substr(0, 2) == ">=")
            {
                token_input.push_back({GREATER_EQUAL, ">="});
                input.erase(0, 2);
            }
            else
            {
                token_input.push_back({GREATER, ">"});
                input.erase(0, 1);
            }
        }
        else if (input.substr(0, 1) == "<")
        {
            if (input.substr(0, 2) == "<=")
            {
                token_input.push_back({LESS_EQUAL, "<="});
                input.erase(0, 2);
            }
            else
            {
                token_input.push_back({LESS, "<"});
                input.erase(0, 1);
            }
        }
        else if (input.substr(0, 1) == "+")
        {
            token_input.push_back({PLUS, "+"});
            input.erase(0, 1);
        }
        else if (input.substr(0, 1) == "-")
        {
            token_input.push_back({MINU, "-"});
            input.erase(0, 1);
        }
        else if (input.substr(0, 1) == "*")
        {
            if (input.substr(0, 2) == "**")
            {
                token_input.push_back({SQUA, "**"});
                input.erase(0, 2);
            }
            else
            {
                token_input.push_back({MULT, "*"});
                input.erase(0, 1);
            }
        }
        else if (input.substr(0, 1) == "/")
        {
            token_input.push_back({DIVI, "/"});
            input.erase(0, 1);
        }
        else if (input.substr(0, 1) == "%")
        {
            token_input.push_back({MOD, "%"});
            input.erase(0, 1);
        }
        else if (input.substr(0, 1) == "^")
        {
            token_input.push_back({SQUA, "^"});
            input.erase(0, 1);
        }
        else if (input.substr(0, 1) == "(")
        {
            token_input.push_back({LPARE, "("});
            input.erase(0, 1);
        }
        else if (input.substr(0, 1) == ")")
        {
            token_input.push_back({RPARE, ")"});
            input.erase(0, 1);
        }
        else if (input.substr(0, 4) == "null")
        {
            token_input.push_back({NUL, "null"});
            input.erase(0, 4);
        }
        else if (isdigit(input[0]) || input[0] == 'e' || input[0] == 'p')
        {
            std::string num_str;
            while (!input.empty() && (isdigit(input[0]) || input[0] == '.'|| input[0] == 'e' || input[0] == 'p'))
            {
                if (input[0] == 'p' && input.substr(0, 2) == "pi")
                {
                    num_str += "3.14159265358979323846";
                    input.erase(0, 2);
                    continue;
                }
                else if (input[0] == 'e') num_str += "2.71828182845904523536";
                else num_str += input[0];
                input.erase(0, 1);
            }
            token_input.push_back({NUM, num_str});
        }
        else if (isalpha(input[0]))
        {
            std::string param_str;
            while (!input.empty() && (isalnum(input[0]) || input[0] == '_'))
            {
                param_str += input[0];
                input.erase(0, 1);
            }
            token_input.push_back({PARAM, param_str});
        }
        else
        {
            token_input.push_back({UNKNOWN, std::string(1, input[0])});
            input.erase(0, 1);
        }
    }
    token_input.push_back({END, "END"});
    return token_input;
}