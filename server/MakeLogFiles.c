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
			for(nLoop=0;p_cFile[nLoop]!='.';nLoop++)
				szFile[nLoop] = p_cFile[nLoop];
			sprintf(szPath,"../User/%s/%slog1.txt",row[0],szFile);
			if(creat(szPath,0755)==-1)
				perror("Error in creating file:");
		}
	}
	mysql_free_result(p_sqlResultSet);
}