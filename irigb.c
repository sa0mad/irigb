// Standard C includes
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Project includes
#include "sintab.h"
#include "time.h"

// Module include
#include "irigb.h"

#define	PHASE_MS (1L << 24)
#define	CYCLE_LIMIT (10)
#define	AM_LIMIT (10)
#define SF_LIMIT (10)
#define F_LIMIT (10)

struct irigb_state
{
	double	samplerate;

	// PLL Phase detector
	long	pd;

	// foo begin

	// PLL PI loop control parameters
	long	p, i;

	// PLL Integrator state
	long	ifreq;
	//double	ifreq;

	// NCO frequency steering
	long	freq0;
	long	freq;
	//double	freq0;
	//double	freq;

	// NCO phase state
	long	phase;

	// foo end

	// PLL Amplitude detector
	long	ad;

	// PLL Amplitude integrator
	long	ai, aq;

	// Amplitude detector
	unsigned int	ad_state;
	long		ad_prev;
	long		ad_high;
	long		ad_low;

	// Amplitude PWM state
	unsigned int	am;
	unsigned int	am_state;
	unsigned int	pwm;

	// Cycle state
	unsigned int	cycle_state;
	unsigned int	cycle;

	// Subframe state
	unsigned int	sf_bit;
	unsigned int	sf_state;

	// Frame state
	unsigned int	f_sf;
	unsigned int	f_state;

	// Decode bit
	unsigned int	bit;

	// foo begin

	// Decoded fields
	unsigned int	year;
	unsigned int	day;
	unsigned int	hour;
	unsigned int	min;
	unsigned int	sec, rx_sec;

	// foo end
};

int 	irigb_sin(int amp, long phase)
{
	long	phase_0, phase_1, frac0, frac1;
	long	a;
	phase_0 = (phase / 65536 ) & 255;
	phase_1 = (phase_0 + 1) & 255;
	frac1 = phase & 65535;
	frac0 = 65536 - frac1;
	a = sin_table[phase_0]*frac0 + sin_table[phase_1]*frac1;
	a /= 65536;
	a *= amp;
	a /= 65536;
	return (int)a;
}

int 	irigb_cos(int amp, long phase)
{
	long	phase_0, phase_1, frac0, frac1;
	long	a;
	phase += PHASE_MS / 4;
	phase_0 = (phase / 65536) & 255;
	phase_1 = (phase_0 + 1) & 255;
	frac1 = phase & 65535;
	frac0 = 65536 - frac1;
	a = sin_table[phase_0]*frac0 + sin_table[phase_1]*frac1;
	a /= 65536;
	a *= amp;
	a /= 65536;
	return (int)a;
}

/*@null@*/ irigb_state * irigb_create()
{
	irigb_state * ibs;
	ibs = (irigb_state *)malloc(sizeof(irigb_state));
	if (ibs == NULL)
		return NULL;

	// Set samplerate
	ibs->samplerate = 0;
	
	// Clear time-counters
	ibs->cycle_state = 0;
	ibs->cycle = 0;
	ibs->bit = 0;
	ibs->sec = 0;
	ibs->min = 0;
	ibs->hour = 0;
	ibs->day = 0;
	ibs->year = 0;

	// PLL Phase detector
	ibs->pd = 0;

	// PLL Amplitude detector
	ibs->ad = 0;

	// PLL Amplitude integrator
	ibs->ai = 0;

	// PLL PI loop control parameters
	ibs->p = 0;
	ibs->i = 0;

	// PLL Integrator state
	ibs->ifreq = 0;

	// NCO frequency steering
	ibs->freq0 = 0;
	ibs->freq = 0;

	// NCO phase state
	ibs->phase = 0;

	ibs->ad_state = 0;
	ibs->ad_prev = 0;
	ibs->ad_low = 0;
	ibs->ad_high = 0;

	ibs->am = 0;
	ibs->am_state = 0;
	ibs->pwm = 0;

	ibs->sf_state = 0;
	ibs->sf_bit = 0;

	ibs->rx_sec = 0;
	ibs->aq = 0;
	ibs->f_sf = 0;
	ibs->f_state = 0;

	return ibs;
}

