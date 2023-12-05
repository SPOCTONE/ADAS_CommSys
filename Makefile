all: menu.o CAS.o CASalert.o LDW.o ACC.o ACCreceive.o client.o server.o CASclient.o CASserver.o BSD.o BSDalert.o

	gcc menu.o -o menu
	gcc CAS.o -o CAS
	gcc CASalert.o -o CASalert
	gcc LDW.o -o LDW
	gcc ACC.o -o ACC
	gcc ACCreceive.o -o ACCreceive
	gcc CASclient.o -o CASclient
	gcc CASserver.o -o CASserver
	gcc client.o -o client
	gcc server.o -o server
	gcc BSD.o -o BSD
	gcc BSDalert.o -o BSDalert
	./menu

menu.o: menu.c
	gcc -c menu.c

CAS.o:	CAS.c	
	gcc -c CAS.c

CASalert.o: CASalert.c
	gcc -c CASalert.c 

LDW.o:	LDW.c
	gcc -c LDW.c 

ACC.o:	ACC.c
	gcc -c ACC.c

ACCreceive.o: ACCreceive.c
	gcc -c ACCreceive.c

CASclient.o: CASclient.c
	gcc -c CASclient.c

CASserver.o: CASserver.c 
	gcc -c CASserver.c

client.o: client.c
	gcc -c client.c

server.o: server.c 
	gcc -c server.c

BSD.o:  BSD.c 
	gcc -c BSD.c

BSDalert.o: BSDalert.c
	gcc -c BSDalert.c

clean:
	rm *.o