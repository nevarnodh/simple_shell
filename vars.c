#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/**
 * char *replace_variables(char *command, int exit_status)-replace variables in a command
 * Return: modified command;
 */
char *replace_variables(char *command, int exit_status)
{
int command_length = strlen(command);
char *modified_command = malloc((command_length + 1) * sizeof(char));
if (modified_command == NULL)
{
perror("malloc error");
exit(EXIT_FAILURE);
}
strcpy(modified_command, command);
char *question_mark = strstr(modified_command, "$?");
if (question_mark != NULL)
{
char exit_status_str[10];
snprintf(exit_status_str, sizeof(exit_status_str), "%d", exit_status);
modified_command = str_replace(modified_command, "$?", exit_status_str);
}
char *dollar_sign = strstr(modified_command, "$$");
if (dollar_sign != NULL)
{
pid_t process_id = getpid();
char process_id_str[10];
snprintf(process_id_str, sizeof(process_id_str), "%d", process_id);
modified_command = str_replace(modified_command, "$$", process_id_str);
}
return modified_command;
}
/**
 * char *str_replace-replace occurrences of a substring in a string
 * Return: modified string
 */
char *str_replace(const char *string, const char *substring, const char *replacement)
{
int string_length = strlen(string);
int substring_length = strlen(substring);
int replacement_length = strlen(replacement);
int modified_string_length = string_length + (replacement_length - substring_length) + 1;
char *modified_string = malloc(modified_string_length * sizeof(char));
if (modified_string == NULL)
{
perror("malloc error");
exit(EXIT_FAILURE);
}

const char *position = string;
char *insertion_point = modified_string;
while (1)
{
const char *occurrence = strstr(position, substring);
if (occurrence == NULL)
{
strcpy(insertion_point, position);
break;
}
strncpy(insertion_point, position, occurrence - position);
insertion_point += occurrence - position;
strcpy(insertion_point, replacement);
insertion_point += replacement_length;
position = occurrence + substring_length;
}
return modified_string;
}

char *modified_command = replace_variables(command, exit_status);
execute_command(modified_command);
free(modified_command);

