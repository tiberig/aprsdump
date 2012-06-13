LD=gcc
CC=gcc

CFLAGS=-Wall -I.
LDFLAGS=

all:	aprsdump

aprsdump:	main.o audio_capture.o cdump.o audiometer.o
	$(LD) $(LDFLAGS) -o aprsdump main.o audio_capture.o cdump.o  audiometer.o -lasound -lm

main.o:	main.c
	$(CC) $(CFLAGS) -c main.c

audio_capture.o:	audio_capture.c
	$(CC) $(CFLAGS) -c audio_capture.c 

cdump.o:	cdump.c
	$(CC) $(CFLAGS) -c cdump.c
	
audiometer.o:	audiometer.c
	$(CC) $(CFLAGS) -c audiometer.c
	
clean:
	rm -f *.o aprsdump
	make -C multimon clean
