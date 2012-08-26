/*******************************************************\
 * **
 * ** Filename RequestMonitor.c
 * **
 * ** Description Requesting Server to monitor a file.
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
void RequestMonitor(int nSocket)
{
	int nFiles,i=1;
	char cFile[200],cnFiles[2],cRecvMsg[300],szSendMsg[100];
	
	system("clear");
	printf("You have requested to monitor file(s).\n");
	printf("Please tell the number of files you want to monitor: ");
	scanf("%d%*c",&nFiles);				//(%*c) for no buffer problem
	sprintf(cnFiles,"%d",nFiles);
	SendMsg(nSocket,cnFiles);

	printf("Please enter the name of files along with their paths (separated by a blank space):\n");
	while(i<=nFiles){
		bzero(cFile,sizeof(cFile));
		bzero(szSendMsg,sizeof(szSendMsg));
		fgets(cFile,sizeof(cFile),stdin);
		cFile[strlen(cFile)-1]='\0';
		SendMsg(nSocket,cFile);
		strcpy(cRecvMsg,(char*)RecieveMsg(nSocket));
		printf("%s\n",cRecvMsg);
		sprintf(szSendMsg,"%s --- Already being monitored by someone else",cFile);
		if(!strcmp(szSendMsg,cRecvMsg))
			ShowMenu(nSocket);
		else
			i++;
	}
}
