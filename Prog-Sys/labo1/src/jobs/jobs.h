#ifndef JOBS_H
#define JOBS_H

#define _GNU_SOURCE

#include "../tools/tools.h"

void apply_job(char** array);
void apply_2_jobs(char** array);
void apply_background_job(char** array);

void handler(int sig, siginfo_t* siginfo, void* context);

#endif
