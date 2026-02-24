#include <stdio.h>
#include "Reader.h"

std::string InputReader()
{
    std::string input_string;
    int c;
    printf("> ");
    while ((c = getchar()) != '\n')
    {
        if (c == EOF)
        {
            break;
        }
        else
        {
            input_string += c;
        }
    }
    return input_string;
}
