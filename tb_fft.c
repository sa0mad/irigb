// Standard C includes
#include <complex.h>
#include <math.h>
#include <stdio.h>

#include "tb.h"

#include "fft.h"

TB_VAR(fft);

void tb_dft()
{
	int i;
	complex samples[16];
	complex * sp = (complex *)&samples;

	for (i = 0; i < 16; i++)
		samples[i] = 1.0;
	TB_TEST_EXPECT_M_DBL_PREC(fft, cabs(dft(sp, 0, 16)), 1.0, 1E-10, "dft test");
	TB_TEST_EXPECT_M_DBL_ZERO(fft, cabs(dft(sp, 1, 16)), "dft test");
	TB_TEST_EXPECT_M_DBL_ZERO(fft, cabs(dft(sp, 2, 16)), "dft test");
	TB_TEST_EXPECT_M_DBL_ZERO(fft, cabs(dft(sp, 3, 16)), "dft test");
	TB_TEST_EXPECT_M_DBL_ZERO_PREC(fft, cabs(dft(sp, 4, 16)), 1E-15, "dft test");
	TB_TEST_EXPECT_M_DBL_ZERO(fft, cabs(dft(sp, 5, 16)), "dft test");
	TB_TEST_EXPECT_M_DBL_ZERO_PREC(fft, cabs(dft(sp, 6, 16)), 1E-15, "dft test");
	TB_TEST_EXPECT_M_DBL_ZERO_PREC(fft, cabs(dft(sp, 7, 16)), 1E-15, "dft test");

	for (i = 0; i < 16; i++)
		samples[i] = cexp(I*2*M_PI*i/16);
	TB_TEST_EXPECT_M_DBL_ZERO(fft, cabs(dft(sp, 0, 16)), "dft test");
	TB_TEST_EXPECT_M_DBL_PREC(fft, cabs(dft(sp, 1, 16)), 1.0, 1E-10, "dft test");
	TB_TEST_EXPECT_M_DBL_ZERO(fft, cabs(dft(sp, 2, 16)), "dft test");
	TB_TEST_EXPECT_M_DBL_ZERO(fft, cabs(dft(sp, 3, 16)), "dft test");
	TB_TEST_EXPECT_M_DBL_ZERO(fft, cabs(dft(sp, 4, 16)), "dft test");
	TB_TEST_EXPECT_M_DBL_ZERO(fft, cabs(dft(sp, 5, 16)), "dft test");
	TB_TEST_EXPECT_M_DBL_ZERO_PREC(fft, cabs(dft(sp, 6, 16)), 1E-15, "dft test");
	TB_TEST_EXPECT_M_DBL_ZERO(fft, cabs(dft(sp, 7, 16)), "dft test");

	for (i = 0; i < 16; i++)
		samples[i] = cexp(I*2*M_PI*2*i/16);
	TB_TEST_EXPECT_M_DBL_ZERO(fft, cabs(dft(sp, 0, 16)), "dft test");
	TB_TEST_EXPECT_M_DBL_ZERO(fft, cabs(dft(sp, 1, 16)), "dft test");
	TB_TEST_EXPECT_M_DBL_PREC(fft, cabs(dft(sp, 2, 16)), 1.0, 1E-10, "dft test");
	TB_TEST_EXPECT_M_DBL_ZERO(fft, cabs(dft(sp, 3, 16)), "dft test");
	TB_TEST_EXPECT_M_DBL_ZERO(fft, cabs(dft(sp, 4, 16)), "dft test");
	TB_TEST_EXPECT_M_DBL_ZERO_PREC(fft, cabs(dft(sp, 5, 16)), 1E-15, "dft test");
	TB_TEST_EXPECT_M_DBL_ZERO_PREC(fft, cabs(dft(sp, 6, 16)), 1E-15, "dft test");
	TB_TEST_EXPECT_M_DBL_ZERO_PREC(fft, cabs(dft(sp, 7, 16)), 1E-15, "dft test");

	for (i = 0; i < 16; i++)
		samples[i] = cexp(I*2*M_PI*3*i/16);
	TB_TEST_EXPECT_M_DBL_ZERO(fft, cabs(dft(sp, 0, 16)), "dft test");
	TB_TEST_EXPECT_M_DBL_ZERO(fft, cabs(dft(sp, 1, 16)), "dft test");
	TB_TEST_EXPECT_M_DBL_ZERO(fft, cabs(dft(sp, 2, 16)), "dft test");
	TB_TEST_EXPECT_M_DBL_PREC(fft, cabs(dft(sp, 3, 16)), 1.0, 1E-10, "dft test");
	TB_TEST_EXPECT_M_DBL_ZERO(fft, cabs(dft(sp, 4, 16)), "dft test");
	TB_TEST_EXPECT_M_DBL_ZERO_PREC(fft, cabs(dft(sp, 5, 16)), 1E-15, "dft test");
	TB_TEST_EXPECT_M_DBL_ZERO_PREC(fft, cabs(dft(sp, 6, 16)), 1E-15, "dft test");
	TB_TEST_EXPECT_M_DBL_ZERO_PREC(fft, cabs(dft(sp, 7, 16)), 1E-15, "dft test");

	for (i = 0; i < 16; i++)
		samples[i] = cexp(I*2*M_PI*4*i/16);
	TB_TEST_EXPECT_M_DBL_ZERO_PREC(fft, cabs(dft(sp, 0, 16)), 1E-15, "dft test");
	TB_TEST_EXPECT_M_DBL_ZERO(fft, cabs(dft(sp, 1, 16)), "dft test");
	TB_TEST_EXPECT_M_DBL_ZERO(fft, cabs(dft(sp, 2, 16)), "dft test");
	TB_TEST_EXPECT_M_DBL_ZERO(fft, cabs(dft(sp, 3, 16)), "dft test");
	TB_TEST_EXPECT_M_DBL_PREC(fft, cabs(dft(sp, 4, 16)), 1.0, 1E-10, "dft test");
	TB_TEST_EXPECT_M_DBL_ZERO_PREC(fft, cabs(dft(sp, 5, 16)), 1E-15, "dft test");
	TB_TEST_EXPECT_M_DBL_ZERO_PREC(fft, cabs(dft(sp, 6, 16)), 1E-15, "dft test");
	TB_TEST_EXPECT_M_DBL_ZERO_PREC(fft, cabs(dft(sp, 7, 16)), 1E-15, "dft test");

	for (i = 0; i < 16; i++)
		samples[i] = cexp(I*2*M_PI*5*i/16);
	TB_TEST_EXPECT_M_DBL_ZERO(fft, cabs(dft(sp, 0, 16)), "dft test");
	TB_TEST_EXPECT_M_DBL_ZERO(fft, cabs(dft(sp, 1, 16)), "dft test");
	TB_TEST_EXPECT_M_DBL_ZERO_PREC(fft, cabs(dft(sp, 2, 16)), 1E-15, "dft test");
	TB_TEST_EXPECT_M_DBL_ZERO_PREC(fft, cabs(dft(sp, 3, 16)), 1E-15, "dft test");
	TB_TEST_EXPECT_M_DBL_ZERO_PREC(fft, cabs(dft(sp, 4, 16)), 1E-15, "dft test");
	TB_TEST_EXPECT_M_DBL_PREC(fft, cabs(dft(sp, 5, 16)), 1.0, 1E-10, "dft test");
	TB_TEST_EXPECT_M_DBL_ZERO_PREC(fft, cabs(dft(sp, 6, 16)), 1E-15, "dft test");
	TB_TEST_EXPECT_M_DBL_ZERO_PREC(fft, cabs(dft(sp, 7, 16)), 1E-15, "dft test");

	for (i = 0; i < 16; i++)
		samples[i] = cexp(I*2*M_PI*6*i/16);
	TB_TEST_EXPECT_M_DBL_ZERO_PREC(fft, cabs(dft(sp, 0, 16)), 1E-15, "dft test");
	TB_TEST_EXPECT_M_DBL_ZERO_PREC(fft, cabs(dft(sp, 1, 16)), 1E-15, "dft test");
	TB_TEST_EXPECT_M_DBL_ZERO_PREC(fft, cabs(dft(sp, 2, 16)), 1E-15, "dft test");
	TB_TEST_EXPECT_M_DBL_ZERO_PREC(fft, cabs(dft(sp, 3, 16)), 1E-15, "dft test");
	TB_TEST_EXPECT_M_DBL_ZERO_PREC(fft, cabs(dft(sp, 4, 16)), 1E-15, "dft test");
	TB_TEST_EXPECT_M_DBL_ZERO_PREC(fft, cabs(dft(sp, 5, 16)), 1E-15, "dft test");
	TB_TEST_EXPECT_M_DBL_PREC(fft, cabs(dft(sp, 6, 16)), 1.0, 1E-10, "dft test");
	TB_TEST_EXPECT_M_DBL_ZERO_PREC(fft, cabs(dft(sp, 7, 16)), 1E-15, "dft test");

	for (i = 0; i < 16; i++)
		samples[i] = cexp(I*2*M_PI*7*i/16);
	TB_TEST_EXPECT_M_DBL_ZERO_PREC(fft, cabs(dft(sp, 0, 16)), 1E-15, "dft test");
	TB_TEST_EXPECT_M_DBL_ZERO_PREC(fft, cabs(dft(sp, 1, 16)), 1E-15, "dft test");
	TB_TEST_EXPECT_M_DBL_ZERO_PREC(fft, cabs(dft(sp, 2, 16)), 1E-15, "dft test");
	TB_TEST_EXPECT_M_DBL_ZERO_PREC(fft, cabs(dft(sp, 3, 16)), 1E-15, "dft test");
	TB_TEST_EXPECT_M_DBL_ZERO_PREC(fft, cabs(dft(sp, 4, 16)), 1E-15, "dft test");
	TB_TEST_EXPECT_M_DBL_ZERO_PREC(fft, cabs(dft(sp, 5, 16)), 1E-15, "dft test");
	TB_TEST_EXPECT_M_DBL_ZERO_PREC(fft, cabs(dft(sp, 6, 16)), 1E-15, "dft test");
	TB_TEST_EXPECT_M_DBL_PREC(fft, cabs(dft(sp, 7, 16)), 1.0, 1E-10, "dft test");

	for (i = 0; i <8; i++)
		samples[i] = +1.0;
	for (i = 8; i < 16; i++)
		samples[i] = -1.0;
	TB_TEST_EXPECT_M_DBL_ZERO(fft, cabs(dft(sp, 0, 16)), "dft test");
	//TB_TEST_EXPECT_M_DBL_PREC(fft, cabs(dft(sp, 1, 16)), 1.0, 1E-10, "dft test");
	TB_TEST_EXPECT_M_DBL_ZERO_PREC(fft, cabs(dft(sp, 2, 16)), 1E-10, "dft test");
	//TB_TEST_EXPECT_M_DBL_PREC(fft, cabs(dft(sp, 3, 16)), 1.0/3, 1E-10, "dft test");
	TB_TEST_EXPECT_M_DBL_ZERO_PREC(fft, cabs(dft(sp, 4, 16)), 1E-10, "dft test");
	//TB_TEST_EXPECT_M_DBL_PREC(fft, cabs(dft(sp, 5, 16)), 1.0/5, 1E-10, "dft test");
	TB_TEST_EXPECT_M_DBL_ZERO_PREC(fft, cabs(dft(sp, 6, 16)), 1E-10, "dft test");
	//TB_TEST_EXPECT_M_DBL_PREC(fft, cabs(dft(sp, 7, 16)), 1.0/7, 1E-10, "dft test");
}

