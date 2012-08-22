#include "sheader.h"
#include "methods.h"
#include "GlobalData.h"

void StartMonitor(int* fd,char p_cFilePath[][200],int nLength,int nSocket)
{
	int nIndex=0,nInotifyFd,nWatch,nRead;
	nInotifyFd = inotify_init();
	struct inotify_event *event;
	char *p_cLoop;
	char szBuffer[BUF_LEN];
	for(nIndex=0;nIndex<nLength;nIndex++){
		printf("%s\t",p_cFilePath[nIndex]);
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
	printf("wd=%2d;", event->wd);
        printf("file = %s",p_cFilePath[(event->wd)-1]);
	if(event->mask & IN_ACCESS)
		printf("File is being accessed");
        if(event->mask & IN_ATTRIB)        
		printf("File attributes have been changed");
        if(event->mask & IN_MODIFY)        printf("IN_MODIFY ");
    	printf("\n");

        if (event->len > 0)
        printf("        name = %s\n", event->name);

}
