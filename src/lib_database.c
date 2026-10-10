#include "lib_database.h"
#include <stdlib.h>
#include <string.h>

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
