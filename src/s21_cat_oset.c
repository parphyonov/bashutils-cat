#include "s21_cat_oset.h"

void init_all_option_set_to_false(struct OptionSet *options_set) {
  options_set->number = false;
  options_set->number_nonblank = false;
  options_set->show_ends = false;
  options_set->show_npc = false;
  options_set->show_tabs = false;
  options_set->squeeze_blank = false;
  options_set->all_failed = false;
  options_set->this_line_empty = false;
}
