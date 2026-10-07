#ifndef LIB_DATABASE
#define LIB_DATABASE
#include <stdint.h>

struct Record{
	// Primary key
	char *name;
	uint32_t *values;
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
	int relations_stored;
	int relations_allocated;
};
struct Database *newDatabase(void);

#endif
