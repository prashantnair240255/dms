#include "sheader.h"
#include "methods.h"

char* ExtractFile(char p_cFilePath[][200])
{
	printf("In Extract File\n");
	static char szSFileName[50];
	char *p_cFile;
	int nLoop;
	printf("In Extract File2\n");
	bzero(szSFileName,sizeof(szSFileName));
	p_cFile = strrchr(p_cFilePath[0],'/');
	*p_cFile++;
	printf("In Extract File3\n");
	for(nLoop=0;p_cFile[nLoop]!='.';nLoop++){
		if(p_cFile[nLoop]!='\0')
			szSFileName[nLoop] = p_cFile[nLoop];
		else{
			printf("Out of extractfile()\n");
			return szSFileName;
		}
	}
}
