#include "sheader.h"
#include "methods.h"
#include "GlobalData.h"

int DatabaseConnect()
{
	conn = mysql_init(NULL);

	if(conn==NULL)
	{
		printf("\nError %u: %s\n\n",mysql_errno(conn),mysql_error(conn));
		exit(1);
	}

	if(mysql_real_connect(conn,"localhost","root","uhsiavli","test",0,NULL,0)==NULL)
	{
		printf("\nConnection problem...Error %u: %s\n\n",mysql_errno(conn),mysql_error(conn));
		exit(1);
	}

	if(!command("desc %s",TABLE_LOG)){
		printf("\nTable %s already exists...\n\n",TABLE_LOG);
	}
	else
	{
		if(command("create table %s(LOG_FILE_NAME varchar(20) PRIMARY KEY,LOG_FILE_COUNT integer(1),FILE_PATH varchar(20), CLIENT_ID integer(4));",TABLE_LOG)){	
			printf("\nTable %s not created...Error %u: %s\n\n",TABLE_LOG,mysql_errno(conn),mysql_error(conn));
			return 0;
		}
		else{
			printf("\nTable created.\n\n");
		}
	}
	p_sqlResultSet = mysql_use_result(conn);
	mysql_free_result(p_sqlResultSet);
	
	if(!command("desc %s",TABLE_CLIENT)){
		printf("\nTable %s already exists...\n\n",TABLE_CLIENT);
	}
	else
	{
		if(command("create table %s(CLIENT_ID integer(2),CLIENT_NAME varchar(30));",TABLE_CLIENT)){	
			printf("\nTable %s not created...Error %u: %s\n\n",TABLE_CLIENT,mysql_errno(conn),mysql_error(conn));
			return 0;
		}
		else{
			printf("\nTable %s created.\n\n",TABLE_CLIENT);
		}
	}
	p_sqlResultSet = mysql_use_result(conn);
	mysql_free_result(p_sqlResultSet);
	
	return 1;
}
