#include <stdio.h>
#include <stdlib.h>
#include <alsa/asoundlib.h>

#include "time.h"
#include "irigb.h"
	      
int main (int argc, char *argv[])
{
	int i;
	int err;
	short buf[128*2];
	snd_pcm_t *capture_handle;
	snd_pcm_hw_params_t *hw_params;

	// Setup sample frequency
	double	y_s = -8.460E-6;
	double	f_0 = 44100.0;
	double	f_s = f_0*(1-y_s);

	irigb_state *is_det;

	int sample;
	int j;

	if (argc != 2)
		exit (1);
	
	if ((err = snd_pcm_open (&capture_handle, argv[1], SND_PCM_STREAM_CAPTURE, 0)) < 0) {
		fprintf (stderr, "cannot open audio device %s (%s)\n", 
			 argv[1],
			 snd_strerror (err));
		exit (1);
	}
		   
	if ((err = snd_pcm_hw_params_malloc (&hw_params)) < 0) {
		fprintf (stderr, "cannot allocate hardware parameter structure (%s)\n",
			 snd_strerror (err));
		exit (1);
	}
				 
	if ((err = snd_pcm_hw_params_any (capture_handle, hw_params)) < 0) {
		fprintf (stderr, "cannot initialize hardware parameter structure (%s)\n",
			 snd_strerror (err));
		exit (1);
	}
	
	if ((err = snd_pcm_hw_params_set_access (capture_handle, hw_params, SND_PCM_ACCESS_RW_INTERLEAVED)) < 0) {
		fprintf (stderr, "cannot set access type (%s)\n",
			 snd_strerror (err));
		exit (1);
	}
	
	if ((err = snd_pcm_hw_params_set_format (capture_handle, hw_params, SND_PCM_FORMAT_S16_LE)) < 0) {
		fprintf (stderr, "cannot set sample format (%s)\n",
			 snd_strerror (err));
		exit (1);
	}

	unsigned int sr = 44100;
	unsigned int * srp = (unsigned int *)&sr;
	if ((err = snd_pcm_hw_params_set_rate_near (capture_handle, hw_params, srp, 0)) < 0) {
		fprintf (stderr, "cannot set sample rate (%s)\n",
			 snd_strerror (err));
		exit (1);
	}
	
	if ((err = snd_pcm_hw_params_set_channels (capture_handle, hw_params, 2)) < 0) {
		fprintf (stderr, "cannot set channel count (%s)\n",
			 snd_strerror (err));
		exit (1);
	}
	
	if ((err = snd_pcm_hw_params (capture_handle, hw_params)) < 0) {
		fprintf (stderr, "cannot set parameters (%s)\n",
			 snd_strerror (err));
		exit (1);
	}
	
	snd_pcm_hw_params_free (hw_params);
	
	if ((err = snd_pcm_prepare (capture_handle)) < 0) {
		fprintf (stderr, "cannot prepare audio interface for use (%s)\n",
			 snd_strerror (err));
		exit (1);
	}

	is_det = irigb_create();
	irigb_init(is_det, f_s);
	irigb_set_phase(is_det, 0.0);
	sample = 0;
	
	for (i = 0; i < 10000000; ++i) {
		if ((err = snd_pcm_readi (capture_handle, buf, 128)) != 128) {
			fprintf (stderr, "read from audio interface failed (%s)\n",
				 snd_strerror (err));
			exit (1);
		}
		
		for (j = 0; j < 128; j++)
		{
			unsigned int	cycle_delayed;
			unsigned int	prev_sec;

			sample = buf[2*j];
			irigb_det_step(is_det, sample);

			// Only once per cycle
			if (cycle_delayed == irigb_get_cycle(is_det))
				continue;
			cycle_delayed = irigb_get_cycle(is_det);
			// Only once per bit
			if (cycle_delayed != 9)
				continue;

			if ((irigb_get_bit(is_det) == 99) && (irigb_get_cycle(is_det) == 9) && (prev_sec != irigb_get_sec(is_det)))
			{
				int year, doy;
				year = irigb_get_year(is_det);
				doy  = irigb_get_day(is_det);
				printf("%+6i ", sample);
				printf("%4i %3i %2i %2i %2i:%02i:%02i %02i %li %+e %+e\n", year, doy, doy2month(year, doy), doy2dom(year, doy), irigb_get_hour(is_det), irigb_get_min(is_det), irigb_get_sec(is_det), irigb_get_rxsec(is_det), irigb_get_nstime(is_det), irigb_get_pd(is_det), irigb_get_freq(is_det));
				prev_sec = irigb_get_sec(is_det);
			}
		
			cycle_delayed = irigb_get_cycle(is_det);
		}
	}
	irigb_free(is_det);
	
	snd_pcm_close (capture_handle);
	exit (0);
}
