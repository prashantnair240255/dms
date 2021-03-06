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
	ClientSignalHandler();
	int nFiles,i=1;
	char szFile[200],szFiles[2],szRecvMsg[300],szSendMsg[100],szSendMesg[100],szMesag[2];
	system("clear");
	printf("You have requested to monitor file(s).\n");
	printf("Please tell the number of files you want to monitor: ");
	scanf("%d%*c",&nFiles);				//(%*c) for no buffer problem
	sprintf(szFiles,"%d",nFiles);
	SendMsg(nSocket,szFiles);
	printf("Please enter the name of files along with their paths (separated by a blank space):\n");
	while(i<=nFiles){
		bzero(szFile,sizeof(szFile));
		bzero(szSendMsg,sizeof(szSendMsg));
		bzero(szSendMesg,sizeof(szSendMesg));
		fgets(szFile,sizeof(szFile),stdin);
		szFile[strlen(szFile)-1]='\0';
		SendMsg(nSocket,szFile);
		strcpy(szRecvMsg,(char*)RecieveMsg(nSocket));
		printf("%s\n",szRecvMsg);
		strcpy(szMesag,(char*)RecieveMsg(nSocket));
		printf("szMesag = %s\n",szMesag);
		if(!strcmp(szMesag,"1")){
			printf("Please enter from start again...\n");
			ShowMenu(nSocket);
		}
		else if(!strcmp(szMesag,"2")){
			printf("Please enter from start again...\n");
			ShowMenu(nSocket);					
		}
		else if(!strcmp(szMesag,"3")){
			ShowMenu(nSocket);					
		}
		else
			i++;
	}
}
