CC   = gcc
CFLAGS = -g 
LFLAGS = -lpthread
ALL  = send_udp recv_udp

all : $(ALL)

recv_udp: recv_udp.c
	$(CC) $(CFLAGS) recv_udp.c -o recv_udp wrappers.c -ansi

send_udp: send_udp.c
	$(CC) $(CFLAGS) send_udp.c -o send_udp wrappers.c

clean:
	/bin/rm -f *.o *~ core $(ALL)
