#ifndef COLOR_H
#define COLOR_H

#define _GNU_SOURCE

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <errno.h>
#include <unistd.h> 
#include <sched.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <limits.h>
#include <signal.h>
#include <dirent.h>
#include <sys/stat.h>
#include <time.h>
#include <fcntl.h>
#include <ucontext.h>

void black();
void red();
void green();
void yellow();
void blue();
void purple();
void cyan();
void white();
void reset();

#endif
