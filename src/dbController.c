#include "dbController.h"
#include "lib_consoleInput.h"
#include "lib_database.h"
#include "strTokenizer.h"
#include <ctype.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

static struct Relation *getRelationByNameFromDB(const struct Database *const db, const char *const name){
	for(unsigned int i = 0; i < db->relationsUsed; i++){
		if(strcmp(db->relations[i]->name, name)==0){
			return(db->relations[i]);
		}
	}
	return NULL;
}
static void dbCreateTableHandler(struct DBController *const dbc, const char *const cmd, const struct StringTokens *tok){
	if(tok->tokenCount!=3) return;
	dbc->currentDB->makeRelation(dbc->currentDB, (cmd+tok->tokens[0]), atoi(cmd+tok->tokens[2]));
}
// SELECT cols,... FROM relation and apply to DBController
static void dbSelectHandler(struct DBController *const dbc, const char *const cmd, const struct StringTokens *tok){
	if(tok->tokenCount<4) return;
	dbc->currentView->selectedRelation = getRelationByNameFromDB(dbc->currentView->selectedDB, cmd+tok->tokens[tok->tokenCount-1]);
	const struct Relation *const rel = dbc->currentView->selectedRelation;
	unsigned int *validCols = 0;
	unsigned int validColCount = 0;
	for(unsigned int i = 1; i < tok->tokenCount-2; i++){
		for(unsigned int j = 0; j < rel->fieldsUsed; j++){
			if(strcmp(rel->fields[j], cmd+tok->tokens[i])==0){
				// Validate that there are no duplicates
				unsigned int duplicate = 0;
				for(unsigned int k = 0; k < validColCount; k++){
					if(validCols[k]==j){
						duplicate = 1;
						break;
					}
				}
				if(duplicate!=0) 
					break;
				validColCount++;
				validCols = realloc(validCols, sizeof(unsigned int)*validColCount);
				validCols[validColCount-1]=j;
				break;
			}
		}
	}
}
// DROP 
static void dbDropHandler(struct DBController *const dbc, const char *const cmd, const struct StringTokens *const tok){
	if(tok->tokenCount<3) return;
	//What is being dropped?
	const char *const dropArg = cmd+tok->tokens[1];
	if(strcmp(dropArg,"TABLE")){
		//Drop TABLE handler
	}
}
static void printHelp(void){
	printf("help print here\n");
}
static void parseStringCommand(struct DBController *const dbc, char *const cmd){
	(void)dbc;
	printf("rcvd %s %p to parse\n", cmd, cmd);
	struct StringTokens str_tok;
	strTokenize(cmd, &str_tok);
	printf("retrieved %u tokens\n", str_tok.tokenCount);
	printf("nextToken is %s\n", (cmd+str_tok.tokens[0]));
	
	printf("cmd is %p\n", cmd);
	const char *const carg0 = cmd+str_tok.tokens[0];
	if(strcmp((carg0),"CREATE")==0){
		printf("test match create ok\n");
		dbCreateTableHandler(dbc, cmd, &str_tok);
	} else if (strcmp((carg0),"SELECT")==0){
		dbSelectHandler(dbc, cmd, &str_tok);
	} else if (strcmp(carg0, "DROP")==0){
		dbDropHandler(dbc, cmd, &str_tok);
	}/*
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
