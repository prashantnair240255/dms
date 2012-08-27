/*******************************************************\
 * **
 * ** Filename command.c
 * **
 * ** Description: Wrapper function for mysql_query.
 * **
 * ** 
 * ** Copyright (c) 24/08/2012 .ABC Ltd..
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
#include "GlobalData.h"
#include "methods.h"

int command(const char *format, ...)
{
        va_list arg;
        int nDone;
	pCommand = (char *)malloc(5000);
	bzero(pCommand,sizeof(pCommand));
        va_start(arg,format);
        nDone = vsprintf(pCommand,format,arg);
        va_end(arg);
        
	if(mysql_query(conn,pCommand))
		return 1;

        return 0;
}

