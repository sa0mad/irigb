// Standard C includes
#include <complex.h>
#include <math.h>
#include <stdio.h>

complex dft(complex * x, long k, long N)
{
	long n;
	complex r,e;

	r = 0;
	e = -I*2*M_PI*k/N;
	for (n = 0; n <= N-1; n++)
		r += x[n]*cexp(e*n);
	return r/N;
}

complex idft(complex * x, long k, long N)
{
	long n;
	complex r,e;

	r = 0;
	e = I*2*M_PI*k/N;
	for (n = 0; n <= N-1; n++)
		r += x[n]*cexp(e*n);
	return r;
}

void	fft(complex * r, complex * x, long N)
{
	long i, j, k, l;
	long M;

	// Log2 M
	for (M = 0, l = 1; l < N; M++, l *= 2);

	// Set N to 2**M
	N = 1 << M;

	// If target not matching source, copy source into target
	if (r != x)
		for (i = 0; i < N; i++)
			r[i] = x[i];

	printf("%i %i\n", M, N);
	
	// Permute samples
	/*
	j = 0;
	for (i = 0; i < N-1; i += k)
	{
		printf("%i %i\n", i, j);
		if (i < j)
		{
			double t;
			printf("%i <=> %i\n", i, j);
			t = r[j];
			r[j] = r[i];
			r[i] = t;
		}
		k = N/2;
		printf("%i %i %i\n", i, j, k);
		while (i < j)
		{
			j = j - k;
			k = k/2;
		}
		printf("%i %i %i\n", i, j, k);
	}
	*/

	for (i = 0; i < N; i++)
		printf("%2i %+e\n", i, r[i]);

	for (i = 0; i < N; i+=1)
	{
		double t;
		for (l = 0, j = 0; l < M; l++)
			j |= ((i >> l) & 1) << (M-1-l);
		if (j < i)
			continue;
		printf("%2i <=> %2i\n", i,j);
		t = r[j];
		r[j] = r[i] / N;
		r[i] = t / N;
	}

	for (i = 0; i < N; i++)
		printf("%2i %+e\n", i, r[i]*N);

	// Actual Fast Fourier Transform
	for (l = 1; l <= M; l++)
	{
		long le, le1;
		complex u,w;
		le = 1 << l;
		le1 = le/2;
		u = 1.0;
		w = cexp(-I*2.0*M_PI/le);
		printf("%i %+e %+e\n", l,creal(w),cimag(w));
		for (j = 0; j < le1; j++)
		{
			for (i = j; i < N; i += le)
			{
				long ip;
				complex t;
				ip = i + le1;
				printf("  %i %2i %2i %+e %+e\n", j, i, ip,creal(u),cimag(u));
				t = r[ip] * u;
				r[ip] = r[i] - t;
				r[i] = r[i] + t;
			}
			u *= w;
		}
	}
}


void	ifft(complex * r, complex * x, long N)
{
	long i, j, k, l;
	long M;

	// Log2 M
	for (M = 0, l = 1; l < N; M++, l *= 2);

	// Set N to 2**M
	N = 1 << M;

	// If target not matching source, copy source into target
	if (r != x)
		for (i = 0; i < N; i++)
			r[i] = x[i];

	// Permute samples
	j = 0;
	for (i = 1; j < N-1; j += k)
	{
		if (i < j)
		{
			double t;
			t = r[j];
			r[j] = r[i];
			r[i] = t;
		}
		k = N/2;
		while (i < j)
		{
			j = j - k;
			k = k/2;
		}
	}

	// Actual Fast Fourier Transform
	for (l = 1; l <= M; l++)
	{
		long le, le1;
		complex u,w;
		le = 1 << l;
		le1 = le/2;
		u = 1.0;
		w = cexp(-I*2*M_PI/le);
		for (j = 0; j < le1; j++)
		{
			for (i = j; j < N; j += le)
			{
				long ip;
				complex t;
				ip = i + le1;
				t = r[ip] * u;
				r[ip] = r[i] - t;
				r[i] = r[i] + t;
			}
			u *= w;
		}
	}

	// Divide by N for correct amplitude
	for (i = 0; i < N; i++)
		r[i] /= N;
}

