#include "cheader.h"
#include "methods.h"
#include "../SocketFunc.h"

int nSocketNo;
char* p_SendSig;
void ClientSignalHandler(int nSocket)
{
	nSocketNo = nSocket;
	struct sigaction action = { SigHandler };
	sigaction(SIGINT,&action,NULL);
}

void SigHandler(int nSigNo)
{
	printf("\nRecieved Signal = %d\n",nSigNo);
	SendMsg(nSocketNo,"~2");
	while(1)
	{
		if(!strcmp(RecieveMsg(nSocketNo),"~9"))
			exit(0);
	}
}
