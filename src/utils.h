#ifndef UTILS_H
#define UTILS_H

#include "player.h"
#include "time.h"

#define md 10    // max_id
#define MAX_NAME_LEN 64
#define shedule 13

enum InputResult {
    INPUT_INVALID = -1,
    INPUT_END = -2
};

int input_check(void);
int input_inventory_check(void);
void print_inventory(void);
void up_item(void);
void null_slot(void);
void print_find_the_greatest(void);
void find_id_by_name(void);
void diary(Player *player, Time *time);
void check_village(Time *time);
void load_items(void);
void load_input(void);
#endif
