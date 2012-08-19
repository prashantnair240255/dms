#include "sheader.h"

void CleanExit(void* p_Socket)
{
	printf("Disconnected\n");
	SendMsg((int)p_Socket,"~9");
	pthread_exit(p_Socket);
}
