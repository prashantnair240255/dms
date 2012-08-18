#include "cheader.h"
#include "../SocketFunc.h"

void TransactWithServer(int nSocket)
{
	char* cBuff;
	cBuff = (char*)malloc(500);
	ClientSignalHandler(nSocket);
	char* p_Recieved;
	while(1)
	{
		bzero(cBuff,sizeof(cBuff));
		fgets(cBuff,sizeof(cBuff)-1,stdin);
		SendMsg(nSocket,cBuff);
		p_Recieved = RecieveMsg(nSocket);
		write(1,cBuff,sizeof(cBuff));
	}
	close(nSocket);
}
