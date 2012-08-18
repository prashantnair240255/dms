All : client

client : client.o  transactwithserv.o SendMsg.o RecvMsg.o ClientSignalHandler.o 
	gcc -o client client.o transactwithserv.o SendMsg.o RecvMsg.o ClientSignalHandler.o -lpthread

client.o : client.c cheader.h methods.h ../server/methods.h
	gcc -c client.c -lpthread

transactwithserv.o : transactwithserv.c cheader.h ../SocketFunc.h
	gcc -c transactwithserv.c

ClientSignalHandler.o : ClientSignalHandler.c cheader.h methods.h
	gcc -c ClientSignalHandler.c

SendMsg.o: ../SendMsg.c
	gcc -c  ../SendMsg.c

RecvMsg.o: ../RecvMsg.c
	gcc -c ../RecvMsg.c

clean:
	rm -rf *.o
