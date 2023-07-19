#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_COMMAND_LENGTH 100
#define MAX_ARGUMENTS 10
/**
 * void display_prompt()-Displays the shell prompt (> ) on the console
 * char **split_command_arguments(char *command):Splits the user input command into individual arguments
 * void free_command_arguments(char **arguments):Frees the memory allocated for the argument array returned by
 * int main():The main function that runs the shell's main loop
 * Returns: An integer value (0) to indicate successful execution
 */

void display_prompt();
char **split_command_arguments(char *command);
void free_command_arguments(char **arguments);

int main()
{
char command[MAX_COMMAND_LENGTH];
while (1)
{
display_prompt();
fgets(command, sizeof(command), stdin);
command[strcspn(command, "\n")] = '\0';
// Split the command into arguments
char **arguments = split_command_arguments(command);
if (arguments[0] != NULL)
{
// Fork a child process
pid_t pid = fork();
if (pid == -1)
{
perror("fork");
}
else if (pid == 0)
{
// Child process
// Execute the command with arguments
execvp(arguments[0], arguments);
// execvp only returns if there's an error
perror("execvp");
// Exit the child process with a non-zero status
exit(1);
}
else
{
waitpid(pid, NULL, 0);
}
}
free_command_arguments(arguments);
}
return 0;
}
void display_prompt()
{
printf("> ");
fflush(stdout);
}
char **split_command_arguments(char *command)
{
char **arguments = malloc((MAX_ARGUMENTS + 1) * sizeof(char *));
char *argument;
if(arguments == NULL)
{
perror("malloc");
exit(1);
}
int i = 0;
argument = strtok(command, " ");
while (argument != NULL && i < MAX_ARGUMENTS)
{
arguments[i] = strdup(argument);
argument = strtok(NULL, " ");
i++;
}
arguments[i] = NULL;
return arguments;
}
void free_command_arguments(char **arguments)
{
for
(int i = 0; arguments[i] != NULL; i++)
{
free(arguments[i]);
}

