# 42-get_next_line

![42-get_next_line](https://socialify.git.ci/julienhouyet/42-get_next_line/image?logo=https%3A%2F%2Fgithub.com%2Fayogun%2F42-project-badges%2Fraw%2Fmain%2Fbadges%2Fget_next_linem.png&name=1&owner=1&pattern=Circuit%20Board&theme=Auto)

# Introduction

The aim of this project is to make a function that returns a line ending with a newline, read from a file descriptor.

At [42 School](https://github.com/42School), almost every project must be written in accordance to the [Norm](https://github.com/42School/norminette/blob/master/pdf/en.norm.pdf), the school's coding standard. As a result, the implementation of certain parts may appear strange and for sure had room for improvement.

## :zap: Usage

To use this library, import the "get_next_line.h" header into your files.

```c
#include "get_next_line.h"
```

Compile your file with "get_next_line.c" and "get_next_line_utils.c". 

You can edit the BUFFER_SIZE with -D BUFFER_SIZE=number.

Exemple :

```shell
gcc your_file.c get_next_line.c get_next_line_utils.c -D BUFFER_SIZE=100 && ./a.out
```

###  :electric_plug: Installation

To install the project, clone this repository :

```shell
$ git@github.com:julienhouyet/42-get_next_line.git
```

##  :page_facing_up: Function in the library
 
✅ get_next_line
```c
char *get_next_line(int fd);
```
```
Returns a line read from a file descriptor.
```

##  :lock: License

GNU GENERAL PUBLIC LICENSE
Version 3.
