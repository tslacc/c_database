#include "lib_consoleInput.h"
#include <stdio.h>
static void getLineToBuf(char *buf, const size_t sz){
	size_t i = 0;
	for(; i < sz-1; i++){
		buf[i] = getc(stdin);
		if(buf[i] == '\n'){
			buf[i] = '\0';
			return;
		}
	}
}
struct consoleInput api_console = {
	getLineToBuf
};
