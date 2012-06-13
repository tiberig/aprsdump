#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>

#include "audio_capture.h"
#include "audiometer.h"
#include "cdump.h"

static void  sig_int_handler(int sig);
static char *audio_dev = "";
static int   run = 1;
static int  *aubuf;

int main(int argc, char *argv[])
{
	int rc, rdnum;
	printf("APRSDUMP V1.0, Stefan Koch <s-koch@gmx.net>\n");

	if (2 != argc) {
		printf("need sound device\n");
		return EXIT_FAILURE;
	}
	audio_dev = strdup(argv[1]);
	//audio_dev = strdup("plughw:0,0");

	printf("- init audio capture\n");
	printf("  + audio device = %s\n", audio_dev);
	rc = audio_capture_init(audio_dev);
	if (0 == rc) {
		printf("  + init sucess\n");
	} else {
		printf("  + init failed (%d)\n", rc);
		return EXIT_FAILURE;
	}
	
	/* register sigint handler */
	printf("- register sigint handler\n");
	signal(SIGINT, sig_int_handler);

	/* start decoder loop */
	while (1 == run) {
		rdnum = audio_capture_read(&aubuf);
		if (-1 == rdnum) break;
	//	cdump(aubuf, rdnum);
		cbar(audiometer(aubuf, rdnum));
	}

	printf("- shutdown audio capture\n");
	audio_capture_close();

	return 0;
}

void sig_int_handler(int sig)
{
	run = 0;
}
