#ifndef CONSTANTS_H
#define CONSTANTS_H

#define CONFIG_FILE "/home/yani/code/c/mini-shell/.shellrc"

#define PROMPT_TOKENS_MAX 128
#define PROMPT_TOKEN_LEN 512

#define HOSTNAME_MAX 256
#define TIME_BUFF_MAX 128

#define INPUT_TOKENS_MAX 64
#define INPUT_TOKEN_LEN 1024

// indexes/shifts for flags
#define O_REDIRECT_INDEX 0
#define I_REDIRECT_INDEX 1

// flags for special prompt inputs
#define O_REDIRECT 1 << O_REDIRECT_INDEX
#define I_REDIRECT 1 << I_REDIRECT_INDEX

#endif