void	irigb_free(/*@null@*/ irigb_state * ibs)
{
	free(ibs);
}

void	irigb_init(irigb_state * ibs, double samplerate)
{
	// Set samplerate
	ibs->samplerate = samplerate;

	// PLL Phase detector
	ibs->pd = 0;

	// PLL Amplitude detector
	ibs->ad = 0;

	// PLL Amplitude integrator
	ibs->ai = 0;
	ibs->aq = 0;

	// PLL PI loop control parameters
	ibs->p = 0;
	ibs->i = 0;

	// PLL Integrator state
	ibs->ifreq = 0;

	// NCO frequency steering
	ibs->freq0 = (long)(1000.0/samplerate*256.0*256.0*256.0);
	ibs->freq = 0;

	// NCO phase state
	ibs->phase = 0;

	// Amplitude discriminator
	ibs->ad_state = 0;
	ibs->ad_prev = 0;
	ibs->ad_low = 0;
	ibs->ad_high = 0;

	// Amplitude detector
	ibs->am = 0;
	ibs->am_state = 0;
	ibs->pwm = 0;

	// Cycle state
	ibs->cycle_state = 0;
	ibs->cycle = 0;

	// Sub-frame state
	ibs->sf_state = 0;
	ibs->sf_bit = 0;

	// Sub-frame state
	ibs->f_state = 0;
	ibs->f_sf = 0;
	
	// Clear time-counters
	ibs->bit = 0;
	ibs->rx_sec = 0;
	ibs->sec = 0;
	ibs->min = 0;
	ibs->hour = 0;
	ibs->day = 0;
	ibs->year = 0;
}

void	irigb_init_tb(irigb_state * ibs, double samplerate)
{
	// Set samplerate
	ibs->samplerate = samplerate;

	// PLL Phase detector
	ibs->pd = 16777216;

	// PLL Amplitude detector
	ibs->ad = 11;

	// PLL Amplitude integrator
	ibs->ai = 11;
	ibs->aq = 11;

	// PLL PI loop control parameters
	ibs->p = 16777216;
	ibs->i = 16777216;

	// PLL Integrator state
	ibs->ifreq = 16777216;

	// NCO frequency steering
	ibs->freq0 = (long)(1000.0/samplerate*256.0*256.0*256.0);
	ibs->freq = 16777216;

	// NCO phase state
	ibs->phase = 16777216;

	// Amplitude discriminator
	ibs->ad_state = 1;
	ibs->ad_prev = 11;
	ibs->ad_low = 11;
	ibs->ad_high = 11;

	// Amplitude detector
	ibs->am = 1;
	ibs->am_state = 1;
	ibs->pwm = 1;

	// Cycle state
	ibs->cycle_state = 1;
	ibs->cycle = 1;

	// Sub-frame state
	ibs->sf_state = 1;
	ibs->sf_bit = 1;

	// Sub-frame state
	ibs->f_state = 1;
	ibs->f_sf = 1;
	
	// Clear time-counters
	ibs->bit = 1;
	ibs->rx_sec = 1;
	ibs->sec = 1;
	ibs->min = 1;
	ibs->hour = 1;
	ibs->day = 1;
	ibs->year = 1;
}

void	irigb_copy(irigb_state * dest, irigb_state * src)
{
	dest->samplerate = src->samplerate;
	
	// PLL Phase detector
	dest->pd = src->pd;

	// PLL Amplitude detector
	dest->ad = src->ad;

	// PLL Amplitude integrator
	dest->ai = src->ai;
	dest->aq = src->aq;

	// PLL PI loop control parameters
	dest->p = src->p;
	dest->i = src->i;

	// PLL Integrator state
	dest->ifreq = src->ifreq;

	// NCO frequency steering
	dest->freq0 = src->freq0;
	dest->freq  = src->freq;

	// NCO phase state
	dest->phase = src->phase;

	// Amplitude detector
	dest->ad_prev = src->ad_prev;
	dest->ad_high = src->ad_high;
	dest->ad_low = src->ad_low;
	dest->ad_state = src->ad_state;

	// Amplitude PWM state
	dest->am = src->am;
	dest->am_state = src->am_state;
	dest->pwm = src->pwm;

	// Subframe state
	dest->sf_bit = src->sf_bit;
	dest->sf_state = src->sf_state;

	// Frame state
	dest->f_sf = src->f_sf;
	dest->f_state = src->f_state;

	dest->cycle_state = src->cycle_state;
	dest->cycle = src->cycle;

	dest->bit  = src->bit;

	dest->sec  = src->sec;
	dest->rx_sec = src->rx_sec;
	dest->min  = src->min;
	dest->hour = src->hour;
	dest->day  = src->day;
	dest->year = src->year;
}

