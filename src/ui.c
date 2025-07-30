#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include "ui.h"

void init_ui() 
{
	initscr();
	cbreak();
	noecho();
	keypad(stdscr, TRUE);
}

void cleanup_ui() 
{
	endwin();
}

void display_menu() 
{
	clear();
	const char *title = "Inventory_Sysughh";
	int len = strlen(title);
	int x = (COLS - len) / 2;

	mvprintw(0, x, "%s", title);
	move(1, 0);
	hline('=', COLS);

	mvprintw(3, x, "1. Add New Item");
	mvprintw(4, x, "2. Delete Item");
	mvprintw(5, x, "3. Search Item");
	mvprintw(6, x, "4. Generate Reports");
	mvprintw(7, x, "5. Exit");
	mvprintw(8, x, "Enter Your Choice: ");

	move(LINES - 2, 0);
	hline('=', COLS);
	refresh();
}

int get_menu_choice() 
{
	char input[10];
	echo();
	getstr(input);
	noecho();
	return atoi(input);
}

void get_item_input(Inventory* item) 
{
	clear();

	const char *title = "Inventory_Sysughh";
	int len = strlen(title);
	int x = (COLS - len) / 2;

	mvprintw(0, x, "%s", title);
	move(1, 0);
	hline('=', COLS);

	move(LINES - 2, 0);
	hline('=', COLS);

	mvprintw(3, x, "Enter item details:");
	mvprintw(4, x, "Name: ");
	echo();
	getstr(item->name);
	mvprintw(5, x, "Description: ");
	getstr(item->description);
	mvprintw(6, x, "Category (1-6): ");
	char cat[10];
	getstr(cat);
	item->category = atoi(cat);
	mvprintw(7, x, "Quantity: ");
	char qty[10];
	getstr(qty);
	item->quantity = atoi(qty);
	mvprintw(8, x, "Price: ");
	char price[10];
	getstr(price);
	item->price = atof(price);
	noecho();
}

void get_delete_input(char* name, int* quantity) 
{
	clear();

	const char *title = "Inventory_Sysughh";
	int len = strlen(title);
	int x = (COLS - len) / 2;

	mvprintw(0, x, "%s", title);
	move(1, 0);
	hline('=', COLS);

	move(LINES - 2, 0);
	hline('=', COLS);

	mvprintw(3, x, "Enter item name: ");
	echo();
	getstr(name);
	mvprintw(4, x, "Enter Quantity to delete: ");
	char qty[10];
	getstr(qty);
	*quantity = atoi(qty);
	noecho();
}

void get_search_input(char* name) 
{
	clear();

	const char *title = "Inventory_Sysughh";
	int len = strlen(title);
	int x = (COLS - len) / 2;

	mvprintw(0, x, "%s", title);
	move(1, 0);
	hline('=', COLS);

	move(LINES - 2, 0);
	hline('=', COLS);

	mvprintw(3, x, "Enter item name: ");
	echo();
	getstr(name);
	noecho();
}
