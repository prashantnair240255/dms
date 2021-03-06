/*******************************************************\
 * **
 * ** Filename TransactWithClient.c
 * **
 * ** Description: Server transacting with client.
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
#include "../SocketFunc.h"

void* TransactWithClient(void* vSocket)
{
	char *pBuff;
	pBuff = (char*)malloc(500);
	int nCSocket = (int)vSocket;
	bzero(pBuff,sizeof(pBuff));

	while(strcpy(pBuff,RecieveMsg(nCSocket))!=NULL){
		sleep(1);
		if(!strcmp(pBuff,"~2"))
		{
			CleanExit((void*)nCSocket);
		}		
		else if(!strcmp(pBuff,"1"))
		{	
			printf("Message from Client %d: ",nCSocket);
			RequestMonitor(nCSocket);
		}
		else if(!strcmp(pBuff,"2"))
		{	
			printf("Message from Client %d: ",nCSocket);
			ViewMonitoringStatus(nCSocket);
		}
		else if(!strcmp(pBuff,"3"))
		{	
			printf("Message from Client %d: ",nCSocket);
			Exit((void*)nCSocket);
		}
	}
}

void Exit(void* pSocket){
	int nSocket = (int)pSocket;
	printf("Client %d disconnected\n-------------------------------------\n",nSocket);
	if(command("delete from %s where client_id=%d",TABLE_CLIENT,nSocket))
		printf("Error %u:%s\n",mysql_errno(conn),mysql_error(conn));
	command("commit");
	if(command("delete from %s where client_id=%d",TABLE_CLIENT,nSocket))
		printf("Error %u:%s\n",mysql_errno(conn),mysql_error(conn));
	command("commit");
	pthread_exit(pSocket);
}
