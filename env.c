#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
/**
 * void execute_env_command():Executes the "env" command, which prints the current environment
 * Returns: Void
 * Parameters: None
 */

void display_prompt();
char **split_command_arguments(char *command);
void free_command_arguments(char **arguments);
int is_exit_command(char *command);
void execute_env_command();

int main()
{
char command[MAX_COMMAND_LENGTH];
while (1)
{
display_prompt();
fgets(command, sizeof(command), stdin);
command[strcspn(command, "\n")] = '\0';
char **arguments = split_command_arguments(command);
if (arguments[0] != NULL)
{
if (is_exit_command(arguments[0]))
{
free_command_arguments(arguments);
break;
}
else  if (strcmp(arguments[0], "env") == 0)
{
execute_env_command();
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
void display_prompt()
printf("> ");
fflush(stdout);
}
char **split_command_arguments(char *command)
{
char **arguments = malloc((MAX_ARGUMENTS + 1) * sizeof(char *));
char *argument;
if (arguments == NULL)
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
for (int i = 0; arguments[i] != NULL; i++)
{
free(arguments[i]);
}
free(arguments);
}
int is_exit_command(char *command)
{
return strcmp(command, "exit") == 0;
}
void execute_env_command()
{
extern char **environ;
for (char **env = environ; *env != NULL; env++)
{
printf("%s\n", *env);
}
}
