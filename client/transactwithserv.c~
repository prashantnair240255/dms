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
  char cBuff[500], szName[50];
  ClientSignalHandler (nSocket);
  char *p_Recieved;
  printf ("%s ", RecieveMsg (nSocket));
  scanf ("%s%*c", szName);
  SendMsg (nSocket, szName);

  while (1)
    {
      ShowMenu (nSocket);
      bzero (cBuff, sizeof (cBuff));
      fgets (cBuff, sizeof (cBuff), stdin);
      SendMsg (nSocket, cBuff);
      sleep (1);
      p_Recieved = RecieveMsg (nSocket);
      printf ("Message from Server: %s\n", p_Recieved);
    }
  close (nSocket);
}