double	irigb_get_samplerate(irigb_state * ibs)
{
	return ibs->samplerate;
}

double	irigb_get_p(irigb_state * ibs)
{
	return (double)ibs->p / (256.0 * 256.0 * 256.0);
}

double	irigb_get_i(irigb_state * ibs)
{
	return (double)ibs->i / (256.0 * 256.0 * 256.0);
}

double	irigb_get_ifreq(irigb_state * ibs)
{
	return (double)ibs->ifreq / (256.0 * 256.0 * 256.0);
}

double	irigb_get_freq0(irigb_state * ibs)
{
	return (double)ibs->freq0 / (256.0 * 256.0 * 256.0);
}

double	irigb_get_freq(irigb_state * ibs)
{
	return (double)ibs->freq / (256.0 * 256.0 * 256.0);
}

double	irigb_get_phase(irigb_state * ibs)
{
	return (double)ibs->phase / (256.0 * 256.0 * 256.0);
}

void	irigb_set_phase(irigb_state * ibs, double phase)
{
	ibs->phase = (long)(phase * 256.0 * 256.0 * 256.0);
	ibs->phase &= 0xffffff;
}

double	irigb_get_pd(irigb_state * ibs)
{
	return (double)ibs->pd / (256.0 * 256.0 * 256.0);
}

unsigned int	irigb_get_ad_state(irigb_state * ibs)
{
	return ibs->ad_state;
}

double	irigb_get_ad(irigb_state * ibs)
{
	return (double)ibs->ad / (ibs->samplerate / 1000.0 / 4.0);
}

double	irigb_get_ad_prev(irigb_state * ibs)
{
	return (double)ibs->ad_prev / (ibs->samplerate / 1000.0 / 4.0);
}

double	irigb_get_ai(irigb_state * ibs)
{
	return (double)ibs->ai / (ibs->samplerate / 1000.0 / 4.0);
}

double	irigb_get_aq(irigb_state * ibs)
{
	return (double)ibs->aq / (ibs->samplerate / 1000.0 / 4.0);
}

double	irigb_get_amp_low(irigb_state * ibs)
{
	return (double)ibs->ad_low / (ibs->samplerate / 1000.0 / 4.0);
}

double	irigb_get_amp_high(irigb_state * ibs)
{
	return (double)ibs->ad_high / (ibs->samplerate / 1000.0 / 4.0);
}

unsigned int	irigb_get_am_state(irigb_state * ibs)
{
	return ibs->am_state;
}

unsigned int	irigb_get_am(irigb_state * ibs)
{
	return ibs->am;
}

unsigned int	irigb_get_pwm(irigb_state * ibs)
{
	return ibs->pwm;
}

unsigned int	irigb_get_cyclestate(irigb_state * ibs)
{
	return ibs->cycle_state;
}

unsigned int	irigb_get_cycle(irigb_state * ibs)
{
	return ibs->cycle;
}

unsigned int	irigb_get_sf_state(irigb_state * ibs)
{
	return ibs->sf_state;
}

unsigned int	irigb_get_sf_bit(irigb_state * ibs)
{
	return ibs->sf_bit;
}

unsigned int	irigb_get_f_state(irigb_state * ibs)
{
	return ibs->f_state;
}

unsigned int	irigb_get_f_sf(irigb_state * ibs)
{
	return ibs->f_sf;
}

