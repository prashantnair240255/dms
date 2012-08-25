/*******************************************************\
 * **
 * ** Filename client.c
 * **
 * ** Description Main function of client.
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

#include "cheader.h"
#include "methods.h"

void main(int argc,char *argv[])
{
	struct sockaddr_in serv;
	int nPort,nSocketDesc;
	printf("\n---Connected to the server---\n\n");
	nPort = atoi(argv[2]);
	nSocketDesc = socket(AF_INET,SOCK_STREAM,0);
	memset(&serv,0,sizeof(struct sockaddr_in));
	serv.sin_family = AF_INET;
	serv.sin_addr.s_addr = inet_addr(argv[1]);
	serv.sin_port = htons(nPort);
	connect(nSocketDesc,(struct sockaddr *)&serv,sizeof(serv));
	TransactWithServer(nSocketDesc);
	close(nSocketDesc);
}
