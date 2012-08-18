#include "sheader.h"
#include "methods.h"

void ServerSignalHandler(int sig)
{
	printf("\nrecieved signal = %d\n",sig);
}
