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

int *fd,g_nSocket;
void StartMonitor(char p_cFilePath[][200],int nLength,int nSocket)
{
	g_nSocket = nSocket;
	int nIndex=0,nInotifyFd,nWatch,nRead;
	nInotifyFd = inotify_init();
	fd = (int*)malloc(nLength*sizeof(int));
	struct inotify_event *event;
	char *p_cLoop;
	char szBuffer[BUF_LEN];
	for(nIndex=0;nIndex<nLength;nIndex++){
		printf("%s\t",p_cFilePath[nIndex]);
		fd[nIndex] = open(p_cFilePath[nIndex],O_RDWR);
	}
	printf("\n");
	for(nIndex=0;nIndex<nLength;nIndex++){
			nWatch = inotify_add_watch(nInotifyFd,p_cFilePath[nIndex],IN_ALL_EVENTS);
			if(nWatch==-1) 
		            perror("inotify_add_watch");
			printf("Watching %s using watch descriptor(%d)\n", p_cFilePath[nIndex], nWatch);
			MakeLogFiles(p_cFilePath,nSocket);
	}
	for(;;){                                  /* Read events forever */
	        nRead = read(nInotifyFd,szBuffer,BUF_LEN);
		if (nRead == 0)
			perror("Inotify read returned 0:");
	        if (nRead == -1)
		        perror("Inotify read returned -1:");
	        printf("Read %ld bytes from inotify fd\n", (long)nRead);
	        for(p_cLoop=szBuffer; p_cLoop<szBuffer+nRead;){ /* Process all of the events in buffer returned by read() */
    		        event = (struct inotify_event *)p_cLoop;
	                DisplayInotifyEvent(event,p_cFilePath);
		        p_cLoop += sizeof(struct inotify_event)+event->len;
	        }
         }
}

void DisplayInotifyEvent(struct inotify_event *event,char p_cFilePath[][200])
{
	int nIndex = (event->wd)-1;
    	printf("Change in %s\n",p_cFilePath[nIndex]);

	char p_cPath[1][200];
	strcpy(p_cPath[0],p_cFilePath[nIndex]);
	printf("Inside DisplayNotifyEvent = %s\n",p_cPath[0]);
	if(event->mask & IN_ACCESS)
		printf("File is being accessed\n");
	if(event->mask & IN_ATTRIB)        
		printf("File attributes have been changed\n");
	if(event->mask & IN_MODIFY)        
		printf("File has been modified\n ");
	WriteToLog(p_cPath);
}

void WriteToLog(char p_cFilePath[][200])
{
	MYSQL_ROW row;
	char szBuff[50],*p_cFile,szFile[50],szPath[100],*ClientName;
	int nCount=0,nfd,nLoop;
	printf("Inside WriteToLog = %s\n",p_cFilePath);
	struct stat filestatus;
	if(stat(p_cFilePath[0],&filestatus)==-1)
		perror("stat");
	else{
		if(command("select CLIENT_NAME from %s where CLIENT_ID=%d",TABLE_CLIENT,g_nSocket))
			printf("Error %u:%s\n",mysql_errno(conn),mysql_error(conn));
		else{
			p_sqlResultSet = mysql_store_result(conn);
			row = mysql_fetch_row(p_sqlResultSet);
			printf("before separating = %s\n",p_cFilePath[0]);
			strcpy(szFile,ExtractFile(p_cFilePath[0]));
			printf("%s\n",szFile);
			ClientName = row[0];
			mysql_free_result(p_sqlResultSet);
			do{
				nCount++;
				sprintf(szPath,"../User/%s/%slog%d.txt",ClientName,szFile,nCount);
			}while(nCount<6 && FileIsFull(szPath,nCount,p_cFilePath));

			if(nCount==6){
				ClearAllFiles(szFile,ClientName);
				sprintf(szPath,"../User/%s/%slog1.txt",ClientName,szFile);
			}
			else{
				printf("\topening file to write\n");
			}
			nfd = open(szPath,O_RDWR|O_APPEND);
			bzero(szBuff,sizeof(szBuff));
			sprintf(szBuff,"\nLast accessed time:%d seconds\t\n",filestatus.st_atime);
			write(nfd,szBuff,strlen(szBuff));
			bzero(szBuff,sizeof(szBuff));
			sprintf(szBuff,"Last modified time:%d seconds\t\n",filestatus.st_mtime);
			write(nfd,szBuff,strlen(szBuff));
			bzero(szBuff,sizeof(szBuff));
			sprintf(szBuff,"Last status change time:%d seconds \t\n",filestatus.st_ctime);
			write(nfd,szBuff,strlen(szBuff));
		}
	}	
}

int FileIsFull(char *p_cPath,int nCount,char szFilePath[][200])
{
	printf("Inside File is Full = %s\n",p_cPath);
	if(open(p_cPath,O_RDWR)==-1)
		open(p_cPath,O_CREAT|O_RDWR|O_APPEND|O_TRUNC,0755);
	
	if(command("insert into %s values('%s',%d,'%s',%d)",TABLE_LOG,p_cPath,nCount,szFilePath[0],g_nSocket)==1)
		printf("Error %u:%s\n",mysql_errno(conn),mysql_error(conn));
	command("commit");
	struct stat filestat;
	if(stat(p_cPath,&filestat)==-1){
		perror("stat");
		exit(1);
	}
	else{
		int nSize = filestat.st_size;
		printf("File Size:%d\n",nSize);
		if(nSize>=100)
			return 1;
		else
			return 0;
	}
}

void ClearAllFiles(char *p_cFile,char *p_cUser)
{
	printf("Inside ClearAllFiles\n");
	int nCount=1,nfd[5];
	char szPath[100];
	for(nCount;nCount<6;nCount++){
		sprintf(szPath,"../User/%s/%slog%d.txt",p_cUser,p_cFile,nCount);
		nfd[nCount-1] = open(szPath,O_RDWR|O_APPEND|O_TRUNC);
	}
	printf("Outside ClearAllFile\n");
}
