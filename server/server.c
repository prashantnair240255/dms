#include "sheader.h"
#include "methods.h"

void main(int argc,char *argv[])
{
	ServerSignalHandler();
	if(mkdir("../User",0755)==-1)
		printf("Directory Exists\n");
	if(DatabaseConnect())
		SocketConnect(argv);
}
