#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <sys/wait.h>
#include "prompt.h"
#include "constants.h"
#include "memory.h"
#include "input.h"

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

    // user input
    char raw_input[LINE_MAX];
    char **input;

    // memory allocation
    malloc_2d(&prompt, PROMPT_TOKENS_MAX, PROMPT_TOKEN_LEN);
    malloc_2d(&input, INPUT_TOKENS_MAX, INPUT_TOKEN_LEN);
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

        fgets(raw_input, sizeof(raw_input), stdin);
        tokenize_input(input, raw_input);

        // pass on empty input
        if (input[0][0] == '\0')
            continue;

        // get input token count
        int tokens = 0;
        while (input[++tokens][0] != '\0')
            ;

        // execvp options vector
        char **input_v;
        calloc_2d(&input_v, tokens, PROMPT_TOKEN_LEN);
        for (int i = 0; i <= tokens; ++i)
        {
            for (int j = 0; j < INPUT_TOKEN_LEN && input[i][j] != '\0'; ++j)
            {
                input_v[i][j] = input[i][j];
            }
        }

        int rc = fork();
        if (rc < 0)
        {
            printf("fork failed.\n");
            exit(1);
        }
        else if (rc == 0)
        {
            // execvp(path, var[])
            // printf("input[0]: %s\n", input[0]);
            execvp(input[0], input_v);
        }
        else
        {
            int rc_wait = wait(NULL);
            // printf("done! rc_wait: %d\n", rc_wait);
        }
        free_2d(input_v, tokens);
    }

    // memory de-allocation
    free_2d(prompt, PROMPT_TOKENS_MAX);
    free_2d(input, INPUT_TOKENS_MAX);
    free(pwd);
    free(hostname);
}
