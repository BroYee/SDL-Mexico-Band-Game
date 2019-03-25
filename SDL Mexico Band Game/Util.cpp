#include "stdafx.h"

double drand(double low, double high)
{
	srand((unsigned)time(NULL));

	double d;

	d = (double)rand() / ((double)RAND_MAX + 1);
	return (low + d * (high - low));
}
