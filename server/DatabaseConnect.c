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

	if(!command("desc %s",TABLE))
		printf("\nTable already exists...\n\n");
	else
	{
		if(command("create table %s(LOG_FILE_NAME varchar(20) PRIMARY KEY,LOG_FILE_COUNT integer(1),FILE_NAME varchar(20), CLIENT_NAME varchar(20),CLIENT_ID integer(1));",TABLE))
		{	
			printf("\nTable not created...Error %u: %s\n\n",mysql_errno(conn),mysql_error(conn));
			return 0;
		}
		else
			printf("\nTable created.\n\n");
	}
	
	return 1;
}
