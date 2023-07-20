#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_BUFFER_SIZE 1024

/**
 * char *get_line():Reads a line of input from the user.
 * Returns: A dynamically allocated character array containing the input line, or NULL on error or end-of-file
 * int main():The main loop of the simple shell
 */

char *get_line();

int main()
{
char *command;
while (1)
{
printf("> ");
fflush(stdout);
command = get_line();
if (command != NULL)
{
free(command);
}
else
{
break;
}
}
return 0;
}
char *get_line()
{
static char buffer[MAX_BUFFER_SIZE];
static size_t buffer_position = 0;
static ssize_t bytes_read = 0;
char *line = NULL;
size_t line_length = 0;
while (1)
{
if (buffer_position >= bytes_read)
{
bytes_read = read(STDIN_FILENO, buffer, sizeof(buffer));
if (bytes_read <= 0)
{
// Error or end-of-file condition
return NULL;
}
buffer_position = 0;
}
if (buffer[buffer_position] == '\n')
{
// End of line reached
buffer_position++;
break;
}
line = realloc(line, line_length + 1);
line[line_length++] = buffer[buffer_position++];
}
if (line != NULL)
line = realloc(line, line_length + 1);
line[line_length] = '\0';
}
return line;
}

