#ifndef WILLSON_H
#define WILLSON_H
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <signal.h>
#include <stdbool.h>
#include <linux/limits.h>
#include <pwd.h>
#include <sys/types.h>
#include <errno.h>
#include <sys/stat.h>
#include <limits.h>

char *getenv_var(const char *var_name, char **env);
char *find_command_path(const char *command);
char **tokenize_command(char *command);
void execute_command(char *command, char **env);
#endif
