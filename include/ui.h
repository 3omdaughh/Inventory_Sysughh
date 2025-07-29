#ifndef UI_H
#define UI_H

#include "inventory.h"

void init_ui();
void cleanup_ui();
void display_menu();
int get_menu_choice();
void get_item_input(Inventory* item);
void get_delete_input(char* name, int* quantity);
void get_search_input(char* name);

#endif
