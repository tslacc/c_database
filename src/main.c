#include "lib_database.h"
#include "lib_consoleInput.h"
#include "dbController.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
static void printHelp(void){
	printf("Enter exit to quit.\n");
}
int main(){	
	struct Database *db = newDatabase();
	struct DBController *dbc = newDBController(db);
	// loop and accept commands
	
	printf("Enter some line...\n");
	char uInput[256];
	while(1)
	{
		api_console.consoleLineToBuffer(uInput, sizeof(uInput));
		
		printf("entered\n%s\nsize %lu\n", uInput, strlen(uInput));
		if(strcmp(uInput, "exit")==0){
			break;
		} else if(strcmp(uInput, "help")==0){
			printHelp();
		}
		parseStringCommand(dbc, uInput, strlen(uInput));
	}
	// todo internal free of db, dbc
	free(db);
	free(dbc);
}
