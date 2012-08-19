#include "mysql.h"
#define TABLE "DMS_TEAM07_CLIENTLOGDETAILS_TB"

MYSQL *conn;
MYSQL_RES *result,*res;
MYSQL_ROW row;

static char* p_Command;
