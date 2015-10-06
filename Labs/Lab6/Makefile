CC   = gcc
CFLAGS = -g 
LFLAGS = -lpthread
ALL  = send_udp recv_udp fileserver getstats getfile

all : $(ALL)

wrappers.o: wrappers.h wrappers.c 
	$(CC) $(CFLAGS) -c wrappers.c -o wrappers.o

readwrite.o: readwrite.h readwrite.c 
	$(CC) $(CFLAGS) -c readwrite.c -o readwrite.o

recv_udp: recv_udp.c wrappers.c
	$(CC) $(CFLAGS) recv_udp.c -o recv_udp wrappers.o -ansi

send_udp: send_udp.c wrappers.c
	$(CC) $(CFLAGS) send_udp.c -o send_udp wrappers.o

getfile: getfile.c wrappers.c readwrite.c
	$(CC) $(CFLAGS) -o getfile getfile.c readwrite.o wrappers.o

getstats: getstats.c wrappers.c readwrite.c
	$(CC) $(CFLAGS) -o getstats getstats.c readwrite.o wrappers.o

fileserver: fileserver.c wrappers.c readwrite.c
	$(CC) $(CFLAGS) -o fileserver fileserver.c readwrite.o wrappers.o
clean:

	/bin/rm -f *.o *~ core $(ALL)
