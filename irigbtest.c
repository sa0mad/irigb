#include <stdint.h>
#include <stdio.h>

#include "time.h"
#include "irigb.h"

#define RAW 1

#if RAW
int	display_count = 0;
int	display_phase = 0;
int	display_adstate = 0;
int	display_pwmstate = 0;
int	display_sfstate = 0;
int	display_fstate = 0;
int	display_bitstate = 0;
int	display_cyclestate = 0;
int	display_phasediff = 0;
int	display_timens = 0;
int	display_nl = 0;
#else
int	display_count = 1;
int	display_phase = 1;
int	display_adstate = 1;
int	display_pwmstate = 1;
int	display_sfstate = 1;
int	display_fstate = 1;
int	display_bitstate = 1;
int	display_cyclestate = 1;
int	display_phasediff = 1;
int	display_timens = 1;
int	display_nl = 1;
#endif

double fabs(double a)
{
	if (a < 0)
		return -a;
	return a;
}

FILE * 	fp;

int	get_sample()
{
	int	b0, b1;
	int	v;
	b0 = fgetc(fp);
	b1 = fgetc(fp);
	v = (b1 << 8) | b0;
	if (v > 32767)
		v -= 65535;
	return v;
}

int main()
{
	irigb_state *is_gen;
	irigb_state *is_gen_prev;
	irigb_state *is_det;
	int sample;
	int i;
	double phasediff;

	// Setup raw time of sampled sequence
	long	time0_year = 2017;
	long	time0_day  = 74;
	long	time0_hour = 13;
	long	time0_min  = 10;
	long	time0_sec  =  9;
	long	time0_ns   = -176480000;
	long	time0 = time0_year - 1970;
	time0 *= 365;
	time0 += leapdays(time0_year,time0_day);
	time0 += time0_day;
	time0 *= 24;
	time0 += time0_hour;
	time0 *= 60;
	time0 += time0_min;
	time0 *= 60;
	time0 += time0_sec;
	long	nstime0 = time0*1000000000L;
	nstime0 += time0_ns;
	nstime0 = epochtimens(2017,74,13,10,9,-176480000);

	// Setup sample frequency
	double	y_s = -8.460E-6;
	double	f_0 = 48000.0;
	double	f_s = f_0*(1-y_s);
	//double	f_s2 = f_0/(1-y_s);
	
	is_gen = irigb_create();
	is_gen_prev = irigb_create();
	irigb_init(is_gen, f_0);
	irigb_set_phase(is_gen, 0.0);

	if (RAW)
		fp = fopen("irig-audio1.raw","rb");

	is_det = irigb_create();
	irigb_init(is_det, f_s);
	irigb_set_phase(is_det, 0.0);

	// Print header
	display_nl = 0;
	if (display_count == 1)
	{
		printf("count  sample  time(s) ");
		display_nl = 1;
	}
	if (display_phase == 1)
	{
		printf(" phi_gen  phi_det  pd_det   ");
		display_nl = 1;
	}
	if (display_adstate == 1)
	{
		printf(" ad       s amp_low  amp_high m pw");
		display_nl = 1;
	}
	if (display_pwmstate == 1)
	{
		printf(" p");
		display_nl = 1;
	}
	if (display_sfstate == 1)
	{
		printf(" s s s");
		display_nl = 1;
	}
	if (display_fstate == 1)
	{
		printf(" f");
		display_nl = 1;
	}
	if (display_bitstate == 1)
	{
		printf(" bi");
		display_nl = 1;
	}
	if (display_cyclestate == 1)
	{
		printf(" cs c c");
		display_nl = 1;
	}
	if (display_phasediff == 1)
	{
		printf(" phi_diff  timediff      freq_det");
		display_nl = 1;
	}
	if (display_timens == 1)
	{
		printf(" ns time   ns time diff");
		display_nl = 1;
	}
	if (display_nl == 1)
		printf("\n");
	sample = 0;
	irigb_copy(is_gen_prev, is_gen);
	for (i = 0; i < 1320*48000; i++)
	{
		int	cycle_delayed;
		double	phase_delayed;
		long	nstime_delayed;
		long	nstime_diff;
		int	prev_sec;

		if (RAW)
		{
			sample = get_sample();
		}
		else
		{
			sample = irigb_gen_step(is_gen);
		}
		irigb_det_step(is_det, sample);
		phasediff = phase_delayed-irigb_get_phase(is_gen);
		phase_delayed = irigb_get_phase(is_det);
		nstime_diff = nstime_delayed-irigb_get_nstime(is_gen);
		nstime_delayed = irigb_get_nstime(is_det);
		if (i == 0)
			nstime_diff = 0;
		if (phasediff < -0.5)
			phasediff += 1.0;
		if (phasediff > 0.5)
			phasediff -= 1.0;


		// Only once per cycle
		if (cycle_delayed == irigb_get_cycle(is_det))
			continue;
		cycle_delayed = irigb_get_cycle(is_det);
		// Only once per bit
		if (cycle_delayed != 9)
			continue;

		// Sample count and value
		if (display_count == 1)
			printf("%6i %+6i %9.6f", i, sample, (double)i/48000.0);

		// Generator and receiver phase, detected phase
		if (display_phase == 1)
			printf(" %f %f %+f", irigb_get_phase(is_gen), irigb_get_phase(is_det), irigb_get_pd(is_det));

		// Amplitude detector state
		if (display_adstate == 1)
			printf(" %8.2f %i %8.2f %8.2f %i %2i", irigb_get_ad(is_det), irigb_get_ad_state(is_det), irigb_get_amp_low(is_det), irigb_get_amp_high(is_det), irigb_get_am(is_det), irigb_get_am_state(is_det));

		// PWM state
		if (display_pwmstate == 1)
			printf(".%i", irigb_get_pwm(is_det));
		else
		{
			/*
			printf("%i", irigb_get_pwm(is_det));
			if (irigb_get_bit(is_det) == 99)
				printf("\n");
			*/
		}

		// Subframe state
		if (display_sfstate == 1)
			printf(" %i %i %i", irigb_get_sf_state(is_det), irigb_get_sf_bit(is_gen), irigb_get_sf_bit(is_det));

		// Frame state
		if (display_fstate == 1)
			printf(" %i %i %i", irigb_get_f_state(is_det), irigb_get_f_sf(is_gen), irigb_get_f_sf(is_det));

		// Bit state
		if (display_bitstate == 1)
		{
			if (RAW == 0)
				printf(" %2i %2i", irigb_get_bit(is_gen), irigb_get_bit(is_det));
			else
				printf(" %i%i %2i", irigb_get_f_sf(is_det), irigb_get_sf_bit(is_det), irigb_get_bit(is_det));
		}

		// Cycle state
		if (display_cyclestate == 1)
			printf(" %2i.%i %i", irigb_get_cyclestate(is_det), irigb_get_cycle(is_gen), irigb_get_cycle(is_det));

		// Phase difference state
		if (display_phasediff == 1)
			printf(" %+f %+e %+e", phasediff, phasediff/1000.0, irigb_get_freq(is_det));

		// ns time state
		if (display_timens == 1)
			printf(" %11li %11li", irigb_get_nstime(is_det), nstime_diff);

		// Newline
		if (display_nl == 1)
			printf("\n");

		if ((irigb_get_bit(is_det) == 99) && (irigb_get_cycle(is_det) == 9) && (prev_sec != irigb_get_sec(is_det)))
		{
			int year, doy;
			year = irigb_get_year(is_det);
			doy  = irigb_get_day(is_det);
			//printf(" %8.2f %i %8.2f %8.2f %i %i", irigb_get_ad(is_det), irigb_get_ad_state(is_det), irigb_get_amp_low(is_det), irigb_get_amp_high(is_det), irigb_get_am(is_det), irigb_get_am_state(is_det));
			//printf(" %i %i ", irigb_get_sf_state(is_det), irigb_get_sf_bit(is_det));
			//printf(" %i %i ", irigb_get_f_state(is_det), irigb_get_f_sf(is_det));
			printf("%4i %3i %2i %2i %2i:%02i:%02i %02i %li %li %+e %+e\n", year, doy, doy2month(year, doy), doy2dom(year, doy), irigb_get_hour(is_det), irigb_get_min(is_det), irigb_get_sec(is_det), irigb_get_rxsec(is_det), irigb_get_nstime(is_det), irigb_get_nstime(is_det)-nstime0-(long)((double)i/f_s*1000000000.0), irigb_get_pd(is_det), irigb_get_freq(is_det));
			prev_sec = irigb_get_sec(is_det);
		}
		
		double phase_gen = irigb_get_phase(is_gen) + irigb_get_cycle(is_gen);
		double phase_det = irigb_get_phase(is_det) + irigb_get_cycle(is_det);
		double phase_diff = phase_det-phase_gen;
		if (i == 0)
			phase_diff = 0;
		if (phase_diff > 5)
			phase_diff -= 10;
		if (phase_diff < -5)
			phase_diff += 10;
		//printf("%6i %f %f %6i %f %f %f %f\n", irigb_get_cycle(is_det), irigb_get_phase(is_det), phase_det, irigb_get_cycle(is_gen), irigb_get_phase(is_gen), phase_gen, phase_diff, fabs(phase_diff));
		cycle_delayed = irigb_get_cycle(is_det);
		if (RAW == 0)
		{
		if ((fabs(phase_diff) > 1.0) && (irigb_get_am_state(is_det) > 0))
		{
			printf("ERROR: Cycle mismatch Tx->Rx!\n");
			break;
		}
		if ((irigb_get_sf_bit(is_gen) != irigb_get_sf_bit(is_det)) && (irigb_get_sf_state(is_det) == 1))
		{
			printf("ERROR: Subframe bit mismatch Tx->Rx!\n");
			break;
		}
		if ((irigb_get_f_sf(is_gen) != irigb_get_f_sf(is_det)) && (irigb_get_f_state(is_det) == 1))
		{
			printf("ERROR: Frame subframe mismatch Tx->Rx!\n");
			break;
		}
		}
		if (0) {
		if (((((irigb_get_nstime(is_det) / 1000000) % 10) != irigb_get_cycle(is_det)) && (irigb_get_f_state(is_det) == 1)) && (irigb_get_f_state(is_det) == 1))
		{
			printf("ERROR: Cycle mismatch Rx->Rx time!\n");
			break;
		}
		if (((((irigb_get_nstime(is_det) / 10000000) % 10) != irigb_get_sf_bit(is_det)) && (irigb_get_f_state(is_det) == 1)) && (irigb_get_f_state(is_det) == 1))
		{
			printf("ERROR: Sub-frame bit mismatch Rx->Rx time!\n");
			break;
		}
		if (((((irigb_get_nstime(is_det) / 100000000) % 10) != irigb_get_f_sf(is_det)) && (irigb_get_f_state(is_det) == 1)) && (irigb_get_f_state(is_det) == 1))
		{
			printf("ERROR: Sub-frame mismatch Rx->Rx time!\n");
			break;
		}
		if ((((irigb_get_nstime(is_det) / 10000000) % 100) != irigb_get_bit(is_det)) && (irigb_get_f_state(is_det) == 1))
		{
			printf("ERROR: Bit mismatch Rx->Rx time!\n");
			break;
		}
		}
	}
	irigb_free(is_gen);
	fclose(fp);
	irigb_free(is_det);
	return 0;
}