unsigned int	irigb_get_bit(irigb_state * ibs)
{
	return ibs->bit;
}

unsigned int	irigb_get_sec(irigb_state * ibs)
{
	return ibs->sec;
}

unsigned int	irigb_get_min(irigb_state * ibs)
{
	return ibs->min;
}

unsigned int	irigb_get_hour(irigb_state * ibs)
{
	return ibs->hour;
}

unsigned int	irigb_get_day(irigb_state * ibs)
{
	return ibs->day;
}

unsigned int	irigb_get_year(irigb_state * ibs)
{
	return ibs->year;
}

unsigned int	irigb_get_rxsec(irigb_state * ibs)
{
	return ibs->rx_sec;
}

void	irigb_phase_step(irigb_state * ibs)
{
	// Update phase
	ibs->phase += ibs->freq0 + ibs->freq;

	// Update cycle
	if (ibs->phase >= PHASE_MS)
	{
		ibs->phase -= PHASE_MS;
		ibs->cycle++;
	}

	// Update bit
	if (ibs->cycle >= 10)
	{
		ibs->cycle -= 10;
		ibs->sf_bit++;
	}

	if (ibs->sf_bit >= 10)
	{
		ibs->sf_bit -= 10;
		ibs->f_sf++;
	}	

	// Update sec;
	if (ibs->f_sf >= 10)
	{
		ibs->f_sf -= 10;
		ibs->sec++;
	}
	ibs->bit = ibs->f_sf * 10 + ibs->sf_bit;

	// Update min (FIXME)
	if (ibs->sec >= 60)
	{
		ibs->sec -= 60;
		ibs->min++;
	}

	// Update hour
	if (ibs->min >= 60)
	{
		ibs->min -= 60;
		ibs->hour++;
	}

	// Update day
	if (ibs->hour >= 24)
	{
		ibs->hour -= 24;
		ibs->day++;
	}

	// Update year (FIXME)
	if (ibs->day >= 365)
	{
		ibs->day -= 365;
		ibs->year++;
	}
}

unsigned long	irigb_get_nstime(irigb_state * ibs)
{
	//int bit = ibs->f_sf * 10 + ibs->sf_bit;
	unsigned int bit = ibs->bit;
	unsigned long nstime;
	if (ibs->year < 100)
		ibs->year += 2000;

	nstime = epochtimens(ibs->year, ibs->day, ibs->hour, ibs->min, ibs->sec, (unsigned int)((double)bit*10+ibs->cycle+irigb_get_phase(ibs))*1000000);
	return nstime;
}

