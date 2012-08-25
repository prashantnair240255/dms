/*******************************************************\
 * **
 * ** Filename ClientSignalHandler.c
 * **
 * ** Description To handle the Signal from Client side.
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
