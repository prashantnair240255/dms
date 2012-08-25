/*******************************************************\
 * **
 * ** Filename CheckStatus.c
 * **
 * ** Description: Checking the status of file.
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

int CheckStatus(char *p_cFilePath)
{
	printf("Inside CheckStatus() = %s\n",p_cFilePath);
	if(command("select * from %s where LOG_FILE_NAME = '%s'",TABLE_LOG,p_cFilePath)){	
		printf("Error %u in selecting: %s\n",mysql_errno(conn),mysql_error(conn));
	}
	else{
		printf("In storing part\n");
		p_sqlResultSet=mysql_store_result(conn);
		int nRows = mysql_num_rows(p_sqlResultSet);
		printf("No. of rows: %d\n",nRows);
		if(nRows==0){
			mysql_free_result(p_sqlResultSet);
			return 1;
		}
		else{
			mysql_free_result(p_sqlResultSet);
			return 0;
		}
		
		mysql_free_result(p_sqlResultSet);
	}
	
	return -1;
}
