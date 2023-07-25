#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_COMMAND_LENGTH 100
#define MAX_ARGUMENTS 10

void display_prompt();
void split_command_arguments(char *command, char **arguments);
void free_command_arguments(char **arguments);
int is_exit_command(char *command);
int execute_exit_command(char **arguments);
int is_setenv_command(char *command);
int execute_setenv_command(char **arguments);
int is_unsetenv_command(char *command);
int execute_unsetenv_command(char **arguments);
int is_cd_command(char *command);
int execute_cd_command(char **arguments);
/**
 * int main()-The main function of the shell program.
 * Returns: 0 upon successful execution
 */
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
int exit_status = execute_exit_command(arguments);
exit(exit_status);
}
else if (is_setenv_command(arguments[0]))
{
execute_setenv_command(arguments);
}
else if (is_unsetenv_command(arguments[0]))
{
execute_unsetenv_command(arguments);
}
else if (is_cd_command(arguments[0]))
{
execute_cd_command(arguments);
}
else
{
// Handle other commands
// ...
}
}
free_command_arguments(arguments);
}
return 0;
}
/**
 * void display_prompt()-Displays the prompt for the shell ("> ").
 * Returns: Void
 */
void display_prompt()
{
printf("> ");
fflush(stdout);
}
/**
 * void split_command_arguments-Splits the command string into separate arguments
 * command-The input command string
 * arguments-an array of strings to store the split arguments
 * Return: Void
 */
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
if (*token == '\0')
{
break;
}
arguments[arg_index++] = token;
while (*token != '\0' && *token != ' ' && *token != '\t')
{
token++;
}
if (*token == '\0')
{
break;
}
*token++ = '\0';
}
arguments[arg_index] = NULL;
}
/**
 * void free_command_arguments-Frees the memory allocated for the command arguments
 * arguments-An array of strings containing the split arguments
 * Returns: Void
 */
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
int execute_exit_command(char **arguments)
{
int exit_status = 0;
if (arguments[1] != NULL)
{
exit_status = atoi(arguments[1]);
}
return exit_status;
}
int is_setenv_command(char *command)
{
return strcmp(command, "setenv") == 0;
}
int execute_setenv_command(char **arguments)
{
if (arguments[1] != NULL && arguments[2] != NULL)
{
if (setenv(arguments[1], arguments[2], 1) != 0)
{
fprintf(stderr, "Failed to set environment variable\n");
}
}
else
{
fprintf(stderr, "Invalid setenv command syntax\n");
}
return 0;
}
int is_unsetenv_command(char *command)
{
return strcmp(command, "unsetenv") == 0;
}

int execute_unsetenv_command(char **arguments)
{
if (arguments[1] != NULL)
{
if (unsetenv(arguments[1]) != 0)
{
fprintf(stderr, "Failed to unset environment variable\n");
}
}
else
{
fprintf(stderr, "Invalid unsetenv command syntax\n");
}
return 0;
}
/**
 * int is_cd_command(char *command)-Checks if the given command is the "cd" command
 * command-the input command string
 * Returns: 1 if it is the "cd" command, 0 otherwise
 */
int is_cd_command(char *command)
{
return strcmp(command, "cd") == 0;
}
/**
 * int execute_cd_command(char **arguments)-Executes the "cd" command to change the working directory.
 * arguments-An array of strings containing the split arguments.
 * Returns:always returns 0
 */
int execute_cd_command(char **arguments)
{
char *dir = arguments[1];
if (dir == NULL || strcmp(dir, "~") == 0)
{
dir = getenv("HOME");
}
else if (strcmp(dir, "-") == 0)
{
dir = getenv("OLDPWD");
}
if (dir != NULL)
{
// Save the current working directory
char cwd[1024];
getcwd(cwd, sizeof(cwd));
if (chdir(dir) != 0)
{
fprintf(stderr, "Failed to change directory\n");
}
else
{
setenv("PWD", dir, 1);
setenv("OLDPWD", cwd, 1);
}
}
else
{
fprintf(stderr, "Invalid cd command syntax\n");
}
return 0;
}

