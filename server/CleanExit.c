#include "sheader.h"

void CleanExit(void* p_Socket)
{
	int nSocket = (int)p_Socket;
	printf("Client %d disconnected\n-------------------------------------\n",nSocket);
	SendMsg((int)p_Socket,"~9");
	pthread_exit(p_Socket);
}
