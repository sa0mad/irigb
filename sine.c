#include <stdio.h>
#include <math.h>

int main()
{
	double phi;
	int i, a;

	printf("int\tsin_table[256] =\n\t{ ");
	for (i = 0; i < 256; i++)
	{
		phi = 2*M_PI*i/256.0;
		a = 32767 * sin(phi);
		printf("%6i", a);
		if (i < 255)
			printf(", ");
		if ((i % 8) == 7)
			printf("\n\t  ");
	}
	printf("};\n");
	return 0;
}
