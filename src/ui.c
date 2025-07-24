#include <ncurses.h>
#include <string.h>
#include "../include/ui.h"
#include "../include/ins.h"

void ui_init()
{
	initscr(); noecho(); cbreak();
	keypad(stdscr, TRUE);
	curs_set(0);
}

void ui_cleanup()
{
	endwin();
}

void ui_draw_header()
{
	const char *title = " Inventory_Sysughh - Press 'a' to add, 'd' to delete, 's' for search, 'g' to generate reports, 'q' to quit ";
	int len = strlen(title);
	int x = (COLS - len) / 2; /* Center horizontally */

	/* Print the centered title at the top */
	mvprintw(0, x, "%s", title);
	/* Print the centerd horizontal line under the text */ 
	move(1, 0);
	hline('=', COLS);
}

void ui_draw_footer() 
{
	/* Draw horizontal line above the footer */
	move(LINES - 2, 0);
	hline('=', COLS);

	/* Print footer message on the last line, centered */
	const char *footer = " use arrows to navigate | Press 'q' to quit ";
	int len = strlen(footer);
	int x = (COLS - len) / 2;
	mvprintw(LINES - 1, x, "%s", footer);

	clrtoeol(); /* clear to end of line just in case */
}

void inventory_display_item(inventory *item, int y, int selected) 
{
    if (selected) attron(A_REVERSE);
    mvprintw(y, 2, "- %s | Qty: %d | Rs%.2f", item->name, item->quantity, item->price);
    if (selected) attroff(A_REVERSE);
}

void ui_main_loop()
{
	initscr();
	keypad(stdscr, TRUE);
	noecho();
	curs_set(FALSE);

	while (1) 
	{
		clear();
		ui_draw_header();

		for (int i = 0; i < (int)inventory.count; ++i) inventory_display_item(&inventory.items[i], 2 + i, i == selected);

		ui_draw_footer();
		refresh();

		ch = getch();
		if (ch == 'q') break;
		else if (ch == KEY_UP && selected > 0) selected--;
		else if (ch == KEY_DOWN && selected < (int)inventory.count - 1) selected++;
		else if (ch == 'a') 
		{
			echo();
			addItem(&inventory);
			noecho();
		}
		else if (ch == 'd' && inventory.count > 0) 
		{
			deleteItem(&inventory.items[selected]);
			for (size_t i = selected; i < inventory.count - 1; ++i) inventory.items[i] = inventory.items[i + 1];
			inventory.count--;
			if (selected >= (int)inventory.count) selected = inventory.count - 1;
	    	}
		else if (ch == 's')
		{
			echo();
			char query[256];
			mvprintw(LINES - 2, 0, "Search by name: ");
			getnstr(query, sizeof(query) - 1);
			noecho();

			for (char *p = query; *p; ++p) *p = tolower(*p);

			int found = -1;
			for (int i = 0; i < (int)inventory.count; ++i) 
			{
				char *copy = strdup(inventory.items[i].name);
				for (char *p = copy; *p; ++p) *p = tolower(*p);
				if (strcmp(copy, query) == 0) 
				{
					found = i;
					free(copy);
					break;
			    	}
			    	free(copy);
			}

			if (found != -1) selected = found;
			else 
			{
				mvprintw(LINES - 3, 0, "Item not found. Press any key...");
				getch();
			}
		}
		else if (ch == 'g')
		{
			clear();
			generateReports(&inventory);
			mvprintw(LINES - 2, 0, "Press any key to return...");
			getch();
	    	}
	}

	return 0;
}
