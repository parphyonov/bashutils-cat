#include "s21_cat_input.h"

void collect_filenames_from_command_line_arguments(char **argv, size_t offset,
                                                   char **target_array) {
  size_t subtractor = 1;
  if (argv[1][0] == '-')
    subtractor = 2;
  while (argv[offset] != NULL) {
    strcpy(target_array[offset - subtractor], argv[offset]);
    offset++;
  }
}

size_t get_filenames_array_size(int argc, char **argv) {
  size_t result = 0;
  if (argc >= 3) {
    if (argv[1][0] == '-') {
      result = argc - 2;
    } else {
      result = argc - 1;
    }
  } else if (argc == 2 && argv[1][0] != '-') {
    result = 1;
  }
  return result;
}

void get_option_set_from_argv1(const char *argv1,
                               struct OptionSet *options_set) {
  // options arg
  char option_string[256] = "\0";
  strcpy(option_string, argv1);
  // first, we address GNU flags, as they are not parsed
  if (strcmp(option_string, "--number-nonblank") == 0 ||
      strcmp(option_string, "-E") == 0 ||
      strcmp(option_string, "--number") == 0 ||
      strcmp(option_string, "--squeeze-blank") == 0 ||
      strcmp(option_string, "-T") == 0) {
    if (strcmp(option_string, "--number-nonblank") == 0) {
      options_set->number_nonblank = true;
    } else if (strcmp(option_string, "-E") == 0) {
      options_set->show_ends = true;
    } else if (strcmp(option_string, "--number") == 0) {
      options_set->number = true;
    } else if (strcmp(option_string, "--squeeze-blank") == 0) {
      options_set->squeeze_blank = true;
    } else if (strcmp(option_string, "-T") == 0) {
      options_set->show_tabs = true;
    }
  } else if (strlen(option_string) > 1 && option_string[0] == '-') {
    // then we parse non-GNU flags, they are parsed and can be passed more than
    // one in a string like -benst
    for (size_t i = 1; i < strlen(option_string); i++) {
      if (option_string[i] == 'b' || option_string[i] == 'e' ||
          option_string[i] == 'n' || option_string[i] == 's' ||
          option_string[i] == 't') {
        if (strchr(option_string, 'b')) {
          options_set->number_nonblank = true;
          options_set->number = false;
        } else if (strchr(option_string, 'n')) {
          options_set->number = true;
          options_set->number_nonblank = false;
        }
        if (strchr(option_string, 's'))
          options_set->squeeze_blank = true;
        if (strchr(option_string, 'e')) {
          options_set->show_ends = true;
          options_set->show_npc = true;
        }
        if (strchr(option_string, 't')) {
          options_set->show_npc = true;
        }
      } else {
        options_set->all_failed = true;
        break;
      }
    }
  } else {
    // parsing failed and we pass it up for correct handling in the program
    options_set->all_failed = true;
  }
}