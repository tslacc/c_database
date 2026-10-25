#include "dbController.h"
#include "lib_database.h"
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
// TODO make
// Parses the next token and places it inside the buffer to avoid unnecessary reallocations
// Returns the length of the token
static int *getNextTokenV2(char *buffer, size_t buffer_size, const char **str, const char *const strend){
	return 0;
}
// Get the next token from str and advance the pointer.
// Space-delimited.
static char *getNextToken(const char **str, const char *const strend){
	printf("parsing next Token starting from %s, %p %p len %lu\n", *str, *str, strend, strend-*str);
	const char *ptr = *str;
	while(ptr < strend && !(*ptr==' ' || *ptr=='\0')){
		ptr++;
	}
	if(*ptr == ' '||*ptr == '\0'){
		// OK. Return by length where length = ptr - str +1
		printf("Return token w size %u\n", ptr-*str+1);
		char *result = malloc(ptr-*str+1);
		memcpy(result, *str, (ptr-*str));
		result[ptr-*str] = '\0';
		*str = ptr+1;
		printf("str modified to %p based on %p\n", *str, ptr);
		printf("returning token %s\n", result);
		return result;
	}
	*str = strend;
	return NULL;
}
static void dbMakeTableHandler(struct DBController *const dbc, const char *cmd, const char *cmdend){
	printf("MakeTableHandler begin w %s %p %p\n", cmd, cmd, cmdend);
	//Consume the rest of the args to make table
	char *nextToken = getNextToken(&cmd, cmdend);
	char *nextToken2 = getNextToken(&cmd, cmdend);
	printf("Tokens\n\t%s %lu\n\t%s %lu\n", nextToken, strlen(nextToken), nextToken2, strlen(nextToken2));
	dbc->currentDB->makeRelation(dbc->currentDB, nextToken, atoi(nextToken2));
	free(nextToken);
	free(nextToken2);
}
static int relationGetIndexOfFieldByName(const struct Relation *const rel, const char *const name){
	for(int i = 0; i < rel->fieldsUsed; i++){
		if(strcmp(rel->fields[i], name)==0) return i;
	}
	return -1;
}
static struct Relation *dbGetRelationByName(const struct Database *const db, const char *const name){
	for(int i = 0; i < db->relationsUsed; i++){
		if(strcmp(db->relations[i]->name, name)==0) return db->relations[i];
	}
	return NULL;
}

