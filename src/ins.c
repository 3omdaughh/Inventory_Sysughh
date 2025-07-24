#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <time.h>
#include <ncurses.h>
#include <unistd.h>
#include "../include/ui.h"
#include "../include/ins.h"

int compareByName(const void *a, const void *b) 
{
	const inventory *item1 = (const inventory *)a;
	const inventory *item2 = (const inventory *)b;
	return strcasecmp(item1->name, item2->name);
}

void toLower(char *s) 
{
	for (; *s; ++s) *s = tolower(*s);
}

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

	printf("Price: ");
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

void deleteItem(vec *v)
{
	char buffer[256];
	printf("Enter item name: ");
	fgets(buffer, sizeof(buffer), stdin);
	buffer[strcspn(buffer, "\n")] = '\0'; 
	toLower(buffer);

	int exist = 0;

	for (size_t i = 0; i < v->count; i++)
	{
		char *itemNC = strdup(v->items[i].name);
		toLower(itemNC);

		if (strcmp(buffer, itemNC) == 0)
		{
			exist = 1;
			free(itemNC);

			int deleteQuan;
			printf("Enter Quantity to delete: ");
			scanf("%d", &deleteQuan);
			getchar();

			if (deleteQuan <= 0) printf("Invalid quantity. Please enter a positive value.\n");
			else if (deleteQuan > v->items[i].capacity) printf("Quantity to delete exceeds available quantity. Available: %d\n", v->items[i].capacity);
			else 
			{
				v->items[i].capacity -= deleteQuan;

				if (v->items[i].capacity == 0)
				{
					free(v->items[i].name);
					free(v->items[i].description);

					for (size_t j = 0; j < v->count-1; j++)
						v->items[j] = v->items[j+1];
					v->count--;

					clear();
					mvprintw(LINES / 2, (COLS - 30) / 2, "!Item deleted successfully!");
					refresh();
					
					napms(1500);

					clear();
					refresh();

					getch();
					endwin();
				}
				else printf("Remaining quantity: %d\n", v->items[i].quantity);
			}
			return;
		}
		free(itemNC);
	}

	if (!exist) printf("Item not found in the inventory.\n");
}


void searchItem(const vec *v) 
{
	if (v->count == 0) 
	{
		printf("Inventory is empty.\n");
		return;
	}

	char buffer[256];
	printf("Enter item name: ");
	fgets(buffer, sizeof(buffer), stdin);
	buffer[strcspn(buffer, "\n")] = '\0';

	for (char *p = buffer; *p; ++p) *p = tolower(*p);

	vec sorted = *v;
	qsort(sorted.items, sorted.count, sizeof(inventory), compareByName);

	inventory key;
	key.name = buffer;

	inventory *found = bsearch(&key, sorted.items, sorted.count, sizeof(inventory), compareByName);

	if (found) 
	{
		printf("\nName: %s\n", found->name);
		printf("Description: %s\n", found->description);
		printf("Category: %s\n", categoryName(found->category));
		printf("Date: %s\n", found->date);
		printf("Quantity: %d\n", found->quantity);
		printf("Price: Rs%.2f\n", found->price);
	}
	else printf("Item not found in the inventory.\n");
}

void generateReports(const vec *v) 
{
	printf("\n");

	printf("Report 1: List of all items in the inventory\n");
	for (size_t i = 0; i < v->count; ++i) 
	{
		inventory item = v->items[i];
		printf("Name: %s, Description: %s, Category: %s, Quantity: %d, Price: Rs%.2f\n",
			item.name,
			item.description,
			categoryName(item.category),
			item.quantity,
			item.price);
	}

	printf("\nReport 2: Total value of inventory\n");
	double totalValue = 0;
	for (size_t i = 0; i < v->count; ++i) totalValue += v->items[i].quantity * v->items[i].price;
	printf("Total value of inventory: Rs%.2f\n\n", totalValue);
}
