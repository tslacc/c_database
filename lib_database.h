#ifndef LIB_DATABASE
#define LIB_DATABASE

#include <stddef.h>
#include <stdlib.h>
//Basic database containing a list of struct Record.
//Each record contains exactly one name and one value.

struct Database{
	char *path;
	struct Table **tables;
	int num_tables;
	int max_tables;
};
struct Table{
	char *name;
	struct Record **records;
	int num_records;
	int max_records;
};
struct Record{
	char *name;
	union{
		int as_int;
		float as_float;
		char as_char[sizeof(float)];
	} value;
};
struct Database *new_db();
struct Table *database_lookup_or_new_table(struct Database *db, const char *_name);
int database_lookup_table(const struct Database *db, const char *_name);

struct Record *table_new_record(struct Table *tb, const char *_name, void *value);
struct Record *table_lookup_record(const struct Table *tb, const char *_name);

void debug_print();

#endif