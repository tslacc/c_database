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
// Add a new record slot to rel and return its index.
static int relationExpandRecords(struct Relation *const rel){
	rel->records = realloc(rel->records, sizeof(struct Record *)*rel->recordsUsed+1);
	rel->recordsUsed++;
	return rel->recordsUsed-1;
}
static struct Record *RelationMakeRecord(struct Relation *const rel, const char *const name){
	struct Record *r = newRecord(name, rel->fieldsUsed);
	rel->records[relationExpandRecords(rel)] = r;
	return r;
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

static void dbmakerelation(struct Database *const db, const char *name, const uint32_t numFields){
	struct Relation *result = newRelation(name, numFields);
	db->relationsAllocated++;
	db->relations = realloc(db->relations, sizeof(struct Relation *));
	*(db->relations+db->relationsUsed) = result;
	db->relationsUsed++;
}

struct Database *newDatabase(void){
	struct Database *result = malloc(sizeof(struct Database));
	result->makeRelation = dbmakerelation;
	return result;
}
