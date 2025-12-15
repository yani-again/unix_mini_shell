#include "input.h"

void tokenize_input(char **input, char *raw_input)
{
    int i, rows, columns;
    char in_string = 0;
    char began_input = 0;
    char counted_space = 0;

    for (i = rows = columns = 0; ; ++i)
    {
        if (raw_input[i] == ' ' || raw_input[i] == '\t')
        {
            if (!began_input || counted_space)
                continue;

            if (in_string)
            {
                input[rows][columns++] = ' ';
                counted_space = 1;
                continue;
            }

            counted_space = 1;
            input[rows][columns] = '\0';
            ++rows;
            columns = 0;
        }
        else if (raw_input[i] == '\0' || raw_input[i] == '\n')
        {
            input[rows][columns] = '\0';
            input[++rows][0] = '\0';
            break;
        }
        else
        {
            if (counted_space)
                counted_space = 0;

            if (!began_input)
                began_input = 1;

            if (raw_input[i] == '"' || raw_input[i] == '\'')
            {
                in_string = in_string ? 0 : 1;
                continue;
            }
            input[rows][columns++] = raw_input[i];
        }
    }
}
