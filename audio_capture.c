#include <stdio.h>
#include <stdlib.h>
#include <alsa/asoundlib.h>

snd_pcm_t *capture_handle;
snd_pcm_hw_params_t *hw_params;
short buf[128];

int audio_capture_init(char *audio_dev)
{
	int i;
	int err, dir;
	unsigned int rate;

	if ((err = snd_pcm_open(&capture_handle, audio_dev, SND_PCM_STREAM_CAPTURE, 0)) < 0) {
		fprintf(stderr, "cannot open audio device %s (%s)\n", audio_dev, snd_strerror(err));
		return -1;
	}

	if ((err = snd_pcm_hw_params_malloc(&hw_params)) < 0) {
		fprintf(stderr, "cannot allocate hardware parameter structure (%s)\n", snd_strerror(err));
		return -1;
	}

	if ((err = snd_pcm_hw_params_any(capture_handle, hw_params)) < 0) {
		fprintf(stderr, "cannot initialize hardware parameter structure (%s)\n", snd_strerror(err));
		return -1;
	}

	if ((err = snd_pcm_hw_params_set_access(capture_handle, hw_params, SND_PCM_ACCESS_RW_INTERLEAVED)) < 0) {
		fprintf(stderr, "cannot set access type (%s)\n", snd_strerror(err));
		return -1;
	}

	if ((err = snd_pcm_hw_params_set_format(capture_handle, hw_params, SND_PCM_FORMAT_S16_LE)) < 0) {
		fprintf(stderr, "cannot set sample format (%s)\n", snd_strerror(err));
		return -1;
	}

	rate = 44100;
	dir  = 0;
	if ((err = snd_pcm_hw_params_set_rate_near(capture_handle, hw_params, &rate, &dir)) < 0) {
		fprintf(stderr, "cannot set sample rate (%s)\n", snd_strerror(err));
		return -1;
	}

	if ((err = snd_pcm_hw_params_set_channels(capture_handle, hw_params, 2)) < 0) {
		fprintf(stderr, "cannot set channel count (%s)\n", snd_strerror(err));
		return -1;
	}

	if ((err = snd_pcm_hw_params(capture_handle, hw_params)) < 0) {
		fprintf(stderr, "cannot set parameters (%s)\n", snd_strerror(err));
		return -1;
	}

	snd_pcm_hw_params_free(hw_params);

	if ((err = snd_pcm_prepare(capture_handle)) < 0) {
		fprintf(stderr, "cannot prepare audio interface for use (%s)\n", snd_strerror(err));
		return -1;
	}

	for (i = 0; i < 10; ++i) {
		if ((err = snd_pcm_readi(capture_handle, buf, 128)) != 128) {
			fprintf(stderr, "read from audio interface failed (%s)\n", snd_strerror(err));
			return -1;
		}
	}
}

void audio_capture_close()
{
	snd_pcm_close(capture_handle);
}
