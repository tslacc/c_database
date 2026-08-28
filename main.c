#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <errno.h>
#include <string.h>
#include "lib_database.h"

int main(int argc, char * argv[]){	
	struct Record *rc = new_record();
	rc->name = malloc(5);
	memcpy(rc->name, "test\0", 5);
	rc->values = malloc(sizeof(union value)*2);
	rc->values[1].as_int = 2;
	char *buffer = rc->to_bytes(rc, 2);
	printf("Buf size %d\n", strlen(rc->name)+1+2*sizeof(union value));
	debug_print_record(rc, 2);
	debug_print_recordbytes(buffer, 2);
	struct Record *rc2 = new_record_from_bytes(buffer, 2);
	debug_print_record(rc2, 2);
	char *buffer2 = rc2->to_bytes(rc2, 2);
	debug_print_recordbytes(buffer2, 2);
	printf("Parity check (1 is good) %u\n", debug_check_record_equality(rc, rc2, 2));
	printf("End program\n");
	
	struct Table *tb = new_table(1,1);
	struct Record *rc3 = tb->make_record(tb);
	rc3->name = malloc(5);
	memcpy(rc3->name, "TEST\0", 5);
	
	return 0;
}
