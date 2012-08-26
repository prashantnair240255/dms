/*******************************************************\
 * **
 * ** Filename RequestMonitor.c
 * **
 * ** Description: Request for monitoring.
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

void RequestMonitor(int nSocket)
{
	int *p_nFiles,nLoopCount=1,nFiles,nIndex=0;
	char p_cFilePath[200], szFiles[2],szSendMsg[300], p_cFileNamePath[10][200];
	printf("\n-----Request for Monitor by Client %d------\n",nSocket);
	strcpy(szFiles,(char*)RecieveMsg(nSocket));
	nFiles = atoi(szFiles);
	printf("Server nFiles : %d\n",nFiles);
	while(nLoopCount<=nFiles){
		bzero(p_cFilePath,sizeof(p_cFilePath));
		strcpy(p_cFilePath,(char*)RecieveMsg(nSocket));
		printf("Inside RequestMonitor() = %s\n",p_cFilePath);
		if(!FileExists(p_cFilePath,nLoopCount-1)){
			if(!CheckStatus(p_cFilePath)){
				sprintf(szSendMsg,"%s --- Already being monitored by someone else",p_cFilePath);
				SendMsg(nSocket,szSendMsg);
				TransactWithClient((void*)socket);
			}
			else{
				sprintf(szSendMsg,"%s --- Available for monitoring\n",p_cFilePath);
				SendMsg(nSocket,szSendMsg);
				strcpy(p_cFileNamePath[nIndex],p_cFilePath);
				nIndex++;
			}
		}
		else{
			sprintf(szSendMsg,"%s --- This file doesn't exist\n",p_cFilePath);
			SendMsg(nSocket,szSendMsg);
		}
		nLoopCount++;
	}
	StartMonitor(p_cFileNamePath,nIndex,nSocket);
}

int FileExists(char *p_cFilePath,int nIndex)
{
	int fd;
	printf("In FileExists() = %s\n",p_cFilePath);
	if((fd=open(p_cFilePath,O_RDWR))==-1){
		printf("Returning 1\n");
		return 1;
	}
	else{
		printf("Returning 0\n");
		close(fd);
		return 0;
	}
}
