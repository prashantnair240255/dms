#include "SocketFunc.h"
#include "server/sheader.h"
#include "client/cheader.h"

char* RecieveMsg(int nSocket)
{
	static char cMsg[500];
	int nReturnVal;
	memset(cMsg,0,500);
	nReturnVal=recv(nSocket,cMsg,sizeof(cMsg),0);
	return cMsg;
}