int	irigb_gen_step(irigb_state * ibs)
{
	unsigned int sec1, sec2, min1, min2, hour1, hour2;
	unsigned int day1, day2, day3, year1, year2;
	unsigned int binsec;
	unsigned int pwm;
	int amp;
	int amp_high;
	int amp_low;
	
	irigb_phase_step(ibs);

	// BCD encode
	sec1 = ibs->sec % 10;
	sec2 = ibs->sec / 10;
	min1 = ibs->min % 10;
	min2 = ibs->min / 10;
	hour1 = ibs->hour % 10;
	hour2 = ibs->hour / 10;
	day1 = ibs->day % 10;
	day2 = (ibs->day / 10) % 10;
	day3 = ibs->day / 100;
	year1 = ibs->year % 10;
	year2 = (ibs->year / 10) % 10;

	// Binary seconds
	binsec = ibs->hour * 3600 + ibs->min * 60 + ibs->sec;

	pwm = 0;
	switch (ibs->bit)
	{
		// Reference bit
	case 0:
		// Position identifiers
	case 9:  case 19: case 29: case 39: case 49:
	case 59: case 69: case 79: case 89: case 99:
		pwm = 2; // Sync pulse
		break;
		// Seconds BCD
	case 1:
		pwm = sec1 & 1;
		break;
	case 2:
		pwm = (sec1 >> 1) & 1;
		break;
	case 3:
		pwm = (sec1 >> 2) & 1;
		break;
	case 4:
		pwm = (sec1 >> 3) & 1;
		break;
	case 5:
		pwm = 0;
		break;
	case 6:
		pwm = sec2 & 1;
		break;
	case 7:
		pwm = (sec2 >> 1) & 1;
		break;
	case 8:
		pwm = (sec2 >> 2) & 1;
		break;
		// Min BCD
	case 10:
		pwm = min1 & 1;
		break;
	case 11:
		pwm = (min1 >> 1) & 1;
		break;
	case 12:
		pwm = (min1 >> 2) & 1;
		break;
	case 13:
		pwm = (min1 >> 3) & 1;
		break;
	case 14:
		pwm = 0;
		break;
	case 15:
		pwm = min2 & 1;
		break;
	case 16:
		pwm = (min2 >> 1) & 1;
		break;
	case 17:
		pwm = (min2 >> 2) & 1;
		break;
	case 18:
		pwm = 0;
		break;
		// Min BCD
	case 20:
		pwm = hour1 & 1;
		break;
	case 21:
		pwm = (hour1 >> 1) & 1;
		break;
	case 22:
		pwm = (hour1 >> 2) & 1;
		break;
	case 23:
		pwm = (hour1 >> 3) & 1;
		break;
	case 24:
		pwm = 0;
		break;
	case 25:
		pwm = hour2 & 1;
		break;
	case 26:
		pwm = (hour2 >> 1) & 1;
		break;
	case 27:
		pwm = 0;
		break;
	case 28:
		pwm = 0;
		break;
		// Day BCD
	case 30:
		pwm = day1 & 1;
		break;
	case 31:
		pwm = (day1 >> 1) & 1;
		break;
	case 32:
		pwm = (day1 >> 2) & 1;
		break;
	case 33:
		pwm = (day1 >> 3) & 1;
		break;
	case 34:
		pwm = 0;
		break;
	case 35:
		pwm = day2 & 1;
		break;
	case 36:
		pwm = (day2 >> 1) & 1;
		break;
	case 37:
		pwm = (day2 >> 2) & 1;
		break;
	case 38:
		pwm = (day2 >> 3) & 1;
		break;
	case 40:
		pwm = day3 & 1;
		break;
	case 41:
		pwm = (day3 >> 1) & 1;
		break;
	case 42:
		pwm = 0;
		break;
	case 43:
		pwm = 0;
		break;
	case 44:
		pwm = 0;
		break;
	case 45:
		pwm = 0;
		break;
	case 46:
		pwm = 0;
		break;
	case 47:
		pwm = 0;
		break;
	case 48:
		pwm = 0;
		break;
		// Year BCD
	case 50:
		pwm = year1 & 1;
		break;
	case 51:
		pwm = (year1 >> 1) & 1;
		break;
	case 52:
		pwm = (year1 >> 2) & 1;
		break;
	case 53:
		pwm = (year1 >> 3) & 1;
		break;
	case 54:
		pwm = 0;
		break;
	case 55:
		pwm = year2 & 1;
		break;
	case 56:
		pwm = (year2 >> 1) & 1;
		break;
	case 57:
		pwm = (year2 >> 2) & 1;
		break;
	case 58:
		pwm = (year2 >> 3) & 1;
		break;
		// Control functions
		// Straight binary seconds
	case 80:
		pwm = binsec & 1;
		break;
	case 81:
		pwm = (binsec >> 1) & 1;
		break;
	case 82:
		pwm = (binsec >> 2) & 1;
		break;
	case 83:
		pwm = (binsec >> 3) & 1;
		break;
	case 84:
		pwm = (binsec >> 4) & 1;
		break;
	case 85:
		pwm = (binsec >> 5) & 1;
		break;
	case 86:
		pwm = (binsec >> 6) & 1;
		break;
	case 87:
		pwm = (binsec >> 7) & 1;
		break;
	case 88:
		pwm = (binsec >> 8) & 1;
		break;
	case 90:
		pwm = (binsec >> 9) & 1;
		break;
	case 91:
		pwm = (binsec >> 10) & 1;
		break;
	case 92:
		pwm = (binsec >> 11) & 1;
		break;
	case 93:
		pwm = (binsec >> 12) & 1;
		break;
	case 94:
		pwm = (binsec >> 13) & 1;
		break;
	case 95:
		pwm = (binsec >> 14) & 1;
		break;
	case 96:
		pwm = (binsec >> 15) & 1;
		break;
	case 97:
		pwm = (binsec >> 16) & 1;
		break;
	case 98:
		pwm = 0;
		break;
	default:
		pwm = 0;
		break;
		
	}

	// PWM
	amp_high = 32767;
	amp_low  = 9929;
	switch (ibs->cycle)
	{
	case 0:
	case 1:
		amp = amp_high;
		break;
	case 2:
	case 3:
	case 4:
		if (pwm == 0)
			amp = amp_low;
		else
			amp = amp_high;
		break;
	case 5:
	case 6:
	case 7:
		if (pwm == 0)
			amp = amp_low;
		else if (pwm == 1)
			amp = amp_low;
		else
			amp = amp_high;
		break;
	case 8:
	case 9:
	default:
		amp = amp_low;
		break;
		
	}
	return irigb_sin(amp, ibs->phase);
}

