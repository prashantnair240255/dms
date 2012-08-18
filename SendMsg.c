#include "SocketFunc.h"
#include "server/sheader.h"
#include "client/cheader.h"
	
int SendMsg(int nSocketDesc,char * p_Buff)
{
	char cMsg[1000];
	memset(cMsg,0,1000);
	strcpy(cMsg,p_Buff);
	return(send(nSocketDesc,cMsg,strlen(p_Buff),0));
}
