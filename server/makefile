MYSQLCFLAGS= mysql_config --cflags
MYSQLLIBS= mysql_config --libs
$(CC)-o mysqlrun $(INCLUDES) $(MYSQLCFLAGS) mysql.c $(MYSQLLIBS)

All : server

server : server.o  transactwithclient.o SocketConnect.o SendMsg.o RecvMsg.o CleanExit.o
	gcc -o server server.o transactwithclient.o SocketConnect.o SendMsg.o RecvMsg.o CleanExit.o -lpthread

server.o : server.c sheader.h methods.h
	gcc -c server.c

SocketConnect.o : SocketConnect.c sheader.h methods.h
	gcc -c SocketConnect.c -lpthread

transactwithclient.o : transactwithclient.c sheader.h ../SocketFunc.h
	gcc -c transactwithclient.c

CleanExit.o : CleanExit.c sheader.h ../SocketFunc.h
	gcc -c CleanExit.c

SendMsg.o: ../SendMsg.c
	gcc -c  ../SendMsg.c

RecvMsg.o: ../RecvMsg.c
	gcc -c ../RecvMsg.c

clean:
	rm -rf *.o

	INCLUDES="c:\mysql\include"
	$(CC)-o mysqlrun $(INCLUDES) $(MYSQLCFLAGS) mysql.c $(MYSQLLIBS)
