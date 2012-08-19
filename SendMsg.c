#include "SocketFunc.h"
#include "server/sheader.h"
#include "client/cheader.h"
	
int SendMsg(int nSocketDesc,char * p_Buff)
{
	char cMsg[500];
	memset(cMsg,0,500);
	strcpy(cMsg,p_Buff);
	int ret = send(nSocketDesc,cMsg,sizeof(cMsg),0);
	return ret;
}
