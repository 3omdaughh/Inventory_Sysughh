#ifndef INS_H
#define INS_H

#define da_append(xs, x)\
	do \
	{ \
		if (xs.count >= xs.capacity) \
		{ \
			if (xs.capacity == 0) xs.capacity = 256; \
			else xs.capacity *= 2; \
			xs.items = realloc (xs.items, xs.capacity*sizeof(*xs.items));\
		} \
		xs.items[xs.count++] = x;\
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

void addItem(/* dynamaic array in C */ );
void deleteItem(/* dynamaic array in C */ );
void searchItem(/* dynamaic array in C */ );
void generateReports(/* dynamaic array in C */ );

#endif
