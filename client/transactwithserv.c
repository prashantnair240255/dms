#include "cheader.h"
#include "../SocketFunc.h"

void TransactWithServer(int nSocket)
{
	char cBuff[500];
	ClientSignalHandler(nSocket);
	char* p_Recieved;
	while(1)
	{
		ShowMenu(nSocket);
		bzero(cBuff,sizeof(cBuff));
		fgets(cBuff,sizeof(cBuff),stdin);
		SendMsg(nSocket,cBuff);
		sleep(1);
		p_Recieved = RecieveMsg(nSocket);
		printf("Message from Server: %s\n",p_Recieved);
	}
	close(nSocket);
}
