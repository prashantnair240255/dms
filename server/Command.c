#include "sheader.h"
#include "GlobalData.h"
#include "methods.h"
#include<stdarg.h>

int command(const char *format, ...)
{
        va_list arg;
        int done;
	p_Command = (char *)malloc(5000);
	bzero(p_Command,sizeof(p_Command));
        va_start(arg,format);
        done = vsprintf(p_Command,format,arg);
        va_end(arg);
        
	if(mysql_query(conn,p_Command))
		return 1;

        return 0;
}

