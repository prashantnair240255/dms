#include "sheader.h"

void CleanExit(void* p_Socket)
{
	printf("Disconnecting Client-Id:%d from server...\n",(int)p_Socket);
	SendMsg((int)p_Socket,"~9");
	pthread_exit(p_Socket);
}
