CFLAGS=`mysql_config --cflags`
LIBS=`mysql_config --libs`

All : server

server : server.o  transactwithclient.o Command.o ViewMonitoringStatus.o CheckStatus.o MakeLogFiles.o StartMonitor.o ServerSignalHandler.o SocketConnect.o DatabaseConnect.o SendMsg.o RecvMsg.o CleanExit.o RequestMonitor.o
	gcc -o server server.o transactwithclient.o Command.o MakeLogFiles.o ViewMonitoringStatus.o CheckStatus.o StartMonitor.o ServerSignalHandler.o SocketConnect.o DatabaseConnect.o SendMsg.o RecvMsg.o CleanExit.o RequestMonitor.o $(LIBS) -lpthread

server.o : server.c sheader.h methods.h
	gcc -c $(CFLAGS) server.c

Command.o : Command.c sheader.h methods.h GlobalData.h
	gcc -c $(CFLAGS) Command.c

CheckStatus.o : CheckStatus.c sheader.h methods.h GlobalData.h
	gcc -c $(CFLAGS) CheckStatus.c

MakeLogFiles.o : MakeLogFiles.c sheader.h methods.h GlobalData.h
	gcc -c $(CFLAGS) MakeLogFiles.c

StartMonitor.o : StartMonitor.c sheader.h methods.h GlobalData.h
	gcc -c $(CFLAGS) StartMonitor.c

ServerSignalHandler.o : ServerSignalHandler.c sheader.h methods.h
	gcc -c $(CFLAGS) ServerSignalHandler.c

ViewMonitoringStatus.o : ViewMonitoringStatus.c sheader.h methods.h GlobalData.h
	gcc -c $(CFLAGS) ViewMonitoringStatus.c 

RequestMonitor.o : RequestMonitor.c sheader.h methods.h
	gcc -c $(CFLAGS) RequestMonitor.c

SocketConnect.o : SocketConnect.c sheader.h methods.h
	gcc -c $(CFLAGS) SocketConnect.c -lpthread

DatabaseConnect.o : DatabaseConnect.c sheader.h GlobalData.h
	gcc -c $(CFLAGS) DatabaseConnect.c

transactwithclient.o : transactwithclient.c sheader.h ../SocketFunc.h methods.h
	gcc -c $(CFLAGS) transactwithclient.c

CleanExit.o : CleanExit.c sheader.h ../SocketFunc.h
	gcc -c $(CFLAGS) CleanExit.c

SendMsg.o: ../SendMsg.c
	gcc -c $(CFLAGS) ../SendMsg.c

RecvMsg.o: ../RecvMsg.c
	gcc -c $(CFLAGS) ../RecvMsg.c

clean:
	rm -rf *.o
