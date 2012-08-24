CFLAGS=`mysql_config --cflags`
LIBS=`mysql_config --libs`

All : client

client : client.o  transactwithserv.o SendMsg.o RecvMsg.o ViewMonitoringStatus.o ClientSignalHandler.o RequestMonitor.o ShowMenu.o
	gcc -o client client.o transactwithserv.o SendMsg.o RecvMsg.o ViewMonitoringStatus.o RequestMonitor.o ClientSignalHandler.o ShowMenu.o -lpthread

client.o : client.c cheader.h methods.h ../server/methods.h
	gcc -c client.c -lpthread

transactwithserv.o : transactwithserv.c cheader.h ../SocketFunc.h
	gcc -c transactwithserv.c

ClientSignalHandler.o : ClientSignalHandler.c cheader.h methods.h
	gcc -c ClientSignalHandler.c

ViewMonitoringStatus.o : ViewMonitoringStatus.c cheader.h methods.h
	gcc -c ViewMonitoringStatus.c

RequestMonitor.o :RequestMonitor.c cheader.h methods.h
	gcc -c RequestMonitor.c

SendMsg.o: ../SendMsg.c
	gcc -c $(CFLAGS) ../SendMsg.c

RecvMsg.o: ../RecvMsg.c
	gcc -c $(CFLAGS) ../RecvMsg.c

ShowMenu.o : ShowMenu.c cheader.h methods.h
	gcc -c $(CFLAGS) ShowMenu.c

clean:
	rm -rf *.o
