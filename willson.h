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
/*void custom_getline(char **lineptr, size_t *bufsize, int *status);*/
int custom_strcmp(const char *str1, const char *str2);
void cmd_path(char **argv);
#endif
