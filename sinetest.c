#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <complex.h>

#include "sine.h"
#include "irigb.h"
int	sin_table[256];

double	samples[48];
complex	freq[48];

void	dft()
{
	complex w0;
	int i,j;

	w0 = -2*M_PI*I/48;

	for (i = 0; i <= 24; i++)
	{
		freq[i] = 0.0;

		for (j = 0; j < 24; j+=2)
			freq[i] += (samples[j]+I*samples[j+2])*cexp(j*i*w0);
	}
}

double	sine_dist()
{
	int i;
	for (i = 0; i < 24; i++)
	{
		long frac;
		frac = (i << 8) / 48;
		samples[i] = sin_table[frac];
	}
	dft();
	double carrier = cabs(freq[1]);
	double dist = 0.0;
	for (i = 2; i < 24; i++)
		dist += cabs(freq[i]);
	return dist/carrier;
}

double	irigb_sine_dist()
{
	int i;
	for (i = 0; i < 48; i++)
	{
		long frac;
		frac = (i << 24) / 48;
		samples[i] = irigb_sin(32767,frac);
	}
	dft();
	double carrier = cabs(freq[1]);
	double dist = 0.0;
	for (i = 2; i < 24; i++)
		dist += cabs(freq[i]);
	return dist/carrier;
}

int main()
{
	printf("%e\n", sine_dist());
	printf("%e\n", irigb_sine_dist());
	return 0;
}
