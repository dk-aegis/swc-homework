all: chall

chall: main.o alloc.o
	gcc -Wno-deprecreated-declarations -fno-stack-protector -z execstack -no-pie -o chall main.o alloc.o

main.o: main.c alloc.h
	gcc -c main.c 

alloc.o: alloc.c
	gcc -c alloc.c 


clean:
	rm *.o chall