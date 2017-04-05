// Standard C includes
#include <stdio.h>

// Project includes
#include "tb.h"
#include "time.h"
#include "sintab.h"

// Module include
#include "irigb.h"

// Duplicate include test
#include "irigb.h"

// Test statistics variables
TB_VAR(irigb);

void tb_irigb_sin()
{
	long	i;
	for (i = 0; i <= 255; i++)
	{
		TB_TEST_EXPECT_M_INT(irigb,irigb_sin(65536,i*65536),sin_table[i],"sin test");
	}
}

void tb_irigb_cos()
{
	long	i, phase;
	for (i = 0; i <= 255; i++)
	{
		phase = (i + 64) & 255;
		TB_TEST_EXPECT_M_INT(irigb,irigb_cos(65536,i*65536),sin_table[phase],"sin test");
	}
}

void tb_irigb_createfree()
{
	irigb_state * ibs;

	ibs = irigb_create();
	TB_TEST_EXPECT_N_PTR(irigb,ibs,NULL,"null ptr test");
	if (ibs == NULL)
	{
		irigb_free(ibs);
		return;
	}
	// Sample rate state
	TB_TEST_EXPECT_M_DBL(irigb,irigb_get_samplerate(ibs),0.0,"sample rate init");

	// PLL PI loop control parameters
	TB_TEST_EXPECT_M_DBL(irigb,irigb_get_p(ibs),0.0,"PLL P init");
	TB_TEST_EXPECT_M_DBL(irigb,irigb_get_i(ibs),0.0,"PLL I init");

	// PLL Integrator state
	TB_TEST_EXPECT_M_DBL(irigb,irigb_get_ifreq(ibs),0.0,"Integrator freq init");

	// PLL Frequency
	TB_TEST_EXPECT_M_DBL(irigb,irigb_get_freq0(ibs),0.0,"freq0init");
	TB_TEST_EXPECT_M_DBL(irigb,irigb_get_freq(ibs),0.0,"freq init");

	// PLL Phase
	TB_TEST_EXPECT_M_DBL(irigb,irigb_get_phase(ibs),0.0,"phase init");

	// Phase detector
	TB_TEST_EXPECT_M_DBL(irigb,irigb_get_pd(ibs),0.0,"phase detector init");

	// Amplitude detector
	TB_TEST_EXPECT_M_UINT(irigb,irigb_get_ad_state(ibs),0,"amplitude detector state init");
	TB_TEST_EXPECT_M_DBL(irigb,irigb_get_ad(ibs),0.0,"amplitude detector init");
	TB_TEST_EXPECT_M_DBL(irigb,irigb_get_ai(ibs),0.0,"amplitude inphase init");
	TB_TEST_EXPECT_M_DBL(irigb,irigb_get_aq(ibs),0.0,"ampliture quadraphase init");

	// Amplitude discriminator
	TB_TEST_EXPECT_M_UINT(irigb,irigb_get_am_state(ibs),0,"amplitude detector state init");
	TB_TEST_EXPECT_M_DBL(irigb,irigb_get_ad_prev(ibs),0.0,"amplitude detector state init");
	TB_TEST_EXPECT_M_DBL(irigb,irigb_get_amp_high(ibs),0.0,"amplitude detector state init");
	TB_TEST_EXPECT_M_DBL(irigb,irigb_get_amp_low(ibs),0.0,"amplitude detector state init");
	TB_TEST_EXPECT_M_UINT(irigb,irigb_get_am(ibs),0,"amplitude detector state init");
	TB_TEST_EXPECT_M_UINT(irigb,irigb_get_pwm(ibs),0,"amplitude detector state init");

	// Cycle state
	TB_TEST_EXPECT_M_UINT(irigb,irigb_get_cyclestate(ibs),0,"cycle state init");
	TB_TEST_EXPECT_M_UINT(irigb,irigb_get_cycle(ibs),0,"cycle init");

	// Subframe state
	TB_TEST_EXPECT_M_UINT(irigb,irigb_get_sf_state(ibs),0,"subframe state init");
	TB_TEST_EXPECT_M_UINT(irigb,irigb_get_sf_bit(ibs),0,"subframe init");

	// Frame state
	TB_TEST_EXPECT_M_UINT(irigb,irigb_get_f_state(ibs),0,"frame state init");
	TB_TEST_EXPECT_M_UINT(irigb,irigb_get_f_sf(ibs),0,"frame init");

	// bit state
	TB_TEST_EXPECT_M_UINT(irigb,irigb_get_bit(ibs),0,"frame init");

	// Rx time
	TB_TEST_EXPECT_M_UINT(irigb,irigb_get_rxsec(ibs),0,"Rx sec init");

	// Current time
	TB_TEST_EXPECT_M_UINT(irigb,irigb_get_sec(ibs),0,"Current sec init");
	TB_TEST_EXPECT_M_UINT(irigb,irigb_get_min(ibs),0,"Current min init");
	TB_TEST_EXPECT_M_UINT(irigb,irigb_get_hour(ibs),0,"Current hour init");
	TB_TEST_EXPECT_M_UINT(irigb,irigb_get_day(ibs),0,"Current day init");
	TB_TEST_EXPECT_M_UINT(irigb,irigb_get_year(ibs),0,"Current year init");

	// Free object
	irigb_free(ibs);
}

