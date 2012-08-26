/*******************************************************\
 * **
 * ** Filename ViewMonitoringStatus.c
 * **
 * ** Description To view the status of files being monitored.
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

void ViewMonitoringStatus(int nSocket)
{
	char szFile[100],szMsg[200];
	system("clear");
	printf("You opted to view the status of the file\n");
	printf("Please write the file (along with the path):\n");
	scanf("%s",szFile);
	printf("%s\n",szFile);

	SendMsg(nSocket,szFile);

	while(1)
	{
		bzero(szMsg,sizeof(szMsg));
		strcpy(szMsg,(char*)RecieveMsg(nSocket));
		if(strcmp(szMsg,"Exit"))
			printf("%s\n",szMsg);
		else
			ShowMenu(nSocket);
	}
}
