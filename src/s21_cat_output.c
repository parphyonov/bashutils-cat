#include "s21_cat_output.h"

void print_character(int character, struct OptionSet options_set) {
  // print non-printing characters (-v implied)
  if (options_set.show_npc) {
    if (character < 32 || character > 126) {
      if (character == '\n')
        if (options_set.number_nonblank && options_set.this_line_empty)
          printf("        $\n");
        else {
          if (options_set.show_ends)
            printf("$\n");
          else
            printf("\n");
        }
      else if (character == '\t')
        printf("^I");
      else {
        // M-Notation here
        if (character == 127)
          printf("^?");
        else {
          printf("M-");
          printf("%c", (character >> 6) | 0xC0);
          printf("M-%c", (character & 0x3F) | 0x80);
        }
      }
    } else
      printf("%c", character);
  } else {
    // -v not implied
    if (character == '\n') {
      // prints $ in the end of the line if -E is set
      if (options_set.show_ends)
        printf("$");
      printf("\n");
    } else if (character == '\t' && options_set.show_tabs) {
      // prints ^I instead of tabs if -T is set
      printf("^I");
    } else {
      printf("%c", character);
    }
  }
}

void print_files(char **filenames, size_t limiter,
                 struct OptionSet options_set) {
  size_t line_num = 1;
  size_t last_file_num = 0;
  for (size_t fn = 0; fn < limiter; fn++)
    read_file(filenames[fn], options_set, &line_num, limiter, fn,
              &last_file_num);
}
