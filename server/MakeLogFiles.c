/*******************************************************\
 * **
 * ** Filename MakeLogFiles.c
 * **
 * ** Description: Makeing Log files.
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

void MakeLogFiles(char szFilePath[][200],int nSocket)
{
	int nLoop;
	char szPath[50],szFile[50],*p_cFile;
	printf("Inside Make LOG \n");
	MYSQL_ROW row;
	int nRows;
	if(command("select client_name from %s where client_id=%d",TABLE_CLIENT,nSocket))
		printf("Error %u:%s\n",mysql_errno(conn),mysql_error(conn));
	else{
		p_sqlResultSet=mysql_store_result(conn);
		if((nRows=mysql_num_rows(p_sqlResultSet))==0)
			printf("Client not present\n");
		else{
			row = mysql_fetch_row(p_sqlResultSet);
			p_cFile = strrchr(szFilePath[0],'/');
			*p_cFile++;

			for(nLoop=0;p_cFile[nLoop]!='.';nLoop++){
				if(p_cFile[nLoop]!='\0')
		                     szFile[nLoop] = p_cFile[nLoop];
		         	else
		                     break;

			}
			sprintf(szPath,"../User/%s/%slog1.txt",row[0],szFile);
			printf("%s\n",szPath);
			if(open(szPath,O_CREAT|O_RDWR|O_TRUNC,0755)==-1)
				perror("Error in creating file:");
			if(command("insert into %s values('%s',1,'%s',%d)",TABLE_LOG,szPath,szFilePath,nSocket)==1)
				printf("Error %u:%s\n",mysql_errno(conn),mysql_error(conn));
		}
	}
	mysql_free_result(p_sqlResultSet);
}
