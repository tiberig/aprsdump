#include <stdio.h>

static int avgmax=0,avgmin=0;

int audiometer(int *buf, int size)
{
	int i, samp;

	samp = 0;
	for (i = 0; i < size; i++) {
		if (buf[i] >= 0) samp = (samp + buf[i]) / 2;
//		if (buf[i] >= 0) avgmax = (avgmax + buf[i]) / 2;
//		if (buf[i] <= 0) avgmin = (avgmin + buf[i]) / 2;
	}
	avgmax = avgmax + (samp/500) - (avgmax/250);
	return avgmax;
}
