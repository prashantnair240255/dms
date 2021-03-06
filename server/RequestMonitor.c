/*******************************************************\
 * **
 * ** Filename RequestMonitor.c
 * **
 * ** Description: Request to Monitor file(s).
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
	int *pFiles,nLoopCount=1,nFiles,nIndex=0,nFlag=0;
	char szFilePath[200], szFiles[2],szSendMsg[300], szFileNamePath[10][200];
	printf("\n-----Request for Monitor by Client %d------\n",nSocket);
	strcpy(szFiles,(char*)RecieveMsg(nSocket));
	nFiles = atoi(szFiles);
	printf("Server nFiles : %d\n",nFiles);
	while(nLoopCount<=nFiles){
		bzero(szFilePath,sizeof(szFilePath));
		strcpy(szFilePath,(char*)RecieveMsg(nSocket));
		printf("Inside RequestMonitor() = %s\n",szFilePath);
		if(!FileExists(szFilePath,nLoopCount-1)){
			if(!CheckStatus(szFilePath)){
				sprintf(szSendMsg,"%s --- Already being monitored by someone else",szFilePath);
				SendMsg(nSocket,szSendMsg);
				SendMsg(nSocket,"1");
				TransactWithClient((void*)nSocket);
			}
			else{
				sprintf(szSendMsg,"%s --- Available for monitoring\n",szFilePath);
				SendMsg(nSocket,szSendMsg);
				strcpy(szFileNamePath[nIndex],szFilePath);
				nIndex++;
			}
		}
		else{
			sprintf(szSendMsg,"%s --- This file doesn't exist\n",szFilePath);
			SendMsg(nSocket,szSendMsg);
			SendMsg(nSocket,"2");
			TransactWithClient((void*)nSocket);
		}
		nLoopCount++;
	}
	SendMsg(nSocket,"3");
	StartMonitor(szFileNamePath,nIndex,nSocket);
}

int FileExists(char *szFilePath,int nIndex)
{
	int fd;
	printf("In FileExists() = %s\n",szFilePath);
	if((fd=open(szFilePath,O_RDWR))==-1){
		printf("Returning 1\n");
		return 1;
	}
	else{
		printf("Returning 0\n");
		close(fd);
		return 0;
	}
}
