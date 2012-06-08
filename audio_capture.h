#ifndef AUDIO_CAPTURE_H
#define AUDIO_CAPTURE_H

int audio_capture_init(char *audio_dev);
int audio_capture_read(int *buffer, int size);
void audio_capture_close();

#endif
