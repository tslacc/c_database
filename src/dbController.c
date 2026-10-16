#include "dbController.h"
#include "lib_database.h"
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
// Get the next token from str and advance the pointer.
// Space-delimited.
static char *getNextToken(const char *str, const char *const strend){
	const char *ptr = str;
	while(ptr < strend && *ptr!=' '){
		ptr++;
	}
	if(*ptr == ' '){
		// OK. Return by length where length = ptr - str +1
		char *result = malloc(ptr-str+1);
		memcpy(result, str, (ptr-str));
		result[ptr-str+1] = '\0';
		str = ptr;
		return result;
	}
	str = strend;
	return NULL;
}
static void dbMakeTableHandler(struct DBController *const dbc, const char *cmd, const char *cmdend){
	//Consume the rest of the args to make table
	char *nextToken = getNextToken(cmd, cmdend);
	char *nextToken2 = getNextToken(cmd, cmdend);
	dbc->currentDB->makeRelation(dbc->currentDB, nextToken, atoi(nextToken2));
}
static int relationGetIndexOfFieldByName(const struct Relation *const rel, const char *const name){
	for(int i = 0; i < rel->fieldsUsed; i++){
		if(strcmp(rel->fields[i], name)==0) return i;
	}
	return -1;
}
static void dbSelectHandler(struct DBController *const dbc, const char *cmd, const char *cmdend){
	struct View *result = malloc(sizeof(struct View));
	//Identify the table to select from
	const char *ptr = cmd;
	char *lastWord;
	while(ptr<cmdend){
		lastWord = getNextToken(cmd,cmdend);
	}
	if(lastWord[strlen(lastWord)==';'])
		lastWord[strlen(lastWord)] = '\0'; //should be true for a properly formed argument
	for(int i = 0; i < dbc->currentDB->relationsUsed; i++){
		if(strcmp(lastWord, dbc->currentDB->relations[i]->name)==0){
			result->selectedDB = dbc->currentDB;
			result->selectedRelation = dbc->currentDB->relations[i];
			break;
		}
	}
	if(result->selectedRelation==NULL) return;
	ptr = cmd;
	lastWord = getNextToken(ptr, cmdend);
	while(ptr < cmdend && strcmp(lastWord, "FROM")!=0){
		if(relationGetIndexOfFieldByName(result->selectedRelation, lastWord)!=-1){
			result->numSelectedColumns+=1;
			result->selectedColumns = realloc(result->selectedColumns, sizeof(int)*result->numSelectedColumns);
		}
		lastWord = getNextToken(ptr, cmdend);
	}
}
static void dbDropHandler(struct DBController *const dbc, const char *cmd, const char *cmdend){
	char *nextToken = getNextToken(cmd, cmdend);
	for(int i = 0; i < dbc->currentDB->relationsUsed; i++){
		if(strcmp(nextToken, dbc->currentDB->relations[i]->name)==0){
			//Drop table and shove all the next tables to the left
			for(int j = i; j < dbc->currentDB->relationsUsed-1; j++) {
				dbc->currentDB->relations[j] = dbc->currentDB->relations[j+1];
			}
			dbc->currentDB->relationsUsed--;
		}
	}
}
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
	} else if (strcmp(nextToken, "INSERT")){ //Add new record(s). Should change mode
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
