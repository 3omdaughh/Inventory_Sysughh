#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ncurses.h>
#include <unistd.h>
#include "../include/ui.h"
#include "../include/ins.h"

void addItem(vec *v)
{
	inventory newItem;
	char buffer[256];

	printf("Enter Item Details:\n");

	printf("Name : ");
	fgets(buffer, sizeof(buffer), stdin);
	buffer[strcspn(buffer, '\n')] = '\0';
	newItem.name = strdup(buffer);

	printf("Category (1-6): ");
	scanf("%d", &newItem.category);
	getchar();

	printf("Price : ");
	scanf("%f", &newItem.price);
	getchar();

	time_t currentTime = time(NULL);
	struct tm *localTime = localtime(&currentTime);
	strftime(newItem.date, sizeof(newItem.date), "%d-%m-%Y", localTime);

	da_append(v, newItem);
	
	/* ---------------------------------------------------  */

	clear();
	mvprintw(LINES / 2, (COLS - 30) / 2, "!Item added successfully!");
	refresh();
	
	napms(1500);

	clear();
	refresh();

	getch();
	endwin();        
}
