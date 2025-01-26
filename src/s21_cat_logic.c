#include "s21_cat_logic.h"

void free_all(char **filenames, size_t limiter) {
  for (size_t i = 0; i < limiter; i++)
    free(filenames[i]);
  free(filenames);
}

char **init_filenames_array(size_t filenames_array_size) {
  char **filenames_array;
  filenames_array = (char **)malloc(filenames_array_size * sizeof(char *));
  if (filenames_array != NULL)
    for (size_t i = 0; i < filenames_array_size; i++) {
      filenames_array[i] = (char *)malloc(256 * sizeof(char));
      if (filenames_array[i] == NULL) {
        printf("s21_cat: failed to initiate filenames[%zu]\n", i);
        exit(1);
      }
    }
  return filenames_array;
}

bool read_file(const char *filename, struct OptionSet options_set,
               size_t *line_num, size_t limiter, size_t counter, size_t *lfn) {
  bool is_read = false;
  FILE *file = fopen(filename, "r");
  if (file != NULL) {
    char line[256];
    if (*lfn != counter && *lfn > 0)
      *line_num = *line_num - 1;
    // prints line by line
    while (fgets(line, sizeof(line), file)) {
      // printf("LIMITER >>> %zu | COUNTER >>> %zu\n", limiter, counter);
      // skips if --squeeze_blank or -s is set
      if (options_set.this_line_empty && strcmp(line, "\n") == 0 &&
          options_set.squeeze_blank) {
        continue;
      }
      // checks to see if the current line is empty, required by
      // --squeeze-blank/-s above
      if (strcmp(line, "\n") == 0)
        options_set.this_line_empty = true;
      else
        options_set.this_line_empty = false;
      // prints non-blank line numbers only
      if (options_set.number_nonblank && strcmp(line, "\n") != 0) {
        if (!(limiter > 1 && counter > 0 && *lfn != counter)) {
          printf("%6zu\t", *line_num);
          *line_num = *line_num + 1;
        }
        if (*lfn != counter)
          *lfn = *lfn + 1;
      } else if (options_set.number) {
        // prints all line numbers
        if (!(limiter > 1 && counter > 0 && *lfn != counter)) {
          printf("%6zu\t", *line_num);
          *line_num = *line_num + 1;
        }
        if (*lfn != counter)
          *lfn = *lfn + 1;
      }
      for (size_t c = 0; c < strlen(line); c++) {
        print_character(line[c], options_set);
      }
    }
    is_read = true;
    fclose(file);
  } else {
    printf("s21_cat: %s: No such file or directory\n", filename);
  }
  return is_read;
}