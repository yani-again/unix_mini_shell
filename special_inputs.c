#include <stdint.h>
#include "special_inputs.h"
#include "constants.h"

/* Detects if > redirection operations are present.
 * If yes, returns the index of the redirection
 * operator, else returns -1.
 * Expects: 2d char array of tokenized inputs. 
 * Returns: uint8_t with a single bit turned on. */
uint8_t o_redirect(char **input)
{
    for (int i = 0; input[i][0] != '\0'; ++i)
    {
        if (input[i][0] == '>')
        {
            return O_REDIRECT;
        }
    }
    return 0;
}

/* Like o_redirect, but for the < operator. */
uint8_t i_redirect(char **input)
{
    for (int i = 0; input[i][0] != '\0'; ++i)
    {
        if (input[i][0] == '<')
        {
            return I_REDIRECT;
        }
    }
    return 0;
}

/* Collects all flags into 1 place to make it more
 * convenient than having 1 monolithic function.
 * Expects: 2d char array of tokenized inputs.
 * Returns: uint8_t of raised flags. */
uint8_t get_flags(char **input)
{
    uint8_t o_redirect_flag = o_redirect(input);
    uint8_t i_redirect_flag = i_redirect(input);

    return
        o_redirect_flag | i_redirect_flag;
}
