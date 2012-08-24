#include "cheader.h"
#include "methods.h"

void ViewMonitoringStatus(int nSocket)
{
	char szFile[100],szMsg[100];
	system("clear");
	printf("You opted to view the status of the file\n");
	printf("Please write the file (along with the path):\n");
	scanf("%s",szFile);

	SendMsg(nSocket,szFile);

	while(1)
	{
		bzero(szMsg,sizeof(szMsg));
		strcpy(szMsg,(char*)RecieveMsg(nSocket));
		if(strcmp(szMsg,"Exit"))
			ShowMenu(nSocket);
		else
			printf("%s\n",szMsg);
	}
}
