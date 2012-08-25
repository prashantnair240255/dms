/*******************************************************\
 * **
 * ** Filename ServerSignalHandler.c
 * **
 * ** Description: Handle the signal from server.
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

void ServerSignalHandler()
{
	struct sigaction action = { SigHandler };
	if(sigaction(SIGINT,&action,NULL))
		perror("Signal no: ");
}

void SigHandler(int nSigNo)
{
	system("clear");
}
