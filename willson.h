#ifndef WILLSON_H
#define WILLSON_H
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#define PATH_MAX 1024
char *getenv_var(const char *var_name, char **env);
char *find_command_path(const char *command, char **env);
char **tokenize_command(char *command);
int execute_command(char *command, char **env);
char *custom_strtok_r(char *command, const char *delim, char **array_str);
#endif
