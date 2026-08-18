#include <stdlib.h>
#include <stdio.h>
#include "lib_database.h"

int main(int argc, char * argv[])
{	
	struct Database *d = new_db();
	struct Table *test = d->add_new_table(d, "test");
	printf("Test\n");
	return 0;
}
