#ifndef INS_H
#define INS_H

#include <stdlib.h> 
#include <stddef.h> 

/* Macro to append to a dynamic array (vec *xs) */
#define da_append(xs, x)\
	do \
	{ \
		if ((xs)->count >= (xs)->capacity) \
		{ \
			(xs)->capacity = (xs)->capacity == 0 ? 256 : (xs)->capacity * 2; \
			(xs)->items = realloc((xs)->items, (xs)->capacity * sizeof(*((xs)->items))); \
		} \
		(xs)->items[(xs)->count++] = (x); \
	} while(0)

typedef struct 
{
	int category;
	char *name;
	char *description;
	char date[80];
	float price;
} inventory;

typedef struct
{
	inventory *items;
	size_t count;
	size_t capacity;
} vec;

void addItem(vec *v);
void deleteItem(vec *v);
void searchItem(const vec *v); /* const cuz it's read-only */
void generateReports(const vec *v); /* const cuz it's read-only */

#endif
