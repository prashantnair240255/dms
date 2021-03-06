/*******************************************************\
 * **
 * ** Filename StartMonitor.c
 * **
 * ** Description: Start monitoring the file.
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

int *pFileDesc,g_nSocket;
struct stat filestatus;
void StartMonitor(char pFilePath[][200],int nLength,int nSocket)
{
	g_nSocket = nSocket;
	int nIndex=0,nInotifypFileDesc,nWatch,nRead;
	nInotifypFileDesc = inotify_init();
	pFileDesc = (int*)malloc(nLength*sizeof(int));
	struct inotify_event *event;
	char *p_cLoop;
	char szBuffer[BUF_LEN];
	for(nIndex=0;nIndex<nLength;nIndex++){
		printf("%s\t",pFilePath[nIndex]);
		pFileDesc[nIndex] = open(pFilePath[nIndex],O_RDWR);
	}
	printf("\n");
	for(nIndex=0;nIndex<nLength;nIndex++){
			nWatch = inotify_add_watch(nInotifypFileDesc,pFilePath[nIndex],IN_ALL_EVENTS);
			if(nWatch==-1) 
		            perror("inotify_add_watch");
			printf("Watching %s using watch descriptor(%d)\n", pFilePath[nIndex], nWatch);
			MakeLogFiles(pFilePath,nSocket);
	}
	for(;;){                                  /* Read events forever */
	        nRead = read(nInotifypFileDesc,szBuffer,BUF_LEN);
		
	        for(p_cLoop=szBuffer; p_cLoop<szBuffer+nRead;){ /* Process all of the events in buffer returned by read() */
    		        event = (struct inotify_event *)p_cLoop;
	                DisplayInotifyEvent(event,pFilePath);
		        p_cLoop += sizeof(struct inotify_event)+event->len;
	        }
         }
}

void DisplayInotifyEvent(struct inotify_event *event,char pFilePath[][200])
{
	int nIndex = (event->wd)-1;
    	printf("Change in %s\n",pFilePath[nIndex]);

	char pPath[1][200];
	strcpy(pPath[0],pFilePath[nIndex]);
	printf("Inside DisplayNotifyEvent = %s\n",pPath[0]);
	if(event->mask & IN_ACCESS)
		printf("File is being accessed\n");
	if(event->mask & IN_ATTRIB)        
		printf("File attributes have been changed\n");
	if(event->mask & IN_MODIFY)        
		printf("File has been modified\n ");
	WriteToLog(pPath);
}

void WriteToLog(char pFilePath[][200])
{
	MYSQL_ROW row;
	char *pFile,szFile[50],szPath[100],ClientName[30];
	int nCount=0,nFileDesc,nLoop;
	printf("Inside WriteToLog = %s\n",pFilePath);
	if(stat(pFilePath[0],&filestatus)==-1)
		perror("stat");
	else{
		printf("Socket No = %d\n",g_nSocket);
		if(command("select CLIENT_NAME from %s where CLIENT_ID=%d",TABLE_CLIENT,g_nSocket))
			printf("Error %u:%s\n",mysql_errno(conn),mysql_error(conn));
		else{
			p_sqlResultSet = mysql_store_result(conn);
			row = mysql_fetch_row(p_sqlResultSet);
			printf("before separating = %s\n",pFilePath[0]);
			strcpy(szFile,ExtractFile(pFilePath[0]));
			printf("%s\n",szFile);
			strcpy(ClientName,row[0]);
			printf("CLient Name = %s\n",ClientName);
			mysql_free_result(p_sqlResultSet);
			do{
				nCount++;
				bzero(szPath,sizeof(szPath));
				printf("Client Name = %s\n",ClientName);
				sprintf(szPath,"../User/%s/%slog%d.txt",ClientName,szFile,nCount);
			}while(nCount<6 && FileIsFull(szPath,nCount,pFilePath));

			if(nCount==6){
				ClearAllFiles(szFile,ClientName);
				sprintf(szPath,"../User/%s/%slog1.txt",ClientName,szFile);
			}
			else{
				printf("\topening file to write\n");
			}
			nFileDesc = open(szPath,O_RDWR|O_APPEND);
			ConvertnWrite(nFileDesc);
		}
	}	
}

void ConvertnWrite(int nFileDesc)
{
	char szBuff[100];
	struct tm *local;
	const char *days[] = {"Sunday", "Monday", "Tuesday", "Wednesday","Thursday","Friday","Saturday"};
	const char *months[] = {"January", "February", "March", "April","May","June","July","August","September","October","November","December"};

	bzero(szBuff,sizeof(szBuff));
        local = localtime(&filestatus.st_atime);
	sprintf(szBuff,"\nLast accessed time:%s, %d %s %d (%d:%d:%d)\n",days[local->tm_wday],local->tm_mday,months[local->tm_mon],(local->tm_year)+1900,local->tm_hour,local->tm_min,local->tm_sec);
	write(nFileDesc,szBuff,strlen(szBuff));

	bzero(szBuff,sizeof(szBuff));
	local = localtime(&filestatus.st_mtime);
	sprintf(szBuff,"\nLast modified time:%s, %d %s %d (%d:%d:%d)\n",days[local->tm_wday],local->tm_mday,months[local->tm_mon],(local->tm_year)+1900,local->tm_hour,local->tm_min,local->tm_sec);
	write(nFileDesc,szBuff,strlen(szBuff));

	bzero(szBuff,sizeof(szBuff));
	local = localtime(&filestatus.st_ctime);
	sprintf(szBuff,"\nLast status change time:%s, %d %s %d (%d:%d:%d)\n",days[local->tm_wday],local->tm_mday,months[local->tm_mon],(local->tm_year)+1900,local->tm_hour,local->tm_min,local->tm_sec);
	write(nFileDesc,szBuff,strlen(szBuff));
}

int FileIsFull(char *pPath,int nCount,char szFilePath[][200])
{
//	ReadFromConfig();
//	printf("nMaxSize = %d\n",nMaxSize);
	if(open(pPath,O_RDWR)==-1){
		open(pPath,O_CREAT|O_RDWR|O_APPEND|O_TRUNC,0755);
		if(command("insert into %s values('%s',%d,'%s',%d)",TABLE_LOG,pPath,nCount,szFilePath[0],g_nSocket)==1)
			printf("Error %u:%s\n",mysql_errno(conn),mysql_error(conn));
		else
			command("commit");
	}
	//mysql_store_result(conn);
	struct stat filestat;
	if(stat(pPath,&filestat)==-1){
		perror("stat");
		exit(1);
	}
	else{
		//mysql_free_result(p_sqlResultSet);
		int nSize = filestat.st_size;
		printf("File Size:%d\n",nSize);
		if(nSize>=100)
			return 1;
		else
			return 0;
	}
}

void ClearAllFiles(char *pFile,char *pUser)
{
	printf("Inside ClearAllFiles\n");
	int nCount=1,nFileDesc[5];
	char szPath[100];
	for(nCount;nCount<6;nCount++){
		sprintf(szPath,"../User/%s/%slog%d.txt",pUser,pFile,nCount);
		nFileDesc[nCount-1] = open(szPath,O_RDWR|O_APPEND|O_TRUNC);
	}
	printf("Outside ClearAllFile\n");
}
