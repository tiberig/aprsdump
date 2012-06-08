all:	aprsdump

aprsdump:	main.o audio_capture.o cdump.o audiometer.o
	gcc -o aprsdump main.o audio_capture.o cdump.o  audiometer.o -lasound

main.o:	main.c
	gcc -c main.c -I.

audio_capture.o:	audio_capture.c
	gcc -c audio_capture.c -I.

cdump.o:	cdump.c
	gcc -c cdump.c -I.
	
audiometer.o:	audiometer.c
	gcc -c audiometer.c -I.
	
clean:
	rm -f *.o aprsdump
