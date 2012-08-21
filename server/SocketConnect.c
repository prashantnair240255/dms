#include "sheader.h"
#include "methods.h"

pthread_t tid;
void SocketConnect(char *argv[])
{
	struct sockaddr_in serv,cli;
	int nPort, nSocketDesc, nAcceptedSocket,nRet;
	nPort = atoi(argv[1]);
	nSocketDesc = socket(AF_INET,SOCK_STREAM,0);
	serv.sin_family = AF_INET;
	serv.sin_addr.s_addr = INADDR_ANY;
	serv.sin_port = htons(nPort);
	bind(nSocketDesc,(struct sockaddr *)&serv,sizeof(serv));
	listen(nSocketDesc,5);
	printf("\n===========================\n");
	printf("Waiting for connection\n");
	printf("===========================\n\n");
	while(1)
	{	
		int nClientSize = sizeof(cli);
		if((nAcceptedSocket=accept(nSocketDesc,(struct sockaddr *)&cli, &nClientSize))==-1)
			perror("Socket not created:");
		else
		{
			printf("\nClient %d connected successfully\n-------------------------------------\n",nAcceptedSocket);
			if((nRet=pthread_create(&tid,NULL,TransactWithClient,(void *)nAcceptedSocket))==-1)
				perror("\nThread not created: ");
		}
	}
	close(nSocketDesc);
}
