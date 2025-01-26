#ifndef __S21_CAT_OSET
#define __S21_CAT_OSET

#include <stdbool.h>

struct OptionSet {
  bool number_nonblank;
  bool show_ends;
  bool number;
  bool squeeze_blank;
  bool show_tabs;
  bool show_npc;
  bool all_failed;
  bool this_line_empty;
};

void init_all_option_set_to_false(struct OptionSet *options_set);

#endif