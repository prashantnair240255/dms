/*******************************************************\
 * **
 * ** Filename SocketConnect.c
 * **
 * ** Description: Establishing connection with server which will help in concurrent transactions.
 * **
 * ** 
 * ** Copyright (c) 24/08/2012 "ABC Ltd."
 * ** All Rights Reserved
 * **
 * ** Author:
 * **    Authors Prashant Nair, Rakesh Arora
 * **
 * ** General Comments
 * **
 * **
 * ** $Header: $
 * **
 * **
 * ** $Log: $
 * **
 * \*******************************************************/


#include "sheader.h"
#include "methods.h"
#include "GlobalData.h"

pthread_t tid;
char szName[50],szPath[100];
struct sockaddr_in serv,cli;
int nPort, nSocketDesc, nAcceptedSocket,nRet;
void SocketConnect(char *argv[])
{
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
	
	ClientConnect();
	close(nSocketDesc);
}

void ClientConnect()
{
	while(1)
	{	
		int nClientSize = sizeof(cli);
		if((nAcceptedSocket=accept(nSocketDesc,(struct sockaddr *)&cli, &nClientSize))==-1)
			perror("Socket not created:");
		else
		{
			system("clear");
			printf("\nClient %d connected successfully\n-------------------------------------\n",nAcceptedSocket);
			SendMsg(nAcceptedSocket,"Input your name:");
			strcpy(szName,(char*)RecieveMsg(nAcceptedSocket));
			if(command("insert into %s values(%d, '%s')",TABLE_CLIENT,nAcceptedSocket,szName))
				printf("Error %u:%s\n",mysql_errno(conn),mysql_error(conn));
			command("commit");
			sprintf(szPath,"../User/%s",szName);
			if((mkdir(szPath,0755))==-1)
				perror("Error in creating folder:");
			if((nRet=pthread_create(&tid,NULL,TransactWithClient,(void *)nAcceptedSocket))==-1)
				perror("\nThread not created: ");
		}
	}
}
