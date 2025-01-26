#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "../common/common.h"

#define CAT_OUT "cat_grounds/cat_out.txt"
#define S21_CAT_OUT "cat_grounds/s21_cat_out.txt"

void make_cat_command(char* dest, const char* opt, const char* files,
                      bool s21) {
  if (s21) {
    sprintf(dest, "../cat/s21_cat %s %s > %s", opt != NULL ? opt : "",
            files != NULL ? files : "", S21_CAT_OUT);
  } else {
    sprintf(dest, "cat %s %s > %s", opt != NULL ? opt : "",
            files != NULL ? files : "", CAT_OUT);
  }
}

int perform_cmp(const char* opt, const char* files) {
  char cat_command[STR_MAX] = "\0";
  char s21_cat_command[STR_MAX] = "\0";

  make_cat_command(cat_command, opt, files, false);
  make_cat_command(s21_cat_command, opt, files, true);

  system(cat_command);
  system(s21_cat_command);

  printf("TEST CASE >>>\n");
  printf("--            %s\n", cat_command);
  printf("-- %s\n", s21_cat_command);

  char s21_cat_valgrind[LINE_MAX] = "\0";
  sprintf(s21_cat_valgrind, "valgrind -q %s", s21_cat_command);
  system(s21_cat_valgrind);

  printf("RESULT: the outputs are ... ");
  int result = compare_files(CAT_OUT, S21_CAT_OUT, false);

  if (result == 0)
    printf("\033[1m\033[32mIDENTICAL\033[0m\n");
  else {
    printf("\033[1m\033[31mNOT IDENTICAL\033[0m\n");
    compare_files(CAT_OUT, S21_CAT_OUT, true);
  }
  printf("\n");

  return result;
}

int main(void) {
  delete_files(CAT_OUT, S21_CAT_OUT);
  create_files(CAT_OUT, S21_CAT_OUT);

  int result = 0;

  const char* path1 = "../lib/wonderwall.txt";
  const char* path2 = "../lib/wonderwall.txt ../lib/universal.txt";

  result = result || perform_cmp(NULL, path1);                 // test 1
  result = result || perform_cmp(NULL, path2);                 // test 2
  result = result || perform_cmp("-b", path1);                 // test 3
  result = result || perform_cmp("-b", path2);                 // test 4
  result = result || perform_cmp("--number-nonblank", path1);  // test 5
  result = result || perform_cmp("--number-nonblank", path2);  // test 6
  result = result || perform_cmp("-e", path1);                 // test 7
  result = result || perform_cmp("-e", path2);                 // test 8
  result = result || perform_cmp("-E", path1);                 // test 9
  result = result || perform_cmp("-E", path2);                 // test 10
  result = result || perform_cmp("-n", path1);                 // test 11
  result = result || perform_cmp("-n", path2);                 // test 12
  result = result || perform_cmp("--number", path1);           // test 13
  result = result || perform_cmp("--number", path2);           // test 14
  result = result || perform_cmp("-s", path1);                 // test 15
  result = result || perform_cmp("-s", path2);                 // test 16
  result = result || perform_cmp("--squeeze_blank", path1);    // test 17
  result = result || perform_cmp("--squeeze_blank", path2);    // test 18
  result = result || perform_cmp("-t", path1);                 // test 19
  result = result || perform_cmp("-t", path2);                 // test 20
  result = result || perform_cmp("-T", path1);                 // test 21
  result = result || perform_cmp("-T", path2);                 // test 22

  delete_files(CAT_OUT, S21_CAT_OUT);

  if (result == 0)
    printf("All tests SUCCESSFULLY passed!");
  else
    printf("Some of the tests FAILED");
  printf("\n\n");
  return result;
}