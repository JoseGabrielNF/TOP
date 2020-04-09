all:		 
	gcc -c -g mytop.c -I ./h -o mytop.o
	gcc -c -g getuserid.c -I ./h -o getuserid.o
	gcc -c -g getusername.c -I ./h -o getusername.o
	gcc -c -g getstat.c -I ./h -o getstat.o
	gcc -c -g getprocpid.c -I ./h -o getprocpid.o
	gcc -c -g compara.c -I ./h -o compara.o
	gcc -c -g lertecla.c -I ./h -o lertecla.o
	gcc mytop.o getuserid.o getusername.o getstat.o getprocpid.o compara.o lertecla.o -o ./mytop -lncurses
	
run:
	./mytop

teste:
	gcc teste.c -o teste -lncurses
	./teste 
	
rm:
	rm *.o