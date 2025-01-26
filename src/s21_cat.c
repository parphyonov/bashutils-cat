#include <stdio.h>
#include <stdlib.h>

#include "s21_cat_input.h"
#include "s21_cat_logic.h"
#include "s21_cat_oset.h"
#include "s21_cat_output.h"

int main(int argc, char **argv) {
  // sets offset for filenames collection from command line
  size_t filenames_collector_offset = 1;

  // sets options based on option string value
  struct OptionSet options_set;
  init_all_option_set_to_false(&options_set);
  if (argc >= 3 && argv[1][0] == '-') {
    get_option_set_from_argv1(argv[1], &options_set);
    filenames_collector_offset = 2;
  }

  // error message if wrong option / set of options were provided
  if (options_set.all_failed) {
    printf("s21_cat: illegal option -- %s\n", argv[1]);
    printf("standard usage: s21_cat [-benst] [file ...]\n");
    printf("GNU flags usage: s21_cat [--number-nonblank / -E / --number / "
           "--squeeze-blank / -T] [file ...]\n");
  } else {
    // sets max FILENAMES array size
    const size_t filenames_array_size = get_filenames_array_size(argc, argv);

    // init FILENAMES array
    if (filenames_array_size > 0) {
      // init FILENAMES array
      char **filenames = init_filenames_array(filenames_array_size);
      if (filenames != NULL) {
        // populates FILENAMES array with filenames
        collect_filenames_from_command_line_arguments(
            argv, filenames_collector_offset, filenames);
        // prints these files if they exist, otherwise error message per each
        // missing file
        print_files(filenames, filenames_array_size, options_set);
        // frees dynamically created FILENAMES array
        free_all(filenames, filenames_array_size);
      } else {
        // FILENAMES array init failure
        printf("s21_cat: Failed to initiate filenames array\n");
      }
    } else {
      // NO OPTIONS OR FILES error message
      printf("s21_cat: No options or files were provided\n");
    }
  }
  return 0;
}
