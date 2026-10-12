#include "dbController.h"
#include "lib_database.h"
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
// Get the next token from str and advance the pointer
static char *getNextToken(const char *str, const char *const strend){
	return NULL;
}
static void dbMakeTableHandler(struct DBController *const dbc, const char *cmd, const char *cmdend){
	//Consume the rest of the args to make table
	char *nextToken = getNextToken(cmd, cmdend);
	char *nextToken2 = getNextToken(cmd, cmdend);
	dbc->currentDB->makeRelation(dbc->currentDB, nextToken, atoi(nextToken2));
}
static void dbSelectHandler(struct DBController *const dbc, const char *cmd, const char *cmdend);
static void dbDropHandler(struct DBController *const dbc, const char *cmd, const char *cmdend);
static void dbInsertHandler(struct DBController *const dbc, const char *cmd, const char *cmdend);
static void dbAlterHandler(struct DBController *const dbc, const char *cmd, const char *cmdend);
void parseStringCommand(struct DBController *const dbc, const char *cmd, const int cmdsz){
	const char *const cmdend = cmd+cmdsz;
	char *nextToken = getNextToken(cmd, cmdend);
	if(strcmp(nextToken, "CREATE")){
		dbMakeTableHandler(dbc, cmd, cmdend);
	} else if (strcmp(nextToken, "SELECT")){
		dbSelectHandler(dbc, cmd, cmdend);
	} else if (strcmp(nextToken, "DROP")){
		dbDropHandler(dbc, cmd, cmdend);
	} else if (strcmp(nextToken, "INSERT")){
		dbInsertHandler(dbc, cmd, cmdend);
	} else if (strcmp(nextToken, "ALTER")){
		dbAlterHandler(dbc, cmd, cmdend);
	}
}

struct DBController *newDBController(struct Database *currentDB){
	struct DBController *result = malloc(sizeof(struct DBController));
	result->currentDB = currentDB;
	return result;
}
