#include <ncurses.h>
#include <string.h>
#include "../include/ui.h"

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
	const char *title = " Inventory_Sysughh - Press 'a' to add, 'd' to delete, 'q' to quit ";
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

void ui_main_loop()
{
	/* --- */
}
