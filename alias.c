#include "shell.h"

/**
 * int is_alias_command-check if the command is an alias command
 * execute_alias_command-handle the alias command
 * Return 0
 */

int is_alias_command(char *command)
{
return strcmp(command, "alias") == 0;
}

int execute_alias_command(char **arguments)
if (arguments[1] == NULL)
{
// Print all aliases, one per line
// Iterate over the alias data structure and print each alias
return 0;
}
for (int i = 1; arguments[i] != NULL; i++)
{
char *alias = arguments[i];
char *equal_sign = strchr(alias, '=');
if (equal_sign != NULL)
{
*equal_sign = '\0';
char *name = alias;
char *value = equal_sign + 1;
// Add or replace the alias in the data structure
continue;
}
// Print the value of the specified alias
}
return 0;
}
if (is_alias_command(arguments[0]))
execute_alias_command(arguments);
}
else if (is_exit_command(arguments[0]))
{
int exit_status = execute_exit_command(arguments);
exit(exit_status);
}
