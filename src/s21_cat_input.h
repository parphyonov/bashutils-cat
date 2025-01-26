#define _DEFAULT_SOURCE 1

#ifndef __S21_CAT_INPUT
#define __S21_CAT_INPUT

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "s21_cat_oset.h"

void collect_filenames_from_command_line_arguments(char **argv, size_t offset,
                                                   char **target_array);

size_t get_filenames_array_size(int argc, char **argv);

void get_option_set_from_argv1(const char *argv, struct OptionSet *options_set);

#endif