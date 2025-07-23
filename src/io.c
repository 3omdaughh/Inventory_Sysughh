#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/io.h"

void save_data()
{
	FILE *f = fopen("data/inventory.csv", "w");
	if (!f)
	{
		perror("fopen (save)");
		return;
	}
	fclose(f);
}

void load_data()
{
	FILE *f = fopen("data/inventory.csv", "r")
	if (!f) return; /* File might not exist yet - skip loading */
	
	char line[512];
	while (fgets(line, sizeof(line), f))
	{
		/* --- */ 
	}
}
