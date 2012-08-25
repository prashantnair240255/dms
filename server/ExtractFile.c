#include "sheader.h"
#include "methods.h"

char* ExtractFile(char p_cFilePath[][200])
{
	printf("In Extract File\n");
	static char szFile[50];
	char *p_cFile;
	int nLoop;
	printf("In Extract File2\n");
	bzero(szFile,sizeof(szFile));
	p_cFile = strrchr(p_cFilePath[0],'/');
	*p_cFile++;
	printf("In Extract File3\n");
	for(nLoop=0;p_cFile[nLoop]!='.';nLoop++){
		if(p_cFile[nLoop]!='\0')
			szFile[nLoop] = p_cFile[nLoop];
		else{
			printf("Out of extractfile()\n");
			return szFile;
		}
	}
}
