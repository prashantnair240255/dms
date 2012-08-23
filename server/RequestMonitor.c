#include "sheader.h"
#include "methods.h"
#include "GlobalData.h"

void RequestMonitor(int nSocket)
{
	int *p_nFiles,nLoopCount=1,nFiles,nIndex=0;
	char p_cFilePath[200], cFiles[2],cSendMsg[300], p_cFileNamePath[10][200];
	printf("\n-----Request for Monitor by Client %d------\n",nSocket);
	strcpy(cFiles,(char*)RecieveMsg(nSocket));
	nFiles = atoi(cFiles);
	printf("Server nFiles : %d\n",nFiles);
	while(nLoopCount<=nFiles){
		bzero(p_cFilePath,sizeof(p_cFilePath));
		strcpy(p_cFilePath,(char*)RecieveMsg(nSocket));
		printf("Inside RequestMonitor() = %s\n",p_cFilePath);
		if(!FileExists(p_cFilePath,nLoopCount-1)){
			if(!CheckStatus(p_cFilePath)){
				sprintf(cSendMsg,"%s --- Already being monitored by someone else",p_cFilePath);
				SendMsg(nSocket,cSendMsg);
			}
			else{
				sprintf(cSendMsg,"%s --- Available for monitoring\n",p_cFilePath);
				SendMsg(nSocket,cSendMsg);
				strcpy(p_cFileNamePath[nIndex],p_cFilePath);
				nIndex++;
			}
		}
		else{
			sprintf(cSendMsg,"%s --- This file doesn't exist\n",p_cFilePath);
			SendMsg(nSocket,cSendMsg);
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
