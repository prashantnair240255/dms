#include "sheader.h"
#include "methods.h"
#include "GlobalData.h"

void ReadFromConfig()
{
	char c;
	int nArr[2],nIndex=0;
	FILE *fp;
		          
	if((fp=fopen("../config.txt","r"))==NULL){
		printf("cannot open the file");
		exit(1);
	}
	else{
		do{
			c=fgetc(fp);
			if(!isdigit(c))
				continue;
			else{
				nArr[nIndex]=atoi(&c);
				nIndex++;
			}
		}while(c!=EOF);
		nMaxFiles = nArr[0];
		nMaxSize = nArr[1];
	}
}
