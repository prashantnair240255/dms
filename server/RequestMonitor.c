#include "sheader.h"
#include "methods.h"
#include "GlobalData.h"

void RequestMonitor(int nSocket)
{
	int *p_nFiles,nLoopCount=1,nFiles,nIndex=0;
	char p_cFilePath[200], cFiles[2],cSendMsg[300];
	printf("\n-----Request for Monitor by Client %d------\n",nSocket);
	strcpy(cFiles,(char*)RecieveMsg(nSocket));
	nFiles = atoi(cFiles);
	printf("Server nFiles : %d\n",nFiles);

	int *fd;
	fd = (int*)malloc(nFiles*sizeof(int));

	while(nLoopCount<=nFiles){
		bzero(p_cFilePath,sizeof(p_cFilePath));
		strcpy(p_cFilePath,(char*)RecieveMsg(nSocket));
		printf("Inside RequestMonitor() = %s\n",p_cFilePath);

		if(mysql_query(conn,"insert into DMS_TEAM07_CLIENTLOGDETAILS_TB values('Hell',1,'CHAR','CHARA',2)")){
			printf("Error %u:%s\n",mysql_errno(conn),mysql_error(conn));
			sprintf(cSendMsg,"%s --- Already being monitored by someone else",p_cFilePath);
			SendMsg(nSocket,cSendMsg);
		}
		else{
			sprintf(cSendMsg,"%s --- Available for monitoring\n",p_cFilePath);
		//	SendMsg(nSocket,cSendMsg);
		//	fd[nIndex]=4;
		//	nIndex++;
		}
		nLoopCount++;
	}
}
