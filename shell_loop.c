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
int execute_command(char **arguments);

int main()
{
char command[MAX_COMMAND_LENGTH];
char *arguments[MAX_ARGUMENTS];
int previous_command_status = 0; // Status of the previous command

while (1)
{
display_prompt();
fgets(command, sizeof(command), stdin);
command[strcspn(command, "\n")] = '\0';
char *token = strtok(command, ";");
while (token != NULL)
{
char *trimmed_command = token;
while (*trimmed_command == ' ')
{
trimmed_command++;
}
size_t len = strlen(trimmed_command);
while (len > 0 && trimmed_command[len - 1] == ' ')
{
trimmed_command[--len] = '\0';
}
split_command_arguments(trimmed_command, arguments);
if (arguments[0] != NULL)
{
if (is_exit_command(arguments[0]))
{
int exit_status = execute_exit_command(arguments);
exit(exit_status);
}
else if
(is_setenv_command(arguments[0]))
{
execute_setenv_command(arguments);
}
else if
(is_unsetenv_command(arguments[0]))
{
execute_unsetenv_command(arguments);
}
else if
(is_cd_command(arguments[0]))
{
execute_cd_command(arguments);
}
else
{
// Handle other commands
//  Execute the command based on the previous command status
if (previous_command_status == 0 && strcmp(arguments[0], "&&") == 0)
{
// Skip the command after && if the previous command had an error
}
else if(previous_command_status != 0 && strcmp(arguments[0], "||") == 0)
{
// Skip the command after || if the previous command was successful
}
else
{
// Execute the command
previous_command_status = execute_command(arguments);
}
}
}
free_command_arguments(arguments);
token = strtok(NULL, ";");
}
}
return 0;
}
void display_prompt()
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
/**
 * int execute_command(char **arguments)-function takes an array of command arguments
 * execvp-attempts to execute an external command 
 * Return: -1;
 */
int execute_command(char **arguments)
pid_t pid;
int status;
pid = fork();
if (pid < 0)
{
perror("Fork failed");
return -1;
}
else if (pid == 0)
{
// Child process
// Execute the command
if (execvp(arguments[0], arguments) == -1)
{
perror("Command execution failed");
exit(EXIT_FAILURE);
}
exit(EXIT_SUCCESS);
}
else
{
// Parent process
// Wait for the child process to complete
if (waitpid(pid, &status, 0) == -1)
{
perror("Error waiting for child process");
return -1;
}
if (WIFEXITED(status))
{
return WEXITSTATUS(status);
}
else
{
fprintf(stderr, "Child process did not exit normally\n");
return -1;
}
}
}

