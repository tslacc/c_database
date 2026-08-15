#ifndef LIB_DATABASE
#define LIB_DATABASE


union value{
	int as_int;
	float as_float;
	char as_char[sizeof(float)];
};

//Basic database containing a list of struct Record.
//Each record contains exactly one name and one value.
//TODO: A record can contain any number of values, up to the number of row headers present in the table.
struct Database{
	char *path;
	struct Table **tables;
	int num_tables;
	int max_tables;
	int (*fptr)(int);
	//TODO reconcile mismatch
	struct Table * (*lookup_or_new_table)(struct Database *db, const char *_name);
	int (*lookup_table_index)(const struct Database *db, const char *_name);
};
struct Table{
	char *name;
	char **headers;
	int num_headers;
	struct Record **records;
	int num_records;
	int max_records;
	//TODO reconcile mismatch
	struct Record * (*add_new_record)(struct Table *tb, const char *_name);
	int (*lookup_record_index)(const struct Table *tb, const char *_name);
};
struct Record{
	char *name;
	union value values[];
};
struct Database *new_db();
void debug_print();

#endif