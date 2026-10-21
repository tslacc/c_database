#include "lib_database.h"
#include "dbController.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
static void getLineToBuf(char *buf, size_t sz){
	size_t i = 0;
	for(; i < sz-1; i++){
		buf[i] = getc(stdin);
		if(buf[i] == '\n'){
			buf[i] = '\0';
			return;
		}
	}
}
int main(){	
	struct Database *db = newDatabase();
	struct DBController *dbc = newDBController(db);
	// loop and accept commands
	
	printf("Enter some line...\n");
	char uInput[256];
	while(1)
	{
		getLineToBuf(uInput, 256);
		printf("entered\n%s\nsize %lu\n", uInput, strlen(uInput));
		if(strcmp(uInput, "exit")==0){
			break;
		}
		parseStringCommand(dbc, uInput, strlen(uInput));
	}
	// todo internal free of db, dbc
	free(db);
	free(dbc);
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
