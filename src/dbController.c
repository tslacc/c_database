#include "dbController.h"
#include "lib_consoleInput.h"
#include "lib_database.h"
#include <ctype.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
struct bounds2D{
	unsigned int rows;
	unsigned int cols;
};
static int countTokens(const char *const str){
	(void)str;
	return 0;
}
//Return the number of tokens filled
static void tokenize(const char *const str, char ***buffers, struct bounds2D *result){
	(void)buffers;
	(void)str;
	int rowCount = countTokens(str);
	result->rows = rowCount;
	result->cols = 0;
	
	return;
}
static void printHelp(void){
	printf("help print here\n");
}
static void parseStringCommand(struct DBController *const dbc, const char *const cmd){
	printf("rcvd %s %p to parse\n", cmd, cmd);
	char **tokens;
	struct bounds2D rsz;
	tokenize(cmd, &tokens, &rsz);
	printf("nextToken is %s\n", tokens[0]);
	printf("cmd is %p\n", cmd);
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
