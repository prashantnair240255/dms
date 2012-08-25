/*******************************************************\
 * **
 * ** Filename ShowMenu.c
 * **
 * ** Description Client's Choice to request or view status
 * **
 * ** 
 * ** Copyright (c) 24/12/2012 "ABC Ltd."
 * ** All Rights Reserved
 * **
 * ** Author:
 * ** Prashant Nair, Rakesh Arora
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
#include "cheader.h"
#include "methods.h"

void ShowMenu(int nSocket)
{
	int nChoice;
	char *p_nChoice;
	p_nChoice = (char*)malloc(4);
	memset(p_nChoice,0,4);
	
	printf("\n-------------\nSelect your choice\n-------------\n\n");
	printf("1. Request to Monitor\n");	
	printf("2. View status of a file\n");	
	printf("3. Exit\n\n");
	printf("Your choice: ");
	scanf("%d",&nChoice);
	
	sprintf(p_nChoice,"%d",nChoice);
	SendMsg(nSocket,p_nChoice);
	switch(nChoice)
	{
		case 1: RequestMonitor(nSocket);
			break;
		case 2: ViewMonitoringStatus(nSocket);
			break;
		case 3: printf("Exit()\n");
			break;
		default: printf("Please select from above\n");
	}
}
