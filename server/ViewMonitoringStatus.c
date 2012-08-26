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
	char szFile[1][200],szPath[200],*pCheck,szData[200],*pszUser,szFileName[50];
	int nFileDesc,nCount=1,nRows,nLoop,nGetSocket;
	pszUser = (char*)malloc(50);
	bzero(pszUser,sizeof(pszUser));
	bzero(szFile,sizeof(szFile));
	printf("------View the status of file-----\n");
	strcpy(szFile[0],(char*)RecieveMsg(nSocket));
	printf("%s\n",szFile[0]);

	if(command("select file_path from %s where file_path='%s'",TABLE_LOG,szFile[0]))
		printf("Error %u:%s\n",mysql_errno(conn),mysql_error(conn));
	else{
		printf("In ResultSet\n");	
		if((p_sqlResultSet=mysql_store_result(conn))!=NULL){
		if((nRows=mysql_num_rows(p_sqlResultSet))>0)
			SendMsg(nSocket,"File is being monitored..Just wait for some time..");
		else{
			SendMsg(nSocket,"File is not being monitored");
			TransactWithClient(nSocket);
		}
	}
	else{
		printf("Resultset null \n");
	}
	}
	p_sqlResultSet = mysql_store_result(conn);
	mysql_free_result(p_sqlResultSet);
	p_sqlResultSet = NULL;
	bzero(szFileName,sizeof(szFileName));
	strcpy(szFileName,ExtractFile(szFile[0]));
	printf("%s\n",szFileName);
	/*pCheck=strrchr(szFile,'/');
	pCheck++;
 	for(nLoop=0;pCheck[nLoop]!='.';nLoop++){
		if(pCheck[nLoop]!='\0')
                	szFileName[nLoop] = pCheck[nLoop];
                else
                	break;
        }*/
	printf("szFile[0] = %s\n",szFile[0]);
	if(command("select client_id from %s where file_path='%s'",TABLE_LOG,szFile[0]))
		printf("Error %u:%s\n",mysql_errno(conn),mysql_error(conn));
	else
		printf("Success\n");
	if((p_sqlResultSet=mysql_store_result(conn))==NULL)
		printf("Error %u:%s\n",mysql_errno(conn),mysql_error(conn));
	else
		printf("Done this also\n");

	if((nRows=mysql_num_rows(p_sqlResultSet))>0){
		row = mysql_fetch_row(p_sqlResultSet);
		nGetSocket = atoi(row[0]);
	}
	printf("Done with first table\n");
	mysql_free_result(p_sqlResultSet);
	p_sqlResultSet = NULL;
	printf("nGetSocket = %d\n",nGetSocket);
	command("select client_name from %s where client_id=%d",TABLE_CLIENT,nGetSocket);
	p_sqlResultSet = mysql_store_result(conn);
	printf("Done with first table\n");
	nRows = mysql_num_rows(p_sqlResultSet);
	printf("%d\n",nRows);
	if(nRows>0){
			row = mysql_fetch_row(p_sqlResultSet);
			bzero(szPath,sizeof(szPath));
			sprintf(szPath,"../User/%s/%slog1.txt",row[0],szFileName);
			printf("Path = %s\n",szPath);
			if((nFileDesc=open(szPath,O_RDONLY))==-1){
				perror("Error:");
			}
			else{
				pszUser = row[0];
				printf("User: %s\n",pszUser);
				close(nFileDesc);
			}
		}
	else{
		SendMsg(nSocket,"Something is wrong");
	}
	mysql_free_result(p_sqlResultSet);

	for(nCount;nCount<6;nCount++){
		bzero(szPath,sizeof(szPath));
		sprintf(szPath,"../User/%s/%slog%d.txt",pszUser,szFileName,nCount);
		printf("Reading from %s\n",szPath);
		nFileDesc = open(szPath,O_RDONLY);
		read(nFileDesc,szData,sizeof(szData));
		printf("%s\n",szData);
		SendMsg(nSocket,szData);
		bzero(szData,sizeof(szData));
		close(nFileDesc);
	}
	SendMsg(nSocket,"Exit");
	TransactWithClient(nSocket);
}
