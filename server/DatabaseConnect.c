#include "sheader.h"
#include "GlobalData.h"

void DatabaseConnect()
{
	conn = mysql_init(NULL);

	if(conn==NULL)
	{
		printf("Error %u: %s\n",mysql_errno(conn),mysql_error(conn));
		exit(1);
	}

	if(mysql_real_connect(conn,"localhost","root","wipro123","test",0,NULL,0)==NULL)
	{
		printf("Error %u: %s\n",mysql_errno(conn),mysql_error(conn));
	}

	mysql_query(conn,"create table DMS_TEAM07_CLIENTLOGDETAILS_TB(LOG_FILE_NAME varchar(20) PRIMARY KEY,LOG_FILE_COUNT number(1),FILE_NAME varchar(20), CLIENT_NAME varchar(20),CLIENT_ID number(1) AUTO_INCREMENT)");
}
