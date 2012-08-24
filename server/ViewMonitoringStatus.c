#include "sheader.h"
#include "methods.h"
#include "GlobalData.h"

void ViewMonitoringStatus(int nSocket)
{
	char szFile[100],szPath[200],cData[150],szUser[50];
	int nFileDesc,nCount=1;
	printf("------View the status of file-----\n");
	strcpy(szFile,(char*)RecvMsg(nSocket));

	if(command("select log_file_name from %s where log_file_name='%s'",TABLE_LOG,szFile))
		printf("Error %u:%s\n",mysql_errno(conn),mysql_error(conn));
	else{
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

 	for(nLoop=0;p_cFile[nLoop]!='.';nLoop++){
		if(p_cFile[nLoop]!='\0')
                	szFile[nLoop] = p_cFile[nLoop];
                else
                	break;
        }

	command("select client_name from %s",TABLE_CLIENT);
	p_sqlResultSet = mysql_store_result(conn);
	if(mysql_num_rows(p_sqlResultSet)>0){
		while((row=mysql_fetch_row(p_sqlResult))!=NULL){
			sprintf(szPath,"../User/%s/%slog1.txt",row[0],szFile);
			if((nFileDesc=open(szPath,O_RDONLY))==-1){
				perror("Error:");
				continue;
			}
			else{
				szUser = row[0];
				close(nFileDesc);
				break;
			}
		}
	}
	else{
		SendMsg(nSocket,"Something is wrong");
	}

	for(nCount;nCount<6;nCount++){
		sprintf(szPath,"../User/%s/%slog%d.txt",szUser,szFile,nCount);
		nFileDesc = open(szPath,O_RDONLY);
		read(nFileDesc,cData,sizeof(cData));
		SendMsg(nSocket,cData);
		bzero(cData,sizeof(cData));
		close(nFileDesc);
	}
	SendMsg(nSocket,"Exit");
	mysql_free_result(p_sqlResultSet);
	TransactWitClient(nSocket);
}