void tb_fft()
{
	int i;
	complex samples[16], spectrum[16];
	complex * sap = (complex *)&samples;
	complex * spp = (complex *)&spectrum;

	for (i = 0; i < 16; i++)
		sap[i] = 1.0;
	fft(spp,sap,16);
	TB_TEST_EXPECT_M_DBL_PREC(fft, cabs(spp[0]), 1.0, 1E-10, "dft test");
	TB_TEST_EXPECT_M_DBL_ZERO(fft, cabs(spp[1]), "dft test");
	TB_TEST_EXPECT_M_DBL_ZERO(fft, cabs(spp[2]), "dft test");
	TB_TEST_EXPECT_M_DBL_ZERO(fft, cabs(spp[3]), "dft test");
	TB_TEST_EXPECT_M_DBL_ZERO_PREC(fft, cabs(spp[4]), 1E-15, "dft test");
	TB_TEST_EXPECT_M_DBL_ZERO(fft, cabs(spp[5]), "dft test");
	TB_TEST_EXPECT_M_DBL_ZERO_PREC(fft, cabs(spp[6]), 1E-15, "dft test");
	TB_TEST_EXPECT_M_DBL_ZERO_PREC(fft, cabs(spp[7]), 1E-15, "dft test");

	for (i = 0; i < 16; i++)
		sap[i] = cexp(I*2*M_PI*i/16);
	fft(spp,sap,16);
	TB_TEST_EXPECT_M_DBL_ZERO(fft, cabs(spp[0]), "dft test");
	TB_TEST_EXPECT_M_DBL_PREC(fft, cabs(spp[1]), 1.0, 1E-10, "dft test");
	TB_TEST_EXPECT_M_DBL_ZERO(fft, cabs(spp[2]), "dft test");
	TB_TEST_EXPECT_M_DBL_ZERO(fft, cabs(spp[3]), "dft test");
	TB_TEST_EXPECT_M_DBL_ZERO(fft, cabs(spp[4]), "dft test");
	TB_TEST_EXPECT_M_DBL_ZERO(fft, cabs(spp[5]), "dft test");
	TB_TEST_EXPECT_M_DBL_ZERO_PREC(fft, cabs(spp[6]), 1E-15, "dft test");
	TB_TEST_EXPECT_M_DBL_ZERO(fft, cabs(spp[7]), "dft test");

	return;
	
	for (i = 0; i < 16; i++)
		sap[i] = cexp(I*2*M_PI*2*i/16);
	fft(spp,sap,16);
	TB_TEST_EXPECT_M_DBL_ZERO(fft, cabs(spp[0]), "dft test");
	TB_TEST_EXPECT_M_DBL_ZERO(fft, cabs(spp[1]), "dft test");
	TB_TEST_EXPECT_M_DBL_PREC(fft, cabs(spp[2]), 1.0, 1E-10, "dft test");
	TB_TEST_EXPECT_M_DBL_ZERO(fft, cabs(spp[3]), "dft test");
	TB_TEST_EXPECT_M_DBL_ZERO(fft, cabs(spp[4]), "dft test");
	TB_TEST_EXPECT_M_DBL_ZERO_PREC(fft, cabs(spp[5]), 1E-15, "dft test");
	TB_TEST_EXPECT_M_DBL_ZERO_PREC(fft, cabs(spp[6]), 1E-15, "dft test");
	TB_TEST_EXPECT_M_DBL_ZERO_PREC(fft, cabs(spp[7]), 1E-15, "dft test");

	for (i = 0; i < 16; i++)
		sap[i] = cexp(I*2*M_PI*3*i/16);
	fft(spp,sap,16);
	TB_TEST_EXPECT_M_DBL_ZERO(fft, cabs(spp[0]), "dft test");
	TB_TEST_EXPECT_M_DBL_ZERO(fft, cabs(spp[1]), "dft test");
	TB_TEST_EXPECT_M_DBL_ZERO(fft, cabs(spp[2]), "dft test");
	TB_TEST_EXPECT_M_DBL_PREC(fft, cabs(spp[3]), 1.0, 1E-10, "dft test");
	TB_TEST_EXPECT_M_DBL_ZERO(fft, cabs(spp[4]), "dft test");
	TB_TEST_EXPECT_M_DBL_ZERO_PREC(fft, cabs(spp[5]), 1E-15, "dft test");
	TB_TEST_EXPECT_M_DBL_ZERO_PREC(fft, cabs(spp[6]), 1E-15, "dft test");
	TB_TEST_EXPECT_M_DBL_ZERO_PREC(fft, cabs(spp[7]), 1E-15, "dft test");

	for (i = 0; i < 16; i++)
		sap[i] = cexp(I*2*M_PI*4*i/16);
	fft(spp,sap,16);
	TB_TEST_EXPECT_M_DBL_ZERO_PREC(fft, cabs(spp[0]), 1E-15, "dft test");
	TB_TEST_EXPECT_M_DBL_ZERO(fft, cabs(spp[1]), "dft test");
	TB_TEST_EXPECT_M_DBL_ZERO(fft, cabs(spp[2]), "dft test");
	TB_TEST_EXPECT_M_DBL_ZERO(fft, cabs(spp[3]), "dft test");
	TB_TEST_EXPECT_M_DBL_PREC(fft, cabs(spp[4]), 1.0, 1E-10, "dft test");
	TB_TEST_EXPECT_M_DBL_ZERO_PREC(fft, cabs(spp[5]), 1E-15, "dft test");
	TB_TEST_EXPECT_M_DBL_ZERO_PREC(fft, cabs(spp[6]), 1E-15, "dft test");
	TB_TEST_EXPECT_M_DBL_ZERO_PREC(fft, cabs(spp[7]), 1E-15, "dft test");

	for (i = 0; i < 16; i++)
		sap[i] = cexp(I*2*M_PI*5*i/16);
	fft(spp,sap,16);
	TB_TEST_EXPECT_M_DBL_ZERO(fft, cabs(spp[0]), "dft test");
	TB_TEST_EXPECT_M_DBL_ZERO(fft, cabs(spp[1]), "dft test");
	TB_TEST_EXPECT_M_DBL_ZERO_PREC(fft, cabs(spp[2]), 1E-15, "dft test");
	TB_TEST_EXPECT_M_DBL_ZERO_PREC(fft, cabs(spp[3]), 1E-15, "dft test");
	TB_TEST_EXPECT_M_DBL_ZERO_PREC(fft, cabs(spp[4]), 1E-15, "dft test");
	TB_TEST_EXPECT_M_DBL_PREC(fft, cabs(spp[5]), 1.0, 1E-10, "dft test");
	TB_TEST_EXPECT_M_DBL_ZERO_PREC(fft, cabs(spp[6]), 1E-15, "dft test");
	TB_TEST_EXPECT_M_DBL_ZERO_PREC(fft, cabs(spp[7]), 1E-15, "dft test");

	for (i = 0; i < 16; i++)
		sap[i] = cexp(I*2*M_PI*6*i/16);
	fft(spp,sap,16);
	TB_TEST_EXPECT_M_DBL_ZERO_PREC(fft, cabs(spp[0]), 1E-15, "dft test");
	TB_TEST_EXPECT_M_DBL_ZERO_PREC(fft, cabs(spp[1]), 1E-15, "dft test");
	TB_TEST_EXPECT_M_DBL_ZERO_PREC(fft, cabs(spp[2]), 1E-15, "dft test");
	TB_TEST_EXPECT_M_DBL_ZERO_PREC(fft, cabs(spp[3]), 1E-15, "dft test");
	TB_TEST_EXPECT_M_DBL_ZERO_PREC(fft, cabs(spp[4]), 1E-15, "dft test");
	TB_TEST_EXPECT_M_DBL_ZERO_PREC(fft, cabs(spp[5]), 1E-15, "dft test");
	TB_TEST_EXPECT_M_DBL_PREC(fft, cabs(spp[6]), 1.0, 1E-10, "dft test");
	TB_TEST_EXPECT_M_DBL_ZERO_PREC(fft, cabs(spp[7]), 1E-15, "dft test");

	for (i = 0; i < 16; i++)
		sap[i] = cexp(I*2*M_PI*7*i/16);
	fft(spp,sap,16);
	TB_TEST_EXPECT_M_DBL_ZERO_PREC(fft, cabs(spp[0]), 1E-15, "dft test");
	TB_TEST_EXPECT_M_DBL_ZERO_PREC(fft, cabs(spp[1]), 1E-15, "dft test");
	TB_TEST_EXPECT_M_DBL_ZERO_PREC(fft, cabs(spp[2]), 1E-15, "dft test");
	TB_TEST_EXPECT_M_DBL_ZERO_PREC(fft, cabs(spp[3]), 1E-15, "dft test");
	TB_TEST_EXPECT_M_DBL_ZERO_PREC(fft, cabs(spp[4]), 1E-15, "dft test");
	TB_TEST_EXPECT_M_DBL_ZERO_PREC(fft, cabs(spp[5]), 1E-15, "dft test");
	TB_TEST_EXPECT_M_DBL_ZERO_PREC(fft, cabs(spp[6]), 1E-15, "dft test");
	TB_TEST_EXPECT_M_DBL_PREC(fft, cabs(spp[7]), 1.0, 1E-10, "dft test");

	return;
	
	for (i = 0; i <8; i++)
		sap[i] = +1.0;
	for (i = 8; i < 16; i++)
		sap[i] = -1.0;
	fft(spp,sap,16);
	TB_TEST_EXPECT_M_DBL_PREC(fft, cabs(spp[0]), cabs(dft(sap, 0, 16)), 1E-10, "fft test");
	TB_TEST_EXPECT_M_DBL_PREC(fft, cabs(spp[1]), cabs(dft(sap, 1, 16)), 1E-10, "fft test");
	TB_TEST_EXPECT_M_DBL_PREC(fft, cabs(spp[2]), cabs(dft(sap, 2, 16)), 1E-10, "fft test");
	TB_TEST_EXPECT_M_DBL_PREC(fft, spp[3], cabs(dft(sap, 3, 16)), 1E-10, "fft test");
	TB_TEST_EXPECT_M_DBL_PREC(fft, spp[4], cabs(dft(sap, 4, 16)), 1E-10, "fft test");
	TB_TEST_EXPECT_M_DBL_PREC(fft, spp[5], cabs(dft(sap, 5, 16)), 1E-10, "fft test");
	TB_TEST_EXPECT_M_DBL_PREC(fft, spp[6], cabs(dft(sap, 6, 16)), 1E-10, "fft test");
	TB_TEST_EXPECT_M_DBL_PREC(fft, spp[7], cabs(dft(sap, 7, 16)), 1E-10, "fft test");
}

int main()
{
	TB_VAR_RESET(fft);
	tb_dft();
	tb_fft();
	TB_RESULT(fft);
	return 0;
}
