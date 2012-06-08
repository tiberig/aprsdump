all:	aprsdump

aprsdump:	main.o audio_capture.o cdump.o
	gcc -o aprsdump main.o audio_capture.o cdump.o -lasound

main.o:	main.c
	gcc -c main.c -I.

audio_capture.o:	audio_capture.c
	gcc -c audio_capture.c -I.

cdump.o:	cdump.c
	gcc -c cdump.c -I.
	
clean:
	rm -f *.o aprsdump
