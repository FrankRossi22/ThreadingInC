all: createThreads parallel1 parallel2 parallel3

#lab: .o
#	gcc -o lab .o

#.o: .c
#	gcc -c .c


createThreads: createThreads.o
	gcc -o createThreads  createThreads.o -lpthread

createThreads.o: createThreads.c
	gcc -c createThreads.c 

parallel1: parallel1.o
	gcc -o parallel1 parallel1.o -lpthread

parallel1.o: parallel1.c
	gcc -c parallel1.c

parallel2: parallel2.o
	gcc -o parallel2 parallel2.o -lpthread

parallel2.o: parallel2.c
	gcc -c parallel2.c

parallel3: parallel3.o
	gcc -o parallel3 parallel3.o -lpthread

parallel3.o: parallel3.c
	gcc -c parallel3.c

clean: 
	rm -rf *.o parallel1 parallel2 parallel3 createThreads
