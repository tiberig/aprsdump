#define AUDIO_CAPTURE_C
#include <stdio.h>
#include <stdlib.h>
/* Use the newer ALSA API */
#define ALSA_PCM_NEW_HW_PARAMS_API
#include <alsa/asoundlib.h>

static snd_pcm_t *handle;
static snd_pcm_hw_params_t *hw_params;
static int *frame_buffer;
static snd_pcm_uframes_t frames;

//int audio_capture_init(char *audio_dev)
//{
//      int i;
//      int err, dir;
//      unsigned int rate;
//
//      if ((err = snd_pcm_open(&capture_handle, audio_dev, SND_PCM_STREAM_CAPTURE, 0)) < 0) {
//              fprintf(stderr, "cannot open audio device %s (%s)\n", audio_dev, snd_strerror(err));
//              return -1;
//      }
//
//      if ((err = snd_pcm_hw_params_malloc(&hw_params)) < 0) {
//              fprintf(stderr, "cannot allocate hardware parameter structure (%s)\n", snd_strerror(err));
//              return -1;
//      }
//
//      if ((err = snd_pcm_hw_params_any(capture_handle, hw_params)) < 0) {
//              fprintf(stderr, "cannot initialize hardware parameter structure (%s)\n", snd_strerror(err));
//              return -1;
//      }
//
//      if ((err = snd_pcm_hw_params_set_access(capture_handle, hw_params, SND_PCM_ACCESS_RW_INTERLEAVED)) < 0) {
//              fprintf(stderr, "cannot set access type (%s)\n", snd_strerror(err));
//              return -1;
//      }
//
//      if ((err = snd_pcm_hw_params_set_format(capture_handle, hw_params, SND_PCM_FORMAT_S16_LE)) < 0) {
//              fprintf(stderr, "cannot set sample format (%s)\n", snd_strerror(err));
//              return -1;
//      }
//
//      rate = 44100;
//      dir  = 0;
//      if ((err = snd_pcm_hw_params_set_rate_near(capture_handle, hw_params, &rate, &dir)) < 0) {
//              fprintf(stderr, "cannot set sample rate (%s)\n", snd_strerror(err));
//              return -1;
//      }
//
//      if ((err = snd_pcm_hw_params_set_channels(capture_handle, hw_params, 2)) < 0) {
//              fprintf(stderr, "cannot set channel count (%s)\n", snd_strerror(err));
//              return -1;
//      }
//
//      if ((err = snd_pcm_hw_params(capture_handle, hw_params)) < 0) {
//              fprintf(stderr, "cannot set parameters (%s)\n", snd_strerror(err));
//              return -1;
//      }
//
//      snd_pcm_hw_params_free(hw_params);
//
//      if ((err = snd_pcm_prepare(capture_handle)) < 0) {
//              fprintf(stderr, "cannot prepare audio interface for use (%s)\n", snd_strerror(err));
//              return -1;
//      }
//}

int audio_capture_init(char *audio_dev)
{
	unsigned int val;
	int dir, rc, size;

	/* Open PCM device for recording (capture). */
	rc = snd_pcm_open(&handle, "default", SND_PCM_STREAM_CAPTURE, 0);
	if (rc < 0) {
		fprintf(stderr, "unable to open pcm device: %s\n", snd_strerror(rc));
		return -1;
	}

	/* Allocate a hardware parameters object. */
	snd_pcm_hw_params_alloca(&hw_params);

	/* Fill it in with default values. */
	snd_pcm_hw_params_any(handle, hw_params);

	/* Set the desired hardware parameters. */

	/* Interleaved mode */
	snd_pcm_hw_params_set_access(handle, hw_params, SND_PCM_ACCESS_RW_INTERLEAVED);

	/* Signed 16-bit little-endian format */
	snd_pcm_hw_params_set_format(handle, hw_params, SND_PCM_FORMAT_S16_LE);

	/* 1 channel mono */
	snd_pcm_hw_params_set_channels(handle, hw_params, 1);

	/* 44100 bits/second sampling rate (CD quality) */
	val = 44100;
	snd_pcm_hw_params_set_rate_near(handle, hw_params, &val, &dir);

	/* Set period size to 32 frames. */
	frames = 32;
	snd_pcm_hw_params_set_period_size_near(handle, hw_params, &frames, &dir);

	/* Write the parameters to the driver */
	rc = snd_pcm_hw_params(handle, hw_params);
	if (rc < 0) {
		fprintf(stderr, "unable to set hw parameters: %s\n", snd_strerror(rc));
		return -1;
	}

	/* Use a buffer large enough to hold one period */
	snd_pcm_hw_params_get_period_size(hw_params, &frames, &dir);
	size = frames * 4;	/* 2 bytes/sample, 2 channels */
	frame_buffer = (char *) malloc(size);
	printf("- Allocated %d bytes frame buffer\n", size);

	snd_pcm_hw_params_get_period_time(hw_params, &val, &dir);

	return 0;
}

int audio_capture_read(int **buffer)
{
	int rc;

	rc = snd_pcm_readi(handle, frame_buffer, frames);
	if (rc == -EPIPE) {
		/* EPIPE means overrun */
		fprintf(stderr, "overrun occurred\n");
		snd_pcm_prepare(handle);
	} else if (rc < 0) {
		fprintf(stderr, "error from read: %s\n", snd_strerror(rc));
	} else if (rc != (int) frames) {
		fprintf(stderr, "short read, read %d frames\n", rc);
	}
	*buffer = frame_buffer;
	return rc;
}

void audio_capture_close()
{
	printf("- Release memory\n");
	free(buffer);

	printf("- Close Soundcard\n");
	snd_pcm_drain(handle);
	snd_pcm_close(handle);
}
