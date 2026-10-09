#include "lib_database.h"
#include <stdlib.h>
#include <string.h>

struct Record{
	// Primary key
	char *name;
	unsigned long int *values;
};

struct Relation{
	char *name;
	char **fields;
	int fieldsUsed;
	int fieldsAllocated;
	struct Record **records;
	int recordsUsed;
	int recordsAllocated;
};
struct Database{
	struct Relation **relations;
	int relationsUsed;
	int relationsAllocated;
};
static struct Record *newRecord(const char *name, const uint32_t numFields){
	struct Record *result = malloc(sizeof(struct Record));
	result->name = malloc(strlen(name)+1);
	memcpy(result->name, name, strlen(name)+1);
	result->values = malloc(sizeof(uint32_t)*numFields);
	return result;
}

static struct Relation *newRelation(const char *name, const uint32_t numFields){
	struct Relation *result = malloc(sizeof(struct Relation));
	result->name = malloc(strlen(name)+1);
	memcpy(result->name, name, strlen(name)+1);
	result->fields = malloc(sizeof(char *)*numFields);
	result->fieldsUsed = 0;
	result->fieldsAllocated = numFields;
	return result;
}

struct Database *newDatabase(void){
	struct Database *result = malloc(sizeof(struct Database));
	return result;
}

static void DatabaseMakeRelation(struct Database *db, const char *name, const uint32_t numFields){
	struct Relation *result = newRelation(name, numFields);
	db->relationsAllocated++;
	
	db->relations = realloc(db->relations, sizeof(struct Relation *));
	*(db->relations+db->relationsUsed) = result;
	db->relationsUsed++;
}
enum OPS{
	NOP,
	CREATE
};
struct Operator{
	int op;
	struct Operator *next;
};
struct Operand{
	char *ope;
	struct Operand *next;
};
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
static void parseStringCommand(const char *cmd, const int cmdsz){
	struct Operator *operatorStackBase;
	operatorStackBase = malloc(sizeof(struct Operator));
	operatorStackBase->op = NOP;
	struct Operator *operatorStack = operatorStackBase;
	struct Operand *operandStackBase;
	operandStackBase = malloc(sizeof(struct Operator));
	struct Operand *operandStack = operandStackBase;
	
	const char *const cmdend = cmd+cmdsz;
	while(cmd < cmdend){
		char *nextToken = getNextToken(cmd, cmdend);
		switch(getTokenType(nextToken)){
			case 1: 
				operatorStack->next = malloc(sizeof(struct Operator));
				operatorStack->next->op = getOpFromToken(nextToken);
				break;
			case 2:
				operandStack->next = malloc(sizeof(struct Operand));
				// TODO FILL OPERAND
				operandStack = operandStack->next;
			default:
				continue;
		}
	}
}