void 	irigb_det_step(irigb_state * ibs, int sample)
{
	unsigned int	cycle;
	unsigned int	am;
	unsigned int	pwm;
	unsigned int	bit;

	// PLL
	
	// Phase detect
	ibs->pd = (sample * irigb_cos(32767, ibs->phase)) / 32768;

	cycle = ibs->cycle;

	// PI loop filter
	ibs->ifreq += ibs->pd *0.002;
	ibs->freq = ibs->ifreq + ibs->pd *0.004;

	// NCO
	irigb_phase_step(ibs);

	// Amplitude detector

	// Integrate and dump
	if ((ibs->cycle != cycle) && (ibs->cycle_state == CYCLE_LIMIT))
	{
		//ibs->ad = sqrt(ibs->aq*ibs->aq+ibs->ai*ibs->ai);
		ibs->ad = ibs->ai;
		if (ibs->ad < 0)
			ibs->ad *= -1;
		ibs->ai = 0;
		ibs->aq = 0;
	}

	// Through-zero detection alignment of cycle period
	if (ibs->cycle_state < CYCLE_LIMIT)
	{
		if ((ibs->aq < 0) && (sample >= 0))
		{
			// Rising edge
			ibs->cycle = 0;
			ibs->phase = 0;
			ibs->cycle_state++;
			ibs->sf_state = 0;
		}
		ibs->aq = sample;
		return;
	}

	// Amplitude integrator
	ibs->aq += ibs->pd;
	ibs->ai += (sample * irigb_sin(32767, ibs->phase)) / 32768;
	

	if (ibs->cycle == cycle)
		return;

	// For each new cycle... amplitude detect
	am = ibs->am;
	if (ibs->ad_state == 0)
	{
		if (ibs->ad_prev != 0)
		{
			if (ibs->ad_prev*2 < ibs->ad)
			{
				ibs->ad_low  = ibs->ad_prev;
				ibs->ad_high = ibs->ad;
				ibs->ad_state = 1;
			}
			if (ibs->ad*2 < ibs->ad_prev)
			{
				ibs->ad_low  = ibs->ad;
				ibs->ad_high = ibs->ad_prev;
				ibs->ad_state = 1;
			}
		}
	}
	else
	{
		// Build AM detector limit
		long ad_lim;
		ad_lim = (ibs->ad_low + ibs->ad_high) / 2;
		if (ibs->ad > ad_lim)
		{
			ibs->am = 1;
			ibs->ad_high += (ibs->ad - ibs->ad_high) / 16;
		}
		else
		{
			ibs->am = 0;
			ibs->ad_low += (ibs->ad - ibs->ad_low) / 16;
		}
	}
	ibs->ad_prev = ibs->ad;

	// Amplitude PWM decode
	pwm = 0;
	if (am < ibs->am)
	{
		// Rising edge
		if (ibs->ad_state > 0 && ibs->cycle != 0)
		{
			// FIXME
			ibs->cycle = 1;
			ibs->am_state = 1;
		}
		else if (ibs->ad_state > 0 && ibs->cycle == 0)
		{
			if (ibs->am_state < AM_LIMIT)
				ibs->am_state++;
		}
	}
	else if (am > ibs->am)
	{
		// Falling edge
		if (ibs->cycle -1 == 1)
			ibs->pwm = pwm = 0;
		if (ibs->cycle -1 == 4)
			ibs->pwm = pwm = 1;
		if (ibs->cycle -1 == 7)
			ibs->pwm = pwm = 2;
	}
	else
		return;

	// Subframe alignment
	if ((ibs->sf_state < SF_LIMIT) && (pwm == 2))
	{
		// While no subframe alignment and Sync-word
		if (ibs->sf_bit == 9)
		{
			ibs->sf_state++;
		}
		if ((ibs->sf_bit != 0) && (ibs->sf_bit != 9))
		{
			ibs->sf_bit = 9;
			ibs->sf_state = 0;
			ibs->f_state = 0;
		}
	}
	if ((ibs->sf_bit == 9) && (pwm != 2))
	{
		// If sub-frame bit is 9 and pwm not sync-word => loose alignment
		ibs->sf_state = 0;
	}
	
	// Frame alignment
	if ((pwm == 2) && (ibs->sf_bit == 0) && (ibs->f_state < F_LIMIT))
	{
		// While frame unaligned and Sync-word in subframe bit 0
		if (ibs->f_sf != 0)
		{
			// Force alignment on non-matching phase
			ibs->f_sf = 0;
			ibs->f_state = 0;
		}
		else
		{
			// Increase 
			ibs->f_state++;
		}
	}

	if (ibs->f_state < F_LIMIT)
		return;

	bit = ibs->f_sf * 10 + ibs->sf_bit;

	//	if (ibs->cycle != 9)
	//	return;

	// Message decoding
	pwm = 1 & ibs->pwm;
	if (cycle != 9)
		return;
	switch (bit-1)
	{
		// Reference bit
	case 0:
		// Position identifiers
	case 9:  case 19: case 29: case 39: case 49:
	case 59: case 69: case 79: case 89: case 99:
		break;
		// Seconds BCD
	case 1:
		ibs->rx_sec = pwm;
		break;
	case 2:
		ibs->rx_sec += pwm * 2;
		break;
	case 3:
		ibs->rx_sec += pwm * 4;
		break;
	case 4:
		ibs->rx_sec += pwm * 8;
		break;
	case 5:
		break;
	case 6:
		ibs->rx_sec += pwm * 10;
		break;
	case 7:
		ibs->rx_sec += pwm * 20;
		break;
	case 8:
		ibs->rx_sec += pwm * 40;
		break;
		// Min BCD
	case 10:
		ibs->min = pwm;
		break;
	case 11:
		ibs->min += pwm * 2;
		break;
	case 12:
		ibs->min += pwm * 4;
		break;
	case 13:
		ibs->min += pwm * 8;
		break;
	case 14:
		break;
	case 15:
		ibs->min += pwm * 10;
		break;
	case 16:
		ibs->min += pwm * 20;
		break;
	case 17:
		ibs->min += pwm * 40;
		break;
	case 18:
		break;
		// Hour BCD
	case 20:
		ibs->hour = pwm;
		break;
	case 21:
		ibs->hour += pwm * 2;
		break;
	case 22:
		ibs->hour += pwm * 4;
		break;
	case 23:
		ibs->hour += pwm * 8;
		break;
	case 24:
		break;
	case 25:
		ibs->hour += pwm * 10;
		break;
	case 26:
		ibs->hour += pwm * 20;
		break;
	case 27:
		break;
	case 28:
		break;
		// Day BCD
	case 30:
		ibs->day = pwm;
		break;
	case 31:
		ibs->day += pwm * 2;
		break;
	case 32:
		ibs->day += pwm * 4;
		break;
	case 33:
		ibs->day += pwm * 8;
		break;
	case 34:
		break;
	case 35:
		ibs->day += pwm * 10;
		break;
	case 36:
		ibs->day += pwm * 20;
		break;
	case 37:
		ibs->day += pwm * 40;
		break;
	case 38:
		ibs->day += pwm * 80;
		break;
	case 40:
		ibs->day += pwm * 100;
		break;
	case 41:
		ibs->day += pwm * 200;
		break;
	case 42:
		break;
	case 43:
		break;
	case 44:
		break;
	case 45:
		break;
	case 46:
		break;
	case 47:
		break;
	case 48:
		break;
		// Year BCD
	case 50:
		ibs->year = pwm + 17;
		break;
	case 51:
		ibs->year += pwm * 2;
		break;
	case 52:
		ibs->year += pwm * 4;
		break;
	case 53:
		ibs->year += pwm * 8;
		break;
	case 54:
		break;
	case 55:
		ibs->year += pwm * 10;
		break;
	case 56:
		ibs->year += pwm * 20;
		break;
	case 57:
		ibs->year += pwm * 40;
		break;
	case 58:
		ibs->year += pwm * 80;
		break;
		// Control functions
		// Straight binary seconds
	case 80:
		//pwm = binsec & 1;
		break;
	case 81:
		//pwm = (binsec >> 1) & 1;
		break;
	case 82:
		//pwm = (binsec >> 2) & 1;
		break;
	case 83:
		//pwm = (binsec >> 3) & 1;
		break;
	case 84:
		//pwm = (binsec >> 4) & 1;
		break;
	case 85:
		//pwm = (binsec >> 5) & 1;
		break;
	case 86:
		//pwm = (binsec >> 6) & 1;
		break;
	case 87:
		//pwm = (binsec >> 7) & 1;
		break;
	case 88:
		//pwm = (binsec >> 8) & 1;
		break;
	case 90:
		//pwm = (binsec >> 9) & 1;
		break;
	case 91:
		//pwm = (binsec >> 10) & 1;
		break;
	case 92:
		//pwm = (binsec >> 11) & 1;
		break;
	case 93:
		//pwm = (binsec >> 12) & 1;
		break;
	case 94:
		//pwm = (binsec >> 13) & 1;
		break;
	case 95:
		//pwm = (binsec >> 14) & 1;
		break;
	case 96:
		//pwm = (binsec >> 15) & 1;
		break;
	case 97:
		//pwm = (binsec >> 16) & 1;
		break;
	case 98:
		//pwm = 0;
		break;
	default:
		//pwm = 0;
		break;
		
	}

	if (bit != 99)
		return;
	ibs->sec = ibs->rx_sec;
}

