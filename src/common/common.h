#ifndef __S21_CAT_GREP_COMMON
#define __S21_CAT_GREP_COMMON

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define STR_MAX 256
#define LINE_MAX 1024

void create_files(char* fn1, char* fn2);
void delete_files(char* fn1, char* fn2);

int compare_files(char* fn1, char* fn2, bool debug);

#endif