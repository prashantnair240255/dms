#include "sheader.h"
#include "methods.h"

char* ExtractFile(char szFilePath[][200])
{
	static char szSFileName[50];
	char *pFile;
	int nLoop;
	bzero(szSFileName,sizeof(szSFileName));
	pFile = strrchr(szFilePath[0],'/');
	*pFile++;
	for(nLoop=0;pFile[nLoop]!='.';nLoop++){
		if(pFile[nLoop]!='\0')
			szSFileName[nLoop] = pFile[nLoop];
		else{
			return szSFileName;
		}
	}
}
