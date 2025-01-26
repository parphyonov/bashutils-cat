#ifndef __S21_CAT_OUTPUT
#define __S21_CAT_OUTPUT

#include <stdio.h>
#include <stdlib.h>

#include "s21_cat_logic.h"
#include "s21_cat_oset.h"

void print_character(int ch, struct OptionSet oset);

void print_files(char **filenames, size_t limit, struct OptionSet oset);

#endif