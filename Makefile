CC=gcc
CFLAGS=-g

mykernel : boot.o cpu.o interpreter.o kernel.o pcb.o ram.o shell.o shellmemory.o
	$(CC) $(CFLAGS) -o mykernel *.o

boot.o : boot.c 
	$(CC) -c $(CFLAGS) boot.c

cpu.o : cpu.c 
	$(CC) -c $(CFLAGS) cpu.c

interpreter.o : interpreter.c
	$(CC) -c $(CFLAGS) interpreter.c 

kernel.o : kernel.c 
	$(CC) -c $(CFLAGS) kernel.c 

pcb.o : pcb.c 
	$(CC) -c $(CFLAGS) pcb.c 

ram.o : ram.c 
	$(CC) -c $(CFLAGS) ram.c 

shell.o : shell.c
	$(CC) -c $(CFLAGS) shell.c 

shellmemory.o : shellmemory.c
	$(CC) -c $(CFLAGS) shellmemory.c 

.PHONY:
clean:
	rm -f *.o
	rm -f mykernel

.PHONY:
test: mykernel
	./mykernel < TESTFILE.txt