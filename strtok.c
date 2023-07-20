#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_COMMAND_LENGTH 100
#define MAX_ARGUMENTS 10

/**
 * void display_prompt:Displays the shell prompt (> ) on the standard output.
 * void split_command_arguments(char *command, char **arguments):Splits the command into individual arguments.
 * void free_command_arguments(char **arguments):Frees the memory allocated for the arguments array.
 * int is_exit_command(char *command):Checks if the given command is the exit command
 * int main():he main loop of the simple shell.
 * Returns: 0 upon successful execution
 */

void display_prompt();
void split_command_arguments(char *command, char **arguments);
void free_command_arguments(char **arguments);
int is_exit_command(char *command);

int main()
{
char command[MAX_COMMAND_LENGTH];
char *arguments[MAX_ARGUMENTS];

while (1)
{
display_prompt();
fgets(command, sizeof(command), stdin);
command[strcspn(command, "\n")] = '\0';
split_command_arguments(command, arguments);
if (arguments[0] != NULL)
{
if (is_exit_command(arguments[0]))
{
break;
}
else
{
// Handle other commands
}
}
// Free the allocated memory for arguments
free_command_arguments(arguments);
}
return 0;
}
void display_prompt()
{
printf("> ");
fflush(stdout);
}
void split_command_arguments(char *command, char **arguments)
{
int arg_index = 0;
char *token = command;
while (*token != '\0' && arg_index < MAX_ARGUMENTS - 1)
{
while (*token == ' ' || *token == '\t')
{
token++;
}
arguments[arg_index] = NULL;
}
void free_command_arguments(char **arguments)
{
for (int i = 0; arguments[i] != NULL; i++)
{
free(arguments[i]);
}
}
int is_exit_command(char *command)
{
return strcmp(command, "exit") == 0;
}
