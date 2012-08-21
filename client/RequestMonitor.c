#include "cheader.h"
#include "methods.h"

void RequestMonitor(int nSocket)
{
	int nFiles,i=1;
	char cFile[200],cnFiles[2],cRecvMsg[300];
	
	system("clear");
	printf("You have requested to monitor file(s).\n");
	printf("Please tell the number of files you want to monitor: ");
	scanf("%d%*c",&nFiles);				//(%*c) for no buffer problem
	sprintf(cnFiles,"%d",nFiles);
	printf("%s\n",cnFiles);
	SendMsg(nSocket,cnFiles);

	printf("Please enter the name of files along with their paths (separated by a blank space):\n");
	while(i<=nFiles){
		bzero(cFile,sizeof(cFile));
		fgets(cFile,sizeof(cFile),stdin);
		SendMsg(nSocket,cFile);
		strcpy(cRecvMsg,(char*)RecieveMsg(nSocket));
		printf("%s\n",cRecvMsg);
		i++;
	}
}
