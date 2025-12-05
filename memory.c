#include <stdlib.h>
#include <stdio.h>
#include "memory.h"

/* Allocates rows * columns to a 2d array using malloc.
 * Expects: pointer to 2d char array (char***), and int
 * values for rows & columns. */
void malloc_2d(char ***prompt, int rows, int columns)
{
    *prompt = (char**)malloc(rows * sizeof(char*));
    if (*prompt == NULL)
    {
        fprintf(stderr, "%s\n");
        exit(1);
    }

    for (int i = 0; i < rows; ++i)
    {
        (*prompt)[i] = (char*)malloc(columns * sizeof(char));
        if ((*prompt)[i] == NULL)
        {
            fprintf(stderr, "%s\n");
            exit(1);
        }
    }
    return;
}

/* Frees the memory of a dynamically allocated 2d array.
 * Expects: 2d char array that has been dynamically 
 * allocated. */
void free_2d(char **prompt, int rows)
{
    for (int i = 0; i < rows; ++i)
    {
        free(prompt[i]);
    }
    free(prompt);
    return;
}

/* Reallocates memory to fit the size perfectly.
 * Expects: pointer to 2d char array (char***). */
void realloc_2d(char ***prompt)
{
    int rows, columns;
    for (rows = 0; (*prompt)[rows][0] != '\0'; ++rows)
    {
        for (columns = 0; (*prompt)[rows][columns] != '\0'; ++columns)
            ;

        // realloc logic here
        (*prompt)[rows][columns++] = '\0';
        (*prompt)[rows] = realloc((*prompt)[rows], columns * sizeof(char));
    }
}
