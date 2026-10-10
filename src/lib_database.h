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
struct Database *newDatabase(void);

#endif
