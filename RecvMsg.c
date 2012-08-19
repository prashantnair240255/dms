#include "SocketFunc.h"
#include "server/sheader.h"
#include "client/cheader.h"

char* RecieveMsg(int nSocket)
{
	static char cMesg[500];
	int nReturnVal;
	memset(cMesg,0,500);
	nReturnVal=recv(nSocket,cMesg,sizeof(cMesg),0);
	return cMesg;
}

