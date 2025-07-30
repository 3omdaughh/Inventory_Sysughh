#include <ncurses.h>
#include "inventory.h"
#include "ui.h"

int main() 
{
	InventoryList inventory;
	int choice;

	init_ui();
	init_inventory(&inventory);

	do 
	{
		display_menu();
		choice = get_menu_choice();

		switch (choice) 
		{
			case 1:
				add_item(&inventory);
				break;
			case 2:
				delete_item(&inventory);
				break;
			case 3:
				search_item(&inventory);
				break;
			case 4:
				generate_reports(&inventory);
				break;
			case 5:
				clear();
				mvprintw(0, 0, "Exiting the Inventory Management System. Thank you for using!");
				refresh();
				getch();
				break;
			default:
				clear();
				mvprintw(0, 0, "Invalid choice! Press any key to continue.");
				refresh();
				getch();
		}
	} while (choice != 5);

	free_inventory(&inventory);
	cleanup_ui();
	return 0;
}
