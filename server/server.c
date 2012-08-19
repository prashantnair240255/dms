#include "sheader.h"
#include "methods.h"

void main(int argc,char *argv[])
{
	ServerSignalHandler();
	if(DatabaseConnect())
		SocketConnect(argv);
}
