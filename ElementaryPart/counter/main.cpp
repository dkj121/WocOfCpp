#include <iostream>
#include <string>
#include <cmath>
#include <memory>
#include <stack>
#include <vector>

const double e = 2.71828182845904523536;
const double pi = 3.14159265358979323846;

enum Token
{
    EQUAL, EQUAL_EQUAL, BANG, BANG_EQUAL,
    PLUS, MINU,
    MULT, DIVI, MOD,
    SQUA,
    FPARE, LPARE,
    SIN, COS, TAN, 
    FUN, VAR, 
    NUL, NUM,
    GREATER, GREATER_EQUAL,
    LESS, LESS_EQUAL,
};

Token getToken (std::string s)
{
    switch (s[0])
    {
        case '=':
            if (s == "==")
            {
                return EQUAL_EQUAL;
            }
            return EQUAL;
        case '!':
            if (s == "!=")
            {
                return BANG_EQUAL;
            }
            return BANG;
        case '+':
            return PLUS;
        case '-':
            return MINU;
        case '*':
            if (s == "**")
            {
                return SQUA;
            }
            return MULT;
        case '/':
            return DIVI;
        case '%':
            return MOD;
        case '^':
            return SQUA;
        case ')':
            return FPARE;
        case '(':
            return LPARE;
        case 's':
            if (s == "sin(")
            {
                return SIN;
            }
            return NUL;
        case 'c':
            if (s == "cos(")
            {
                return COS;
            }
            return NUL;
        case 't':
            if (s == "tan(")
            {
                return TAN;
            }
            return NUL;
        case 'f':
            if (s == "fun(")
            {
                return FUN;
            }
            return NUL;
        case 'v':
            if (s == "var")
            {
                return VAR;
            }
            return NUL;
        case 'p':
            if (s == "pi")
            {
                return NUM;
            }
            return NUL;
        case 'e':
            if (s == "e")
            {
                return NUM;
            }
            return NUL;
        case '0': case '1': case '2': case '3': case '4':
        case '5': case '6': case '7': case '8': case '9':
            return NUM;
        case '>':
            if (s == ">=")
            {
                return GREATER_EQUAL;
            }
            return GREATER;
        case '<':
            if (s == "<=")
            {
                return LESS_EQUAL;
            }
            return LESS;
        default:
            return NUL;
    }
}
double getNum(std::string s)
{
    if (s == "pi")
    {
        return pi;
    }
    else if (s == "e")
    {
        return e;
    }
    else
    {
        return std::stod(s);
    }
}
std::string Calculator(std::stack<std::pair<Token, std::string>> input)
{
    std::string result;
    if (input.empty())
    {
        result = "NULL";
    }
    return result;
}

int main(int argc, char** argv)
{
    int c;
    std::string sinput;
    std::string s;
    std::vector<std::string> varnames;
    std::stack<std::pair<Token, std::string>> input;
    printf("table ctrl + C to finish\n");
    while (true)
    {
        int erridx = 0;
        bool haserror = false, isfun = false, isfunflag = false, isvar = false, hascmp = false;
        printf("> ");
        int idx = 0, flag = 0;
        while ((c = getchar()) != '\n')
        {
            sinput += c;
            idx++;
        }
        for (int i = 0; i < sinput.size(); i++)
        {
            if (sinput[i] == ' ')
            {
                // do nothing
            }
            else if (sinput[i] <= '9' && sinput[i] >= '0' || sinput[i] == 'p' || sinput[i] == 'e')
            {
                if (!s.empty() && flag == 2)
                {
                    input.push(std::make_pair(getToken(s), s));
                    if (getToken(s) == NUL)
                    {
                        haserror = true;
                        erridx = idx - s.size();
                    }
                    else if (getToken(s) == FUN)
                    {
                        isfun = true;
                    }
                    else if (getToken(s) == VAR)
                    {
                        isvar = true;
                    }
                    else if (getToken(s) == EQUAL || getToken(s) == EQUAL_EQUAL || getToken(s) == BANG || getToken(s) == BANG_EQUAL || getToken(s) == GREATER || getToken(s) == GREATER_EQUAL || getToken(s) == LESS || getToken(s) == LESS_EQUAL)
                    {
                        hascmp = true;
                    }
                    s.clear();
                }
                flag = 1;
                s += sinput[i];
            }
            else
            {
                if (!s.empty() && flag == 1)
                {
                    input.push(std::make_pair(getToken(s), s));
                    if (getToken(s) == NUL)
                    {
                        haserror = true;
                        erridx = idx - s.size();
                    }
                    s.clear();
                }
                flag = 2;
                s += sinput[i];
            }
        }
        input.push(std::make_pair(getToken(s), s));
        if (getToken(s) == NUL)
        {
            haserror = true;
            erridx = idx - s.size();
        }
        s.clear();
        std::string result = Calculator(input);
        if (haserror)
        {
            std::string errorline(erridx + 1, ' ');
            errorline[erridx] = '^';
            printf("  %s error here error index: %d\n", errorline.c_str(), erridx);
        }
        else
        {
            printf("%s\n", result.c_str());
        }
        while (!input.empty())
        {
            input.pop();
        }
    }
    return 0;
}
