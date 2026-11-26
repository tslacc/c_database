#ifndef LIBDATABASE
#define LIBDATABASE
#include <stdint.h>

struct Record{
	// Primary key
	char *name;
	unsigned long int *values;
};
struct Relation{
	char *name;
	char **fields;
	unsigned int fieldsUsed;
	unsigned int fieldsAllocated;
	struct Record **records;
	unsigned int recordsUsed;
	unsigned int recordsAllocated;
};
struct Database{
	struct Relation **relations;
	unsigned int relationsUsed;
	unsigned int relationsAllocated;
	void (*makeRelation)(struct Database *const db, const char *name, const uint32_t numFields);
};
struct Relation *dbMakeRelation(struct Database *const db, const char *const name, const uint32_t numFields);
struct Record *relationMakeRecord(struct Relation *const rel, const char *const name);
void databaseDropRelation(struct Database *const db, const struct Relation *const rel);
struct Database *newDatabase(void);

#endif
