#include "sheader.h"
#include "../SocketFunc.h"
#include "methods.h"

void* TransactWithClient(void* vSocket)
{
	char *p_Buff;
	p_Buff = (char*)malloc(500);
	int nSocket = (int)vSocket;
	bzero(p_Buff,sizeof(p_Buff));

	while(strcpy(p_Buff,RecieveMsg(nSocket))!=NULL){
		sleep(1);
		printf("Message from Client %d: ",nSocket);
		if(!strcmp(p_Buff,"~2"))
		{
			CleanExit((void*)nSocket);
		}		
		else if(!strcmp(p_Buff,"1"))
		{	
			printf("Request Monitor\n");
		}
		else if(!strcmp(p_Buff,"2"))
		{	
			printf("View Monitoring Status\n");
		}
		else if(!strcmp(p_Buff,"3"))
		{	
			printf("Exit\n");
		}
	}
}
