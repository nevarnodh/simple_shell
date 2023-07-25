#include "shell.h"
/**
 * int main(int argc, char *argv[])-check if a filename is provided as a command-line argument
 * Return: SUCCESS
 */
int main(int argc, char *argv[])
{
if (argc == 2)
{
FILE *file = fopen(argv[1], "r");
if (file == NULL)
{
perror("Error opening file");
exit(EXIT_FAILURE);
}
char line[MAX_INPUT_LENGTH];
while (fgets(line, sizeof(line), file) != NULL)
{
line[strcspn(line, "\n")] = '\0';  // Remove the newline character
execute_command(line);
}
fclose(file);
return EXIT_SUCCESS;
}
/**
 * execute_command-function is responsible for executing external commands
 * arguments-execute an external command
 * Return -1
 */
void execute_command(char *command)
{
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
if (execvp(arguments[0], arguments) == -1)
{
perror("Command execution failed");
exit(EXIT_FAILURE);
}
exit(EXIT_SUCCESS);
}
else
{
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
