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
	
	
	return 0;
}
