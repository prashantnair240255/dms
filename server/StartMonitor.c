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
	        for (p_cLoop=szBuffer; p_cLoop<szBuffer+nRead;){ /* Process all of the events in buffer returned by read() */
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
		printf("IN_MODIFY\n ");
	WriteToLog(p_cPath);
}

void WriteToLog(char p_cFilePath[][200])
{
	
	MYSQL_ROW row;
	char szBuff[50],*p_cFile,szFile[50],szPath[100];
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
			bzero(szFile,sizeof(szFile));
			p_cFile = strrchr(p_cFilePath[0],'/');
			*p_cFile++;
			for(nLoop=0;p_cFile[nLoop]!='.';nLoop++){
				if(p_cFile[nLoop]!='\0')
					szFile[nLoop] = p_cFile[nLoop];
				else
					break;
			}
			printf("after separating = %s\n",szFile);
			do{
				nCount++;
				sprintf(szPath,"../User/%s/%slog%d.txt",row[0],szFile,nCount);
			}while(nCount<6 && FileIsFull(szPath));

			if(nCount==6){
				ClearAllFiles(szFile,row[0]);
				sprintf(szPath,"../User/%s/%slog1.txt",row[0],szFile);
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

int FileIsFull(char *p_cPath)
{
	printf("Inside File is Full = %s\n",p_cPath);
	if(open(p_cPath,O_RDWR)==-1)
		open(p_cPath,O_CREAT|O_RDWR|O_APPEND|O_TRUNC,0755);
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
