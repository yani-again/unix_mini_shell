#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include "prompt.h"
#include "constants.h"
#include "memory.h"

/* options:
 * TIME_24, TIME_12, USER, HOSTNAME, PWD,
 * PROMPT_CHAR
*/

int main() 
{
    // declare prompt variables
    char **prompt;
    char *user;
    char *hostname;
    char *home;
    char *pwd;
    char prompt_char;

    // memory allocation
    malloc_2d(&prompt, PROMPT_TOKENS_MAX, PROMPT_TOKEN_LEN);
    hostname = (char*)malloc(HOSTNAME_MAX * sizeof(char));

    // assign prompt variables
    user = getenv("USER");
    gethostname(hostname, HOSTNAME_MAX);
    home = getenv("HOME");
    pwd = strdup(home);
    prompt_char = strcmp(user, "root") ? '$' : '#';

    // shrink dynamic memory to fit
    tokenize_prompt(prompt);
    realloc_2d(&prompt);

    while (1)
    {
        print_prompt(prompt, user, hostname, pwd, home, prompt_char);
    }

    // memory de-allocation
    free_2d(prompt, PROMPT_TOKENS_MAX);
    free(pwd);
    free(hostname);
}