static void dbSelectHandler(struct DBController *const dbc, const char *cmd, const char *cmdend){
	struct View *result = malloc(sizeof(struct View));
	//Identify the table to select from
	const char *ptr = cmd;
	char *lastWord;
	while(ptr<cmdend){
		// Replace with indexer instead
		if(lastWord!=NULL) free(lastWord);
		
		lastWord = getNextToken(&cmd,cmdend);
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
	lastWord = getNextToken(&ptr, cmdend);
	while(ptr < cmdend && strcmp(lastWord, "FROM")!=0){
		if(relationGetIndexOfFieldByName(result->selectedRelation, lastWord)!=-1){
			result->numSelectedColumns+=1;
			result->selectedColumns = realloc(result->selectedColumns, sizeof(int)*result->numSelectedColumns);
		}
		if(lastWord!=NULL) free(lastWord);
		lastWord = getNextToken(&ptr, cmdend);
	}
	free(lastWord);
}
static void dbDropHandler(struct DBController *const dbc, const char *cmd, const char *cmdend){
	char *nextToken = getNextToken(&cmd, cmdend);
	for(int i = 0; i < dbc->currentDB->relationsUsed; i++){
		if(strcmp(nextToken, dbc->currentDB->relations[i]->name)==0){
			//Drop table and shove all the next tables to the left
			for(int j = i; j < dbc->currentDB->relationsUsed-1; j++) {
				dbc->currentDB->relations[j] = dbc->currentDB->relations[j+1];
			}
			dbc->currentDB->relationsUsed--;
		}
	}
	free(nextToken);
}
static void dbInsertHandler(struct DBController *const dbc, const char *cmd, const char *cmdend){
	char *nextToken = getNextToken(&cmd, cmdend);
	struct Relation *rel = dbGetRelationByName(dbc->currentDB, nextToken);
	if(rel==NULL) return;
	// Get column format
	int colsCount = 0;
	int *colsOrder = NULL;
	if(cmdend <= cmd){ // Select all
		int colsCount = rel->fieldsUsed;
		int *colsOrder = malloc(sizeof(int)*colsCount);
		for(int i = 0; i < rel->fieldsUsed; i++)
			colsOrder[i] = rel->fieldsUsed;
	} else {// Select by order of names.
		// TODO Fill
		free(nextToken);
		while(1){
			nextToken = getNextToken(&cmd, cmdend);
			if(nextToken==NULL) break;
			int colID = 0;
		}
	}
	//Using colsCount, colsOrder, keep on parsing user lines to add new records to the given Relation.
	free(nextToken);
}
static int relGetAttributeIndexByName(struct Relation *rel, const char *query){
	for(int i = 0; i < rel->fieldsUsed; i++){
		if(strcmp(rel->fields[i], query)==0) return i;
	}
	return -1;
}
static void dbAlterHandler(struct DBController *const dbc, const char *cmd, const char *cmdend){
	char *nextToken = getNextToken(&cmd, cmdend);
	struct Relation *rel = dbGetRelationByName(dbc->currentDB, nextToken);
	//add a column?
	//Check if illegal
	if(rel!=NULL){
		free(nextToken);
		nextToken = getNextToken(&cmd, cmdend);
		int aIdx = relGetAttributeIndexByName(rel, nextToken);
		if(aIdx == -1){
			rel->fields = realloc(rel->fields, sizeof(char *)*(rel->fieldsUsed+1));
			rel->fieldsAllocated = rel->fieldsUsed+1;
			rel->fields[rel->fieldsUsed] = malloc(strlen(nextToken));
			memcpy(rel->fields[rel->fieldsUsed], nextToken, strlen(nextToken)+1);
		}
	}
	free(nextToken);
	return;
}
static void dbDebugHandler(const struct DBController *const dbc){
	const struct Database *const db = dbc->currentDB;
	printf("PTR %p %p\n", dbc, db);
	if(db==NULL) return;
	printf("\tNUM REL: %u\n", db->relationsUsed);
	for(int i = 0; i < db->relationsUsed; i++){
		printf("\tRel \"%s\"\n", db->relations[i]->name);
		printf("\tFields used: %u\tRecords used : %u\n", db->relations[i]->fieldsUsed, db->relations[i]->recordsUsed);
		for(int j = 0; j < db->relations[i]->fieldsUsed; j++){
			if(db->relations[i]->fields[j]!=NULL){
				printf("\t%s", db->relations[i]->fields[j]);
			}else printf("\tNULL");
		}
		printf("\n");
		for(int j = 0; j < db->relations[i]->recordsUsed; j++){
			if(db->relations[i]->records[j]!=NULL){
				for(int k = 0; k < db->relations[i]->fieldsUsed; k++){
					printf("\t%#10lx", db->relations[i]->records[j]->values[k]);
				}
				printf("\n");
			} else printf("\tIncomplete record\n");
		}
	}
}
void parseStringCommand(struct DBController *const dbc, const char *cmd, const int cmdsz){
	printf("rcvd %s %p to parse\n", cmd, cmd);
	const char *const cmdend = cmd+cmdsz;
	char *nextToken = getNextToken(&cmd, cmdend);
	printf("nextToken is %s\n", nextToken);
	printf("cmd is %p\n", cmd);
	if(strcmp(nextToken, "CREATE")==0){
		dbMakeTableHandler(dbc, cmd, cmdend);
	} else if (strcmp(nextToken, "SELECT")==0){
		dbSelectHandler(dbc, cmd, cmdend);
	} else if (strcmp(nextToken, "DROP")==0){
		dbDropHandler(dbc, cmd, cmdend);
	} else if (strcmp(nextToken, "INSERT")==0){ //Add new record(s). Should change mode
		dbInsertHandler(dbc, cmd, cmdend);
	} else if (strcmp(nextToken, "ALTER")==0){
		dbAlterHandler(dbc, cmd, cmdend);
	} else if (strcmp(nextToken, "DEBUG")==0){
		dbDebugHandler(dbc);
	}
	printf("end of parse\n");
	free(nextToken);
}

struct DBController *newDBController(struct Database *currentDB){
	struct DBController *result = malloc(sizeof(struct DBController));
	result->currentDB = currentDB;
	return result;
}
