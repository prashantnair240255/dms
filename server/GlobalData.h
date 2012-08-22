#include "mysql.h"
#define TABLE_LOG "DMS_TEAM07_CLIENTLOGDETAILS_TB"
#define TABLE_CLIENT "DMS_TEAM07_CLIENTDETAILS_TB"
#define BUF_LEN 10*sizeof(struct inotify_event)
MYSQL *conn;
MYSQL_RES *p_sqlResultSet;
static char* p_Command;
