#include "sheader.h"
#include "methods.h"

void ServerSignalHandler()
{
	struct sigaction action = { SigHandler };
	if(sigaction(SIGINT,&action,NULL))
		perror("Signal no: ");
}

void SigHandler(int nSigNo)
{
	system("clear");
}
