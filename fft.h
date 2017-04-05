// Standard C includes
#include <complex.h>

complex dft(complex * x, long k, long N);
complex idft(complex * x, long k, long N);
void	fft(complex * r, complex * x, long N);
void	ifft(complex * r, complex * x, long N);