void tb_irigb_init_get_set()
{
	irigb_state * ibs;

	ibs = irigb_create();
	TB_TEST_EXPECT_N_PTR(irigb,ibs,NULL,"null ptr test");
	if (ibs == NULL)
	{
		irigb_free(ibs);
		return;
	}

	// Init
	irigb_init(ibs,48000.0);
	
	// Sample rate state
	TB_TEST_EXPECT_M_DBL(irigb,irigb_get_samplerate(ibs),48000.0,"sample rate init");

	// PLL PI loop control parameters
	TB_TEST_EXPECT_M_DBL(irigb,irigb_get_p(ibs),0.0,"PLL P init");
	TB_TEST_EXPECT_M_DBL(irigb,irigb_get_i(ibs),0.0,"PLL I init");

	// PLL Integrator state
	TB_TEST_EXPECT_M_DBL(irigb,irigb_get_ifreq(ibs),0.0,"Integrator freq init");

	// PLL Frequency
	TB_TEST_EXPECT_M_DBL_PREC(irigb,irigb_get_freq0(ibs),1.0/48.0,1E-6,"freq0 init");
	TB_TEST_EXPECT_M_DBL(irigb,irigb_get_freq(ibs),0.0,"freq init");

	// PLL Phase
	TB_TEST_EXPECT_M_DBL(irigb,irigb_get_phase(ibs),0.0,"phase init");
	irigb_set_phase(ibs, 0.25);
	TB_TEST_EXPECT_M_DBL(irigb,irigb_get_phase(ibs),0.25,"phase set");

	// Phase detector
	TB_TEST_EXPECT_M_DBL(irigb,irigb_get_pd(ibs),0.0,"phase detector init");

	// Amplitude detector
	TB_TEST_EXPECT_M_UINT(irigb,irigb_get_ad_state(ibs),0,"amplitude detector state init");
	TB_TEST_EXPECT_M_DBL(irigb,irigb_get_ad(ibs),0.0,"amplitude detector init");
	TB_TEST_EXPECT_M_DBL(irigb,irigb_get_ai(ibs),0.0,"amplitude inphase init");
	TB_TEST_EXPECT_M_DBL(irigb,irigb_get_aq(ibs),0.0,"ampliture quadraphase init");

	// Amplitude discriminator
	TB_TEST_EXPECT_M_UINT(irigb,irigb_get_am_state(ibs),0,"amplitude detector state init");
	TB_TEST_EXPECT_M_DBL(irigb,irigb_get_ad_prev(ibs),0.0,"amplitude detector state init");
	TB_TEST_EXPECT_M_DBL(irigb,irigb_get_amp_high(ibs),0.0,"amplitude detector state init");
	TB_TEST_EXPECT_M_DBL(irigb,irigb_get_amp_low(ibs),0.0,"amplitude detector state init");
	TB_TEST_EXPECT_M_UINT(irigb,irigb_get_am(ibs),0,"amplitude detector state init");
	TB_TEST_EXPECT_M_UINT(irigb,irigb_get_pwm(ibs),0,"amplitude detector state init");

	// Cycle state
	TB_TEST_EXPECT_M_UINT(irigb,irigb_get_cyclestate(ibs),0,"cycle state init");
	TB_TEST_EXPECT_M_UINT(irigb,irigb_get_cycle(ibs),0,"cycle init");

	// Subframe state
	TB_TEST_EXPECT_M_UINT(irigb,irigb_get_sf_state(ibs),0,"subframe state init");
	TB_TEST_EXPECT_M_UINT(irigb,irigb_get_sf_bit(ibs),0,"subframe init");

	// Frame state
	TB_TEST_EXPECT_M_UINT(irigb,irigb_get_f_state(ibs),0,"frame state init");
	TB_TEST_EXPECT_M_UINT(irigb,irigb_get_f_sf(ibs),0,"frame init");

	// bit state
	TB_TEST_EXPECT_M_UINT(irigb,irigb_get_bit(ibs),0,"frame init");

	// Rx time
	TB_TEST_EXPECT_M_UINT(irigb,irigb_get_rxsec(ibs),0,"Rx sec init");

	// Current time
	TB_TEST_EXPECT_M_UINT(irigb,irigb_get_sec(ibs),0,"Current sec init");
	TB_TEST_EXPECT_M_UINT(irigb,irigb_get_min(ibs),0,"Current min init");
	TB_TEST_EXPECT_M_UINT(irigb,irigb_get_hour(ibs),0,"Current hour init");
	TB_TEST_EXPECT_M_UINT(irigb,irigb_get_day(ibs),0,"Current day init");
	TB_TEST_EXPECT_M_UINT(irigb,irigb_get_year(ibs),0,"Current year init");

	// Init
	irigb_init_tb(ibs,44100.0);
	
	// Sample rate state
	TB_TEST_EXPECT_M_DBL(irigb,irigb_get_samplerate(ibs),44100.0,"sample rate init");

	// PLL PI loop control parameters
	TB_TEST_EXPECT_M_DBL(irigb,irigb_get_p(ibs),1.0,"PLL P init");
	TB_TEST_EXPECT_M_DBL(irigb,irigb_get_i(ibs),1.0,"PLL I init");

	// PLL Integrator state
	TB_TEST_EXPECT_M_DBL(irigb,irigb_get_ifreq(ibs),1.0,"Integrator freq init");

	// PLL Frequency
	TB_TEST_EXPECT_M_DBL_PREC(irigb,irigb_get_freq0(ibs),1000.0/44100.0,2E-6,"freq0 init");
	TB_TEST_EXPECT_M_DBL(irigb,irigb_get_freq(ibs),1.0,"freq init");

	// PLL Phase
	TB_TEST_EXPECT_M_DBL(irigb,irigb_get_phase(ibs),1.0,"phase init");

	// Phase detector
	TB_TEST_EXPECT_M_DBL(irigb,irigb_get_pd(ibs),1.0,"phase detector init");

	// Amplitude detector
	TB_TEST_EXPECT_M_UINT(irigb,irigb_get_ad_state(ibs),1,"amplitude detector state init");
	TB_TEST_EXPECT_M_DBL_PREC(irigb,irigb_get_ad(ibs),1.0,0.02,"amplitude detector init");
	TB_TEST_EXPECT_M_DBL_PREC(irigb,irigb_get_ai(ibs),1.0,0.02,"amplitude inphase init");
	TB_TEST_EXPECT_M_DBL_PREC(irigb,irigb_get_aq(ibs),1.0,0.02,"ampliture quadraphase init");

	// Amplitude discriminator
	TB_TEST_EXPECT_M_UINT(irigb,irigb_get_am_state(ibs),1,"amplitude detector state init");
	TB_TEST_EXPECT_M_DBL_PREC(irigb,irigb_get_ad_prev(ibs),1.0,0.02,"amplitude detector state init");
	TB_TEST_EXPECT_M_DBL_PREC(irigb,irigb_get_amp_high(ibs),1.0,0.02,"amplitude detector state init");
	TB_TEST_EXPECT_M_DBL_PREC(irigb,irigb_get_amp_low(ibs),1.0,0.02,"amplitude detector state init");
	TB_TEST_EXPECT_M_UINT(irigb,irigb_get_am(ibs),1,"amplitude detector state init");
	TB_TEST_EXPECT_M_UINT(irigb,irigb_get_pwm(ibs),1,"amplitude detector state init");

	// Cycle state
	TB_TEST_EXPECT_M_UINT(irigb,irigb_get_cyclestate(ibs),1,"cycle state init");
	TB_TEST_EXPECT_M_UINT(irigb,irigb_get_cycle(ibs),1,"cycle init");

	// Subframe state
	TB_TEST_EXPECT_M_UINT(irigb,irigb_get_sf_state(ibs),1,"subframe state init");
	TB_TEST_EXPECT_M_UINT(irigb,irigb_get_sf_bit(ibs),1,"subframe init");

	// Frame state
	TB_TEST_EXPECT_M_UINT(irigb,irigb_get_f_state(ibs),1,"frame state init");
	TB_TEST_EXPECT_M_UINT(irigb,irigb_get_f_sf(ibs),1,"frame init");

	// bit state
	TB_TEST_EXPECT_M_UINT(irigb,irigb_get_bit(ibs),1,"frame init");

	// Rx time
	TB_TEST_EXPECT_M_UINT(irigb,irigb_get_rxsec(ibs),1,"Rx sec init");

	// Current time
	TB_TEST_EXPECT_M_UINT(irigb,irigb_get_sec(ibs),1,"Current sec init");
	TB_TEST_EXPECT_M_UINT(irigb,irigb_get_min(ibs),1,"Current min init");
	TB_TEST_EXPECT_M_UINT(irigb,irigb_get_hour(ibs),1,"Current hour init");
	TB_TEST_EXPECT_M_UINT(irigb,irigb_get_day(ibs),1,"Current day init");
	TB_TEST_EXPECT_M_UINT(irigb,irigb_get_year(ibs),1,"Current year init");

	// Free object
	irigb_free(ibs);
}

