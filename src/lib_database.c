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
struct Record *relationMakeRecord(struct Relation *const rel, const char *const name){
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
static void freeRecord(struct Record *rec){
	free(rec->name);
	free(rec->values);
}
static void freeRelation(struct Relation *rel){
	for(unsigned int i = 0; i < rel->fieldsUsed; i++){
		if(rel->fields[i]!=NULL){
			free(rel->fields);
			rel->fields[i] = NULL;
		}
	}
	for(unsigned int i = 0; i < rel->recordsUsed; i++){
		if(rel->records[i]!=NULL){
			freeRecord(rel->records[i]);
			rel->records[i] = NULL;
		}
	}
	free(rel);
}
struct Relation *dbMakeRelation(struct Database *const db, const char *name, const uint32_t numFields){
#include <stdio.h>
	printf("Making relation 54\n");
	struct Relation *result = newRelation(name, numFields);
	db->relationsAllocated++;
	db->relations = realloc(db->relations, sizeof(struct Relation *));
	*(db->relations+db->relationsUsed) = result;
	db->relationsUsed++;
	return result;
}
void databaseDropRelation(struct Database *const db, const struct Relation *const rel){
	unsigned int i = 0;
	for(;i < db->relationsUsed; i++){
		if(db->relations[i]==rel){
			freeRelation(db->relations[i]);
			while(i < db->relationsUsed-1){
				db->relations[i] = db->relations[i+1];
				i++;
			}
			return;
		}
	}
}
struct Database *newDatabase(void){
	struct Database *result = malloc(sizeof(struct Database));
	return result;
}
