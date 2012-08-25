/*******************************************************\
 * **
 * ** Filename CleanExit.c
 * **
 * ** Description: Exiting from server.
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

void CleanExit(void* p_Socket)
{
	int nSocket = (int)p_Socket;
	printf("Client %d disconnected\n-------------------------------------\n",nSocket);
	if(command("delete from %s where client_id=%d",TABLE_CLIENT,nSocket))
		printf("Error %u:%s\n",mysql_errno(conn),mysql_error(conn));
	command("commit");
	if(command("delete from %s where client_id=%d",TABLE_CLIENT,nSocket))
		printf("Error %u:%s\n",mysql_errno(conn),mysql_error(conn));
	command("commit");
	SendMsg(nSocket,"~9");
	pthread_exit(p_Socket);
}
