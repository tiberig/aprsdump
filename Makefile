all:	aprsdump

aprsdump:	main.o audio_capture.o
	gcc -o aprsdump main.o audio_capture.o -lasound

main.o:	main.c
	gcc -c main.c -I.

audio_capture.o:	audio_capture.c
	gcc -c audio_capture.c -I.

	
clean:
	rm -f *.o aprsdump
