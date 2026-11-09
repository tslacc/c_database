#include "dbController.h"
#include "lib_consoleInput.h"
#include "lib_database.h"
#include "strTokenizer.h"
#include <ctype.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

//Move the pointer to either the next LEFT or RIGHT of a valid token.
static void moveStringPointer(const char **const str, int side){
	int c = **str;
	while(side ^ (c == ' '||c==','||c=='\n')){
		(*str)++;
		 c = **str;
	}
}
static int countTokens(const char *const str){
	const char *ptr = str;
	
	moveStringPointer(&ptr, 0); //ptr is now at the begin of any valid token
	
	const char *ptrold = ptr; //ptr and ptr old are now at the beginning of the first valid token, if any
	moveStringPointer(&ptr, 1); //ptr now at begin of delimit block
	moveStringPointer(&ptr, 0); //ptr now at begin of valid token
	int result = 0;
	while(ptr!=ptrold){
		result++;
		ptrold = ptr;
		moveStringPointer(&ptr, 1); 
		moveStringPointer(&ptr, 0); 
		
	}
	return result;
}
//get a token from str and advance the pointer
static char *getNextToken(const char **const str){
	moveStringPointer(str,0);
	const char **begin = str;
	moveStringPointer(str,1); //str is now at the final position
	char *result = malloc(*str-*begin+1);
	memcpy(result, begin, (*str-*begin));
	result[*str-*begin] = '\0';
	return result;	
}
//Return the number of tokens filled
static int tokenize(const char *const str, char ***buffers){
	(void)buffers;
	(void)str;
	int rowCount = countTokens(str);
	*buffers = malloc(sizeof(char*)*rowCount);
	const char *ptr = str;
	for(int i = 0; i < rowCount; i++){
		*buffers[i] = getNextToken(&ptr);
	}
	return rowCount;
}
static void printHelp(void){
	printf("help print here\n");
}
static void parseStringCommand(struct DBController *const dbc, const char *const cmd){
	(void)dbc;
	printf("rcvd %s %p to parse\n", cmd, cmd);
	char **tokens;
	int tokenCount = tokenize(cmd, &tokens);
	printf("retrieved %u tokens\n", tokenCount);
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
