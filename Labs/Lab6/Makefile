CC   = gcc
CFLAGS = -g 
LFLAGS = -lpthread
ALL  = send_udp recv_udp fileserver getstats getfile ugetfile ugetstats ufileserver

all : $(ALL)

wrappers.o: wrappers.h wrappers.c 
	$(CC) $(CFLAGS) -c wrappers.c -o wrappers.o

readwrite.o: readwrite.h readwrite.c 
	$(CC) $(CFLAGS) -c readwrite.c -o readwrite.o

recv_udp: recv_udp.c wrappers.c
	$(CC) $(CFLAGS) recv_udp.c -o recv_udp wrappers.c -ansi

send_udp: send_udp.c wrappers.c
	$(CC) $(CFLAGS) send_udp.c -o send_udp wrappers.c

getfile: getfile.c wrappers.c readwrite.c
	$(CC) $(CFLAGS) -o getfile getfile.c readwrite.c wrappers.c

getstats: getstats.c wrappers.c readwrite.c
	$(CC) $(CFLAGS) -o getstats getstats.c readwrite.c wrappers.c

fileserver: fileserver.c wrappers.c readwrite.c
	$(CC) $(CFLAGS) -o fileserver fileserver.c readwrite.c wrappers.c $(LFLAGS)
ufileserver: ufileserver.c wrappers.c readwrite.c
	$(CC) $(CFLAGS) -o ufileserver ufileserver.c readwrite.c wrappers.c $(LFLAGS)
ugetstats: ugetstats.c wrappers.c readwrite.c
	$(CC) $(CFLAGS) -o ugetstats ugetstats.c readwrite.c wrappers.c $(LFLAGS)
ugetfile: ugetfile.c wrappers.c readwrite.c
	$(CC) $(CFLAGS) -o ugetfile ugetfile.c readwrite.c wrappers.c $(LFLAGS)

clean:

	/bin/rm -f *.o *~ core $(ALL)
