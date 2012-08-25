/*******************************************************\
 * **
 * ** Filename ViewMonitoringStatus.c
 * **
 * ** Description: View status of file.
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
#include "../SocketFunc.h"

void ViewMonitoringStatus(int nSocket)
{
	MYSQL_ROW row;
	char szFile[100],szPath[200],*pCheck=NULL,szData[150],*pszUser,szFileName[50];
	int nFileDesc,nCount=1,nRows,nLoop;
	pszUser = (char*)malloc(50);
	bzero(pszUser,sizeof(pszUser));
	printf("------View the status of file-----\n");
	strcpy(szFile,(char*)RecieveMsg(nSocket));
	printf("%s\n",szFile);

	if(command("select file_path from %s where file_path='%s'",TABLE_LOG,szFile))
		printf("Error %u:%s\n",mysql_errno(conn),mysql_error(conn));
	else{
		printf("In ResultSet\n");	
		p_sqlResultSet = mysql_store_result(conn);
		if((nRows=mysql_num_rows(p_sqlResultSet))>0)
			SendMsg(nSocket,"File is being monitored..Just wait for some time..");
		else{
			SendMsg(nSocket,"File is not being monitored");
			TransactWithClient((void*)nSocket);
		}
	}
	p_sqlResultSet = mysql_store_result(conn);
	mysql_free_result(p_sqlResultSet);

	pCheck=strrchr(szFile,'/');
	pCheck++;
 	for(nLoop=0;pCheck[nLoop]!='.';nLoop++){
		if(pCheck[nLoop]!='\0')
                	szFileName[nLoop] = pCheck[nLoop];
                else
                	break;
        }

	command("select client_name from %s",TABLE_CLIENT);
	p_sqlResultSet = mysql_store_result(conn);
	if(mysql_num_rows(p_sqlResultSet)>0){
		while((row=mysql_fetch_row(p_sqlResultSet))!=NULL){
			bzero(szPath,sizeof(szPath));
			sprintf(szPath,"../User/%s/%slog1.txt",row[0],szFileName);
			printf("Path = %s\n",szPath);
			if((nFileDesc=open(szPath,O_RDONLY))==-1){
				perror("Error:");
				continue;
			}
			else{
				pszUser = row[0];
				printf("User: %s\n",pszUser);
				close(nFileDesc);
				break;
			}
		}
	}
	else{
		SendMsg(nSocket,"Something is wrong");
	}

	for(nCount;nCount<6;nCount++){
		bzero(szPath,sizeof(szPath));
		sprintf(szPath,"../User/%s/%slog%d.txt",pszUser,szFileName,nCount);
		printf("Reading from %s\n",szPath);
		nFileDesc = open(szPath,O_RDONLY);
		read(nFileDesc,szData,sizeof(szData));
		SendMsg(nSocket,szData);
		bzero(szData,sizeof(szData));
		close(nFileDesc);
	}
	SendMsg(nSocket,"Exit");
	mysql_free_result(p_sqlResultSet);
	TransactWithClient(nSocket);
}
