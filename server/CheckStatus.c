#include "sheader.h"
#include "methods.h"
#include "GlobalData.h"

int CheckStatus(char *p_cFilePath)
{
	MYSQL *result;
	result = NULL;
	printf("Inside CheckStatus() = %s\n",p_cFilePath);

	if(mysql_query(conn,"insert into DMS_TEAM07_CLIENTLOGDETAILS_TB values('Hell',1,'CHAR','CHARA',2)"))//command("select * from %s where LOG_FILE_NAME='%s'",TABLE,p_cFilePath)){
	{		printf("Error %u in selecting: %s\n",mysql_errno(conn),mysql_error(conn));
	}
	else{/*
		printf("In storing part\n");
		if((res=mysql_store_result(conn))){
			printf("Error %u in storing: %s\n",mysql_errno(conn),mysql_error(conn));
		}
		else{
			printf("Inc checking part\n");
			if(res)
				return 1;
			else
				return 0;
		}*/
		return 0;
	}
}
