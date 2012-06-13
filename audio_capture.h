#ifndef AUDIO_CAPTURE_H
#define AUDIO_CAPTURE_H

#ifndef AUDIO_CAPTURE_C
extern char *frame_buffer;
#endif

int audio_capture_init(char *audio_dev);
int audio_capture_read(int **buffer);
void audio_capture_close();

#endif
