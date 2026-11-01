#include "lib_consoleInput.h"
#include <stdio.h>

unsigned int consoleLineToBuffer(char *const restrict buffer, const size_t sz){
	size_t i = 0;
	int nchar = 0;
	while(i < sz-1){		
		nchar = getc(stdin);
		if(nchar==EOF) return i;
		else if(nchar == '\n'){
			break;
		}
		buffer[i]=nchar;
		i++;
	}
	buffer[i]='\0';
	return i;
}
