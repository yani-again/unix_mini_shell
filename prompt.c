#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <time.h>
#include "prompt.h"
#include "constants.h"

void dup_prompt(char *prompt_buff, int prompt_size)
{
    FILE *fd_config;
    fd_config = fopen(CONFIG_FILE, "r");
    if (fd_config == NULL)
    {
        printf("Couldn't open %s\n", CONFIG_FILE);
        fprintf(stderr, "%s\n");
        exit(1);
    }

    fgets(prompt_buff, prompt_size, fd_config);

    fclose(fd_config);
    return;
}

void tokenize_prompt(char **prompt)
{
    char *raw_prompt = (char*)malloc(LINE_MAX * sizeof(char));
    dup_prompt(raw_prompt, LINE_MAX);

    int row, col;
    char in_special_word = 0;
    for (int i = row = col = 0; i < LINE_MAX; ++i)
    {
        // end of prompt
        if (raw_prompt[i] == '\0' || raw_prompt[i] == '\n')
        {
            prompt[row + 1][0] = '\0';
            break;
        }
                    
        // normal appending
        if (!in_special_word && 
                raw_prompt[i] != '$' && 
                raw_prompt[i + 1] != '{')
        {
            prompt[row][col++] = raw_prompt[i];
        }

        // entering special word
        if (!in_special_word &&
                raw_prompt[i] == '$' &&
                raw_prompt[i + 1] == '{')
        {
            in_special_word = 1;
            if (i != 0)
            {
                ++row;
            }
            ++i;
            col = 0;
            continue;
        }

        // inside special word
        if (in_special_word &&
                raw_prompt[i] != '}')
        {
            prompt[row][col++] = raw_prompt[i];
        }

        // exiting special word
        if (in_special_word &&
                raw_prompt[i] == '}')
        {
            in_special_word = 0;
            ++row;
            col = 0;
            continue;
        }
    }

    free(raw_prompt);
    return;
}

void print_prompt(char **prompt, char *user, char *hostname, char *pwd, char *home,
                  char prompt_char)
{
    time_t now;
    struct tm *now_local;

    time(&now);
    now_local = localtime(&now);

    if (now_local == NULL)
    {
        perror("localtime failed\n");
        exit(1);
    }

    for (int i = 0; i < PROMPT_TOKENS_MAX && prompt[i][0] != '\0'; ++i)
    {
        if (!strcmp(prompt[i], "USER"))
        {
            printf("%s", user);
        }
        else if (!strcmp(prompt[i], "HOSTNAME"))
        {
            printf("%s", hostname);
        }
        else if (!strcmp(prompt[i], "PWD"))
        {
            printf("%s", strcmp(pwd, home) ? pwd : "~");
        }
        else if (!strcmp(prompt[i], "PROMPT_CHAR"))
        {
            printf("%c", prompt_char);
        }
        else if (!strcmp(prompt[i], "TIME_24"))
        {
            printf("%d:%d:%d", now_local->tm_hour, now_local->tm_min, now_local->tm_sec);
        }
        else if (!strcmp(prompt[i], "TIME_12"))
        {
            printf("%d:%d:%d", 
                   now_local->tm_hour < 12 ? now_local->tm_hour : now_local->tm_hour - 12, 
                   now_local->tm_min, 
                   now_local->tm_sec);
        }
        else
        {
            printf("%s", prompt[i]);
        }
    }
    putchar('\n');
}