// C method recieving the audio data from the microphone
//
// samples points to the start of the buffer
// length is the length in bytes in the buffer (Normally 2048)
// sample_rate is the sample rate in Hz from the microphone (normally 44100.0)
// bits_per_channel indicates the number of bits describing one sample (Normally 16)
// channels_per_frame number of descrete channels (Normally 1)

/*@null@*/ irigb_state * ifs_generic_rx = NULL;

void irigb_got_sample_buffer(uint8_t *samples, unsigned long length,double sample_rate, unsigned int bits_per_channel, unsigned int channels_per_frame)
{
	unsigned long 	i;
	int	bytes_per_channel;
	int	bytes_per_frame;

	if (ifs_generic_rx == NULL)
	{
		ifs_generic_rx = irigb_create();
		if (ifs_generic_rx == NULL)
			return;
		irigb_init(ifs_generic_rx, sample_rate);
		irigb_set_phase(ifs_generic_rx, 0.0);
	}

	if (bits_per_channel <= 16)
		bytes_per_channel = 2;
	else
		bytes_per_channel = 3;
	bytes_per_frame = bytes_per_channel * channels_per_frame;

	for (i = 0; i < length; i+= bytes_per_frame)
	{
		int	b0, b1, b2;
		int	sample;

		// Get bytes and build sample
		b0 = (int)samples[i];
		sample = b0;
		b1 = (int)samples[i+1];
		sample += b1 * 256;
		if (bytes_per_channel == 3)
		{
			b2 = (int)samples[i+2];
			sample += b2 * 65536;
		}

		irigb_det_step(ifs_generic_rx, sample);
	}
}
