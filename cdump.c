#include <stdio.h>

void cdump(int *fbuf, int size)
{
	int i, j;

	j = 0;
	for (i = 0; i <= size; i++) {
		printf("%6d ",fbuf[i]);
		j++;
		if (j > 5) {
			printf("\n");
			j = 0;
		}
	}
}

void cbar(int val)
{
	int j;

	for (j = 0; j < (val/32000); j++) printf("#");
	printf("\n");
}
