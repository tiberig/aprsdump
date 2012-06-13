CFLAGS=-Wall
LDFLAGS=-r -lm

all:	multimon.o

multimon.o:	costabf.o demod_afsk12.o hdlc.o
	$(LD) $(LDFLAGS) costabf.o demod_afsk12.o hdlc.o -o multimon.o

demod_afsk12.o:	demod_afsk12.c
	$(CC) $(CFLAGS) -c demod_afsk12.c

hdlc.o:	hdlc.c
	$(CC) $(CFLAGS) -c hdlc.c

costab.o:	costab.c
	$(CC) $(CFLAGS) -c costab.c

clean:
	rm -f *.o
