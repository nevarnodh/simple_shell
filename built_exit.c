#include <stdio.h>
#include <stdlib.h>

/**
 * void exit_shell(int status):A custom function that exits the program with the specified exit status
 * int main(int argc, char **argv):The main function of the program.
 * Returns: 0 upon successful execution
 */

void exit_shell(int status)
{
exit(status);
}
int main(int argc, char **argv)
{
if (argc == 2)
{
int status = atoi(argv[1]);
exit_shell(status);
}
else
{
printf("Usage: exit status\n");
}
return 0;
}


