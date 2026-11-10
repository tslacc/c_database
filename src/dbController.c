#include "dbController.h"
#include "lib_consoleInput.h"
#include "lib_database.h"
#include "strTokenizer.h"
#include <ctype.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

static void printHelp(void){
	printf("help print here\n");
}
static void parseStringCommand(struct DBController *const dbc, char *const cmd){
	(void)dbc;
	printf("rcvd %s %p to parse\n", cmd, cmd);
	struct StringTokens tokens;
	strTokenize(cmd, &tokens);
	printf("retrieved %u tokens\n", tokens.tokenCount);
	printf("nextToken is %s\n", (cmd+tokens.tokens[0]));
	
	printf("cmd is %p\n", cmd);
	/*
	if(strcmp(tokens[0], "CREATE")==0){
		//dbCreateTableHandler(dbc, cmd, cmdend);
	} else if (strcmp(tokens[0], "SELECT")==0){
		//dbSelectHandler(dbc, cmd, cmdend);
	} else if (strcmp(tokens[0], "DROP")==0){
		//dbDropHandler(dbc, cmd, cmdend);
	} else if (strcmp(tokens[0], "INSERT")==0){ //Add new record(s). Should change mode
		//dbInsertHandler(dbc, cmd, cmdend);
	} else if (strcmp(tokens[0], "ALTER")==0){
		//dbAlterHandler(dbc, cmd, cmdend);
	} else if (strcmp(tokens[0], "DEBUG")==0){
		//dbDebugHandler(dbc);
	}
	*/
	printf("end of parse\n");
}

void dbcControlLoop(struct DBController *const dbc){
	printf("%p control loop; enter command\n", dbc);
	printf("Write result to buffer %p\n", dbc->uInput);
	consoleLineToBuffer(dbc->uInput, sizeof(dbc->uInput));
	printf("entered string: \n\t%s\n\tsize: %lu\n", dbc->uInput, strlen(dbc->uInput));
	if(strcmp(dbc->uInput, "exit")==0){
		return;
	} else if(strcmp(dbc->uInput, "help")==0){
		printHelp();
	} else parseStringCommand(dbc, dbc->uInput);
	return;
}
struct DBController *newDBController(struct Database *currentDB){
	struct DBController *result = malloc(sizeof(struct DBController));
	result->currentDB = currentDB;
	return result;
}
