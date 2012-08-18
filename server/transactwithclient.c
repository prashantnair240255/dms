#include "sheader.h"
#include "../SocketFunc.h"
#include "methods.h"

void* TransactWithClient(void* vSocket)
{
	char* p_Buff;
	p_Buff = (char*)malloc(500);
	int nRecieved;
	int nSocket = (int)vSocket;
	bzero(p_Buff,sizeof(p_Buff));
	do
	{	
		if(!strcmp(p_Buff,"~2"))
		{
			CleanExit((void*)nSocket);
		}		
		else
		{	
			write(1,p_Buff,strlen(p_Buff));
			SendMsg(nSocket,p_Buff);
		}
	} while((p_Buff = RecieveMsg(nSocket))!=NULL);
}
