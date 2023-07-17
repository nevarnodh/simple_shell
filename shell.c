#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_COMMAND_LENGTH 100

void display_prompt() {
printf("simple_shell$ ");
fflush(stdout);
}
int main()
{
char command[MAX_COMMAND_LENGTH];
while (1)
{
display_prompt();
if (fgets(command, sizeof(command), stdin) == NULL) {
// End of file condition (Ctrl+D)
break;
}
// Remove the trailing newline character
command[strcspn(command, "\n")] = '\0';
// Fork a child process
pid_t pid = fork();
if
(pid == -1)
{
// Forking failed
perror("Fork failed");
exit(EXIT_FAILURE);
}
else if (pid == 0)
{
 // Child process
// Execute the command using execve
char *argv[] = {command, NULL};
if (execve(command, argv, environ) == -1)
{
// Execution failed
perror("Command execution failed");
exit(EXIT_FAILURE);
}
}
else
{
// Parent process
int status;
if (wait(&status) == -1) {
perror("Error waiting for child process");
exit(EXIT_FAILURE);
}
}
}
return 0;
}

