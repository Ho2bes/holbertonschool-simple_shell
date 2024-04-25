![**Conquest of the Shell**](https://github.com/Ho2bes/boom/blob/main/shell%20conquest.jpg)
# C - Simple Shell

We have create a simple UNIX command interpreter in C programming language.

## Introduction
**A shell ?**

Shell serves as a command-line interpreter, acting as the bridge between users and the operating system's services. It offers a means for users to interact with the system, with different types of shells available. For instance, the Bourne Shell (sh) is commonly used.

**For what ?**

Its main function lies in interpreting commands, facilitating tasks like process management, input/output manipulation, file operations, security measures, communication, and scripting capabilities. These functionalities enable users to execute commands, automate tasks through batch programs or scripts, and manage system resources efficiently. Across Unix-like systems, at least one Bourne shell interpreter is present, typically located at /bin/sh in the Unix file structure.
## Technologies used

The printf function was coded on an Ubuntu 22.04 LTS machine with gcc version 4.8.4.

VIM was used to write the code.


## Project overview
### Compilation

All files will be compiled with :
````
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh
````

Betty coding style:
All files are written in C and follows the Betty coding style for Holberton School.

### Authorized functions and macros

- all functions from string.h
- access
- chdir
- close
- closedir
- execve
- exit
- _exit
- fflush
- fork
- free
- getcwd
- getline
- getpid
- isatty
- kill
- malloc
- open
- opendir
- perror
- printf
- fprintf
- vfprintf
- sprintf
- putchar
- read
- readdir
- signal
- stat
- lstat
- fstat
- strtok
- wait
- waitpid
- wait3
- wait4
- write

### Files and functions description

#### **custom_strtok_r**

The custom_strtok_r function tokenizes a string into tokens using a specified delimiter.

***Return***

It returns a pointer to the tokenized token.

____

#### **find_command_path**

The find_command_path function searches for the full path of a specified command by traversing the directories listed in the PATH environment variable.

***Return***

It returns a string containing the full path of the command if found, otherwise it returns NULL.
___
#### **getenv_var**

The getenv_var function retrieves the value of a specified environment variable.

***Return***

It returns a pointer to the value of the environment variable if found, otherwise it returns NULL.
___
#### **tokenize_command**

The tokenize_command function splits a command string into a series of tokens, using a space as a delimiter.

***Return***

It returns an array of strings representing the split tokens.
___
#### **execute_command**

The execute_command function executes a given command by creating a child process using fork() and using execve() to execute the command.

***Return***

This function does not return anything.
## Exemples

**Interactive Execution**
````
$ ./shell
$ ls -l
````
**Non-Interactive Execution (with pipe)**
````
$ echo "ls -l" | ./shell
````
**Manual Page**

To view the manual page for Shell, run the following command:
````
$ man ./shell.1
````
**Memory Leak Checking**

To check for memory leaks, you can use the valgrind tool. Run the program with valgrind to detect any potential memory leaks:
````
$ valgrind ./shell
````

![**Flowchart of our code**](https://github.com/Ho2bes/boom/blob/main/Shell%20Flowchart.jpeg)

## Bugs
There are no known bugs so far. Do not hesitate to send us any suggestions or problems encountered when using our shell.
## 🚀 About Us
**M. CORNABAS and N. BRAULT DOMINGO** are two students at Holberton School, the best school in the world.


## Credits
Contributors :
M. CORNABAS and N. BRAULT DOMINGO

**Thanks you to Houssem, Axel, all the staff who inspired us for this project. Special thanks to K.P for his help, always in our heart**![**Conquest of the Shell**](https://github.com/Ho2bes/boom/blob/main/shell%20conquest.jpg)
# C - Simple Shell

We have create a simple UNIX command interpreter in C programming language.
## Introduction
**A shell ?**

Shell serves as a command-line interpreter, acting as the bridge between users and the operating system's services. It offers a means for users to interact with the system, with different types of shells available. For instance, the Bourne Shell (sh) is commonly used.

**For what ?**

Its main function lies in interpreting commands, facilitating tasks like process management, input/output manipulation, file operations, security measures, communication, and scripting capabilities. These functionalities enable users to execute commands, automate tasks through batch programs or scripts, and manage system resources efficiently. Across Unix-like systems, at least one Bourne shell interpreter is present, typically located at /bin/sh in the Unix file structure.
## Technologies used

The printf function was coded on an Ubuntu 22.04 LTS machine with gcc version 4.8.4.

VIM was used to write the code.


## Project overview
### Compilation

All files will be compiled with :
````
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh
````

Betty coding style:
All files are written in C and follows the Betty coding style for Holberton School.

### Authorized functions and macros

- all functions from string.h
- access
- chdir
- close
- closedir
- execve
- exit
- _exit
- fflush
- fork
- free
- getcwd
- getline
- getpid
- isatty
- kill
- malloc
- open
- opendir
- perror
- printf
- fprintf
- vfprintf
- sprintf
- putchar
- read
- readdir
- signal
- stat
- lstat
- fstat
- strtok
- wait
- waitpid
- wait3
- wait4
- write

### Files and functions description

#### **custom_strtok_r**

The custom_strtok_r function tokenizes a string into tokens using a specified delimiter.

***Return***

It returns a pointer to the tokenized token.

____

#### **find_command_path**

The find_command_path function searches for the full path of a specified command by traversing the directories listed in the PATH environment variable.

***Return***

It returns a string containing the full path of the command if found, otherwise it returns NULL.
___
#### **getenv_var**

The getenv_var function retrieves the value of a specified environment variable.

***Return***

It returns a pointer to the value of the environment variable if found, otherwise it returns NULL.
___
#### **tokenize_command**

The tokenize_command function splits a command string into a series of tokens, using a space as a delimiter.

***Return***

It returns an array of strings representing the split tokens.
___
#### **execute_command**

The execute_command function executes a given command by creating a child process using fork() and using execve() to execute the command.

***Return***

This function does not return anything.
## Exemples

**Interactive Execution**
````
$ ./shell
$ ls -l
````
**Non-Interactive Execution (with pipe)**
````
$ echo "ls -l" | ./shell
````
**Manual Page**

To view the manual page for Shell, run the following command:
````
$ man ./shell.1
````
**Memory Leak Checking**

To check for memory leaks, you can use the valgrind tool. Run the program with valgrind to detect any potential memory leaks:
````
$ valgrind ./shell
````

![**Flowchart of our code**](https://github.com/Ho2bes/boom/blob/main/Shell%20Flowchart.jpeg)

## Bugs
There are no known bugs so far. Do not hesitate to send us any suggestions or problems encountered when using our shell.
## 🚀 About Us
**M. CORNABAS and N. BRAULT DOMINGO** are two students at Holberton School, the best school in the world.


## Credits
Contributors :
M. CORNABAS and N. BRAULT DOMINGO

**Thanks you to Houssem, Axel, all the staff who inspired us for this project. Special thanks to K.P for his help, always in our heart**
