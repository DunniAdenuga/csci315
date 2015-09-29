all: echod echoreq echoreq2

echod: echod.c wrappers.c
	gcc -o echod echod.c wrappers.c

echoreq: echoreq.c wrappers.c
	gcc -o echoreq echoreq.c wrappers.c 
echoreq2: echoreq2.c wrappers.c
	gcc -o echoreq2 echoreq2.c wrappers.c 

clean:
	$(RM) echod echoreq echoreq2