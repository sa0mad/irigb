// Standard C includes
#include <stdint.h>

typedef struct irigb_state irigb_state;

extern int 	irigb_sin(int amp, long phase);
extern int 	irigb_cos(int amp, long phase);

// IRIGB struct lifetime
/*@null@*/ extern irigb_state * irigb_create();
extern void	irigb_free(/*@null@*/ irigb_state * ibs);
extern void	irigb_init(irigb_state * ibs, double samplerate);
extern void	irigb_init_tb(irigb_state * ibs, double samplerate);
extern void	irigb_copy(irigb_state * dest, irigb_state * src);

// Access state

// Sampe rate
extern double		irigb_get_samplerate(irigb_state * ibs);

// PLL PI control
extern double		irigb_get_p(irigb_state * ibs);
extern double		irigb_get_i(irigb_state * ibs);

// PLL Integrator state
extern double		irigb_get_ifreq(irigb_state * ibs);

// PLL Frequency
extern double		irigb_get_freq0(irigb_state * ibs);
extern double		irigb_get_freq(irigb_state * ibs);

// PLL Phase
extern double		irigb_get_phase(irigb_state * ibs);
extern void		irigb_set_phase(irigb_state * ibs, double phase);

// Phase detector
extern double		irigb_get_pd(irigb_state * ibs);

// Amplitude detector
extern unsigned int	irigb_get_ad_state(irigb_state * ibs);
extern double		irigb_get_ad(irigb_state * ibs);
extern double		irigb_get_ad_prev(irigb_state * ibs);
extern double		irigb_get_ai(irigb_state * ibs);
extern double		irigb_get_aq(irigb_state * ibs);

// Amplitude discriminator
extern unsigned int	irigb_get_am_state(irigb_state * ibs);
extern double		irigb_get_amp_low(irigb_state * ibs);
extern double		irigb_get_amp_high(irigb_state * ibs);
extern unsigned int	irigb_get_am(irigb_state * ibs);
extern unsigned int	irigb_get_pwm(irigb_state * ibs);

// Cycle state
extern unsigned int	irigb_get_cyclestate(irigb_state * ibs);
extern unsigned int	irigb_get_cycle(irigb_state * ibs);

// Subframe state
extern unsigned int	irigb_get_sf_state(irigb_state * ibs);
extern unsigned int	irigb_get_sf_bit(irigb_state * ibs);

// Frame state
extern unsigned int	irigb_get_f_state(irigb_state * ibs);
extern unsigned int	irigb_get_f_sf(irigb_state * ibs);

// Bit state
extern unsigned int	irigb_get_bit(irigb_state * ibs);

// Rx time
extern unsigned int	irigb_get_rxsec(irigb_state * ibs);

// Current time
extern unsigned int	irigb_get_sec(irigb_state * ibs);
extern unsigned int	irigb_get_min(irigb_state * ibs);
extern unsigned int	irigb_get_hour(irigb_state * ibs);
extern unsigned int	irigb_get_day(irigb_state * ibs);
extern unsigned int	irigb_get_year(irigb_state * ibs);

extern void	irigb_phase_step(irigb_state * ibs);
extern int	irigb_gen_step(irigb_state * ibs);
extern void 	irigb_det_step(irigb_state * ibs, int sample);

extern unsigned long	irigb_get_nstime(irigb_state * ibs);

// Got Sample Buffer interface

/*@null@*/ extern irigb_state * ifs_generic_rx;
extern void irigb_got_sample_buffer(uint8_t *samples, unsigned long length,double sample_rate, unsigned int bits_per_channel, unsigned int channels_per_frame);
