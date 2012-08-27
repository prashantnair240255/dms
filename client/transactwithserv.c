/*******************************************************\
 * **
 * ** Filename transactwithserv.c
 * **
 * ** Description client Transacting with Server 
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
#include "../SocketFunc.h"

void
TransactWithServer (int nSocket)
{
  char szBuff[500], szName[50];
  ClientSignalHandler (nSocket);
  char *pRecieved;
  printf ("%s ", RecieveMsg (nSocket));
  scanf ("%s%*c", szName);
  SendMsg (nSocket, szName);

  while (1)
    {
      ShowMenu (nSocket);
      bzero (szBuff, sizeof (szBuff));
      fgets (szBuff, sizeof (szBuff), stdin);
      SendMsg (nSocket, szBuff);
      sleep (1);
      pRecieved = RecieveMsg (nSocket);
      printf ("Message from Server: %s\n", pRecieved);
    }
  close (nSocket);
}