void tb_irigb_copy()
{
	irigb_state * ibs;
	irigb_state * ibs2;

	ibs = irigb_create();
	TB_TEST_EXPECT_N_PTR(irigb,ibs,NULL,"null ptr test");
	if (ibs == NULL)
	{
		irigb_free(ibs);
		return;
	}
	ibs2 = irigb_create();
	TB_TEST_EXPECT_N_PTR(irigb,ibs2,NULL,"null ptr test");
	if (ibs2 == NULL)
	{
		irigb_free(ibs);
		irigb_free(ibs2);
		return;
	}

	// Init
	irigb_init(ibs,48000.0);
	irigb_init_tb(ibs2,44100.0);
	irigb_copy(ibs, ibs2);
	
	// Sample rate state
	TB_TEST_EXPECT_M_DBL(irigb,irigb_get_samplerate(ibs),44100.0,"sample rate init");

	// PLL PI loop control parameters
	TB_TEST_EXPECT_M_DBL(irigb,irigb_get_p(ibs),1.0,"PLL P init");
	TB_TEST_EXPECT_M_DBL(irigb,irigb_get_i(ibs),1.0,"PLL I init");

	// PLL Integrator state
	TB_TEST_EXPECT_M_DBL(irigb,irigb_get_ifreq(ibs),1.0,"Integrator freq init");

	// PLL Frequency
	TB_TEST_EXPECT_M_DBL_PREC(irigb,irigb_get_freq0(ibs),1000.0/44100.0,2E-6,"freq0 init");
	TB_TEST_EXPECT_M_DBL(irigb,irigb_get_freq(ibs),1.0,"freq init");

	// PLL Phase
	TB_TEST_EXPECT_M_DBL(irigb,irigb_get_phase(ibs),1.0,"phase init");

	// Phase detector
	TB_TEST_EXPECT_M_DBL(irigb,irigb_get_pd(ibs),1.0,"phase detector init");

	// Amplitude detector
	TB_TEST_EXPECT_M_UINT(irigb,irigb_get_ad_state(ibs),1,"amplitude detector state init");
	TB_TEST_EXPECT_M_DBL_PREC(irigb,irigb_get_ad(ibs),1.0,0.02,"amplitude detector init");
	TB_TEST_EXPECT_M_DBL_PREC(irigb,irigb_get_ai(ibs),1.0,0.02,"amplitude inphase init");
	TB_TEST_EXPECT_M_DBL_PREC(irigb,irigb_get_aq(ibs),1.0,0.02,"ampliture quadraphase init");

	// Amplitude discriminator
	TB_TEST_EXPECT_M_UINT(irigb,irigb_get_am_state(ibs),1,"amplitude detector state init");
	TB_TEST_EXPECT_M_DBL_PREC(irigb,irigb_get_ad_prev(ibs),1.0,0.02,"amplitude detector state init");
	TB_TEST_EXPECT_M_DBL_PREC(irigb,irigb_get_amp_high(ibs),1.0,0.02,"amplitude detector state init");
	TB_TEST_EXPECT_M_DBL_PREC(irigb,irigb_get_amp_low(ibs),1.0,0.02,"amplitude detector state init");
	TB_TEST_EXPECT_M_UINT(irigb,irigb_get_am(ibs),1,"amplitude detector state init");
	TB_TEST_EXPECT_M_UINT(irigb,irigb_get_pwm(ibs),1,"amplitude detector state init");

	// Cycle state
	TB_TEST_EXPECT_M_UINT(irigb,irigb_get_cyclestate(ibs),1,"cycle state init");
	TB_TEST_EXPECT_M_UINT(irigb,irigb_get_cycle(ibs),1,"cycle init");

	// Subframe state
	TB_TEST_EXPECT_M_UINT(irigb,irigb_get_sf_state(ibs),1,"subframe state init");
	TB_TEST_EXPECT_M_UINT(irigb,irigb_get_sf_bit(ibs),1,"subframe init");

	// Frame state
	TB_TEST_EXPECT_M_UINT(irigb,irigb_get_f_state(ibs),1,"frame state init");
	TB_TEST_EXPECT_M_UINT(irigb,irigb_get_f_sf(ibs),1,"frame init");

	// bit state
	TB_TEST_EXPECT_M_UINT(irigb,irigb_get_bit(ibs),1,"frame init");

	// Rx time
	TB_TEST_EXPECT_M_UINT(irigb,irigb_get_rxsec(ibs),1,"Rx sec init");

	// Current time
	TB_TEST_EXPECT_M_UINT(irigb,irigb_get_sec(ibs),1,"Current sec init");
	TB_TEST_EXPECT_M_UINT(irigb,irigb_get_min(ibs),1,"Current min init");
	TB_TEST_EXPECT_M_UINT(irigb,irigb_get_hour(ibs),1,"Current hour init");
	TB_TEST_EXPECT_M_UINT(irigb,irigb_get_day(ibs),1,"Current day init");
	TB_TEST_EXPECT_M_UINT(irigb,irigb_get_year(ibs),1,"Current year init");

	// Free object
	irigb_free(ibs);
}

void tb_irigb_phase_step()
{
	irigb_state * ibs;
	int i;

	ibs = irigb_create();
	TB_TEST_EXPECT_N_PTR(irigb,ibs,NULL,"null ptr test");
	if (ibs == NULL)
	{
		irigb_free(ibs);
		return;
	}

	// Init
	irigb_init(ibs,48000.0);
	TB_TEST_EXPECT_M_DBL(irigb,irigb_get_phase(ibs),0.0,"phase init");
	TB_TEST_EXPECT_M_UINT(irigb,irigb_get_cycle(ibs),0,"cycle init");

	// Test basic ripple conditions to the second
	for (i = 1; i <= 48*1000+1; i++)
	{
		double	t;
		irigb_phase_step(ibs);
		t = irigb_get_phase(ibs);
		t += irigb_get_cycle(ibs);
		t += irigb_get_sf_bit(ibs)*10;
		t += irigb_get_f_sf(ibs)*100;
		t += irigb_get_sec(ibs)*1000;
		TB_TEST_EXPECT_M_DBL_PREC(irigb,t,1.0*i/48.0,1E-4,"phase ramp");
	}

	// Test 

	// Free object
	irigb_free(ibs);
}

int main()
{
	TB_VAR_RESET(irigb);
	printf("Testbench for time library\n");
	tb_irigb_sin();
	tb_irigb_cos();
	tb_irigb_createfree();
	tb_irigb_init_get_set();
	tb_irigb_copy();
	tb_irigb_phase_step();
	printf("Tests %3i Fails %i\n", irigb_tb_tests, irigb_tb_fails);
	if (irigb_tb_fails != 0)
	{
		printf("ERROR: FAIL!\n");
		return -1;
	}
	printf("PASS!\n");
	return 0;
}
