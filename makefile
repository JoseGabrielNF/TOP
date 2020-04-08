all:		 
	gcc -c mytop.c -I ./h -o mytop.o
	gcc -c getuserid.c -I ./h -o getuserid.o
	gcc -c getusername.c -I ./h -o getusername.o
	gcc -c getstat.c -I ./h -o getstat.o
	gcc -c getprocpid.c -I ./h -o getprocpid.o
	gcc mytop.o getuserid.o getusername.o getstat.o getprocpid.o -o ./mytop -lncurses
	./mytop

run:
	./mytop

teste:
	gcc teste.c -o teste -lncurses
	./teste 
	
rm:
	rm *.o