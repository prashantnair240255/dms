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
#include "../SocketFunc.h"

void* TransactWithClient(void* vSocket)
{
	char *p_Buff;
	p_Buff = (char*)malloc(500);
	int nCSocket = (int)vSocket;
	bzero(p_Buff,sizeof(p_Buff));

	while(strcpy(p_Buff,RecieveMsg(nCSocket))!=NULL){
		sleep(1);
		if(!strcmp(p_Buff,"~2"))
		{
			CleanExit((void*)nCSocket);
		}		
		else if(!strcmp(p_Buff,"1"))
		{	
			printf("Message from Client %d: ",nCSocket);
			RequestMonitor(nCSocket);
		}
		else if(!strcmp(p_Buff,"2"))
		{	
			printf("Message from Client %d: ",nCSocket);
			ViewMonitoringStatus(nCSocket);
		}
		else if(!strcmp(p_Buff,"3"))
		{	
			printf("Message from Client %d: ",nCSocket);
			Exit();
		}
	}
}

void Exit(){}
