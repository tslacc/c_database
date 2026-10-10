#include "dbController.h"
#include "lib_database.h"
#include <stddef.h>
#include <stdlib.h>

// Get the next token from str and advance the pointer
static char *getNextToken(const char *str, const char *const strend){
	return NULL;
}
// return 0 for not a valid type, 1 for operator, 2 for operand
static int getTokenType(const char *str){
	return 0;
}
static int getOpFromToken(const char *const str){
	return NOP;
}
void parseStringCommand(const char *cmd, const int cmdsz){
	struct Operator *operatorStack = NULL;
	struct Operand *operandStack = NULL;
	
	const char *const cmdend = cmd+cmdsz;
	while(cmd < cmdend){
		char *nextToken = getNextToken(cmd, cmdend);
		switch(getTokenType(nextToken)){
			case 1:
				struct Operator *nextOperator = malloc(sizeof(struct Operator));
				nextOperator->next = operatorStack;
				operatorStack = nextOperator;
				nextOperator->op = getOpFromToken(nextToken);
				break;
			case 2:
				struct Operand *nextOperand = malloc(sizeof(struct Operand));
				nextOperand->next = operandStack;
				operandStack = nextOperand;
				// TODO FILL OPERAND
				break;
			default:
				break;
		}
	}
}
struct DBController *newDBController(struct Database *currentDB){
	struct DBController *result = malloc(sizeof(struct DBController));
	result->currentDB = currentDB;
	return result;
}
