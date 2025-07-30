#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <ncurses.h>
#include "inventory.h"
#include "ui.h" 

const char* categories(int choice) 
{
	switch (choice) 
	{
		case 1: return "Electronics";
		case 2: return "Clothing";
		case 3: return "Furniture";
		case 4: return "Appliances";
		case 5: return "Sports & Outdoor";
		case 6: return "Toys & Games";
		default: return "Invalid Item";
	}
}

void init_inventory(InventoryList* list) 
{
	list->capacity = MAX_ITEMS;
	list->size = 0;
	list->items = (Inventory*)malloc(list->capacity * sizeof(Inventory));
	if (!list->items) 
	{
		printw("Memory allocation failed!\n");
		refresh();
		getch();
		exit(1);
	}
}

void free_inventory(InventoryList* list) 
{
	free(list->items);
	list->items = NULL;
	list->size = 0;
	list->capacity = 0;
}

void add_item(InventoryList* list) 
{
	if (list->size >= list->capacity) 
	{
		clear();
		mvprintw(0, 0, "Inventory is full! Cannot add more items.");
		refresh();
		getch();
		return;
	}

	Inventory newItem;
	get_item_input(&newItem); 

	time_t currentTime = time(NULL);
	strftime(newItem.date, sizeof(newItem.date), "%d-%m-%Y", localtime(&currentTime));

	list->items[list->size] = newItem;
	list->size++;

	clear();
	mvprintw(0, 0, "Item added successfully!");
	refresh();
	getch();
}

void delete_item(InventoryList* list) 
{
	char name[MAX_NAME];
	int deleteQuantity;
	get_delete_input(name, &deleteQuantity); 

	char nameLower[MAX_NAME];
	strcpy(nameLower, name);
	for (int i = 0; nameLower[i]; i++) nameLower[i] = tolower(nameLower[i]);

	int found = 0;
	for (int i = 0; i < list->size; i++) 
	{
		char itemNameLower[MAX_NAME];
		strcpy(itemNameLower, list->items[i].name);
		for (int j = 0; itemNameLower[j]; j++) itemNameLower[j] = tolower(itemNameLower[j]);

		if (strcmp(nameLower, itemNameLower) == 0) 
		{
			found = 1;
			if (deleteQuantity <= 0) 
			{
				clear();
				mvprintw(0, 0, "Invalid quantity. Please enter a positive value.");
			}
			else if (deleteQuantity > list->items[i].quantity) 
			{
				clear();
				mvprintw(0, 0, "Quantity to delete exceeds available quantity: %d", list->items[i].quantity);
			}
			else
			{
				list->items[i].quantity -= deleteQuantity;
				if (list->items[i].quantity == 0) 
				{
					for (int j = i; j < list->size - 1; j++) list->items[j] = list->items[j + 1];
					list->size--;
					clear();
					mvprintw(0, 0, "Item deleted successfully.");
				} 
				else
				{
					clear();
					mvprintw(0, 0, "Remaining quantity: %d", list->items[i].quantity);
				}
			}
			break;
		}
	}

	if (!found) 
	{
		clear();
		mvprintw(0, 0, "Item not found in the inventory.");
	}

	refresh();
	getch();
}

void search_item(InventoryList* list) 
{
	char name[MAX_NAME];
	get_search_input(name); 

	char nameLower[MAX_NAME];
	strcpy(nameLower, name);
	for (int i = 0; nameLower[i]; i++) nameLower[i] = tolower(nameLower[i]);

	int found = 0;
	for (int i = 0; i < list->size; i++) 
	{
		char itemNameLower[MAX_NAME];
		strcpy(itemNameLower, list->items[i].name);
		for (int j = 0; itemNameLower[j]; j++) itemNameLower[j] = tolower(itemNameLower[j]);

		if (strcmp(nameLower, itemNameLower) == 0) 
		{
			found = 1;
			clear();
			mvprintw(0, 0, "Name: %s\n", list->items[i].name);
			mvprintw(1, 0, "Description: %s\n", list->items[i].description);
			mvprintw(2, 0, "Category: %s\n", categories(list->items[i].category));
			mvprintw(3, 0, "Date: %s\n", list->items[i].date);
			mvprintw(4, 0, "Quantity: %d\n", list->items[i].quantity);
			mvprintw(5, 0, "Price: Rs%.2f\n", list->items[i].price);
			break;
		}
	}

	if (!found) 
	{
		clear();
		mvprintw(0, 0, "Item not found in the inventory.");
	}
	refresh();
	getch();
}

void generate_reports(InventoryList* list) 
{
	clear();
	mvprintw(0, 0, "Report 1: List of all items in the inventory\n");
	int line = 1;
	for (int i = 0; i < list->size; i++) 
	{
		mvprintw(line++, 0, "Name: %s, Description: %s, Category: %s, Quantity: %d, Price: Rs%.2f",
			list->items[i].name, list->items[i].description, categories(list->items[i].category),
			list->items[i].quantity, list->items[i].price);
	}

	mvprintw(line++, 0, "\nReport 2: Total value of inventory\n");
	double totalValue = 0;
	for (int i = 0; i < list->size; i++) totalValue += list->items[i].quantity * list->items[i].price;

	mvprintw(line, 0, "Total value of inventory: Rs%.2f", totalValue);

	refresh();
	getch();
}
