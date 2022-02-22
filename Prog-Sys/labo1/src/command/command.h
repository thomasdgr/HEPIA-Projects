#ifndef COMMAND_H
#define COMMAND_H

#define _GNU_SOURCE

#include "../jobs/jobs.h"

void apply_cd_command(char** array);
int apply_command(char** array);

#endif
