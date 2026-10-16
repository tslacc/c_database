#include "lib_database.h"
#include "dbController.h"
#include <stdio.h>
#include <stdlib.h>
int main(){	
	printf("Enter some line...\n");
	char uInput[256];
	if(fgets(uInput, sizeof uInput, stdin) != NULL)
	{
		printf("entered\n%s", uInput);
	}
	struct Database *db = newDatabase();
	struct DBController *dbc = newDBController(db);
	// loop and accept commands
	
	/*
	printf("Enter something.\n");
	char **uInput2 = malloc(sizeof(char*));
	*uInput2 = NULL;
	size_t SZIN = 256; 
	if(getline(uInput2, &SZIN, stdin) != -1)
	{
		printf("entered getline\n%s", *uInput2);
	}
	return 0;
	*/
}
