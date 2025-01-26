#ifndef __S21_CAT_LOGIC
#define __S21_CAT_LOGIC

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "s21_cat_oset.h"
#include "s21_cat_output.h"

void free_all(char **filenames, size_t limiter);

char **init_filenames_array(size_t filenames_array_size);

bool read_file(const char *filenames, struct OptionSet options_set,
               size_t *line_num, size_t limiter, size_t counter, size_t *lfn);

#endif