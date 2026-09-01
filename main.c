#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <errno.h>
#include <string.h>
#include "lib_database.h"

int main(int argc, char * argv[]){	
	struct Table *tb = new_table(1,1);
	struct Record *rc3 = tb->make_record(tb);
	rc3->name = malloc(5);
	memcpy(rc3->name, "TEST\0", 5);
	
	char *buffer = tb->to_bytes(tb);
	tb->allocate_new_headers(tb, 3);
	for(int i = 0; i < 3; i++){
		tb->headers[i] = malloc(sizeof(char)*i+2);
	}
	tb->headers[0] = "TE\0";
	tb->headers[1] = "TES\0";
	tb->headers[2] = "TEST\0";
	return 0;
}
