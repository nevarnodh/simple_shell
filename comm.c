#include "shell.h"
/**
 * parse_input-function to handle comments
 * Return: Void
 */
void parse_input(char *input)
{
char *comment_start = strchr(input, '#');
if (comment_start != NULL)
{
*comment_start = '\0';
}
// Continue with the rest of the parsing logic
}

char *input = readline("prompt> ");
parse_input(input);
execute_command(input);
free(input);
