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
struct Database *newDatabase(void);

#endif
