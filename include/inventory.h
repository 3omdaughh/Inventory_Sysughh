#ifndef INVENTORY_H
#define INVENTORY_H

#define MAX_NAME 50
#define MAX_DESC 100
#define MAX_DATE 80
#define MAX_ITEMS 100

typedef struct 
{
	char name[MAX_NAME];
	char description[MAX_DESC];
	int category;
	char date[MAX_DATE];
	int quantity;
	float price;
} Inventory;

typedef struct 
{
	Inventory* items;
	int size;
	int capacity;
} InventoryList;

const char* categories(int choice);
void init_inventory(InventoryList* list);
void free_inventory(InventoryList* list);
void add_item(InventoryList* list);
void delete_item(InventoryList* list);
void search_item(InventoryList* list);
void generate_reports(InventoryList* list);

#endif
