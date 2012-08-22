#include "sheader.h"
#include "methods.h"
#include "GlobalData.h"

void MakeLogFiles(char szFilePath[][200],int nSocket)
{
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
			printf("Inside MakeLogFiles = %s\n",row[0]);
		}
	}
	mysql_free_result(p_sqlResultSet);
}
