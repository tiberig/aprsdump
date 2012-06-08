#include <stdio.h>

void cdump(char *fbuf, int size)
{
	int i, j;

	j = 0;
	for (i = 0; i <= size; i++) {
		printf("%4d ", fbuf[i]);
//		if (j++ >= 5) {
			printf("\n");
//			j = 0;
//		}
	}
}
