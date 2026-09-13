#ifndef LIB_DATABASE
#define LIB_DATABASE

union value{
	int as_int;
	float as_float;
	char as_char[sizeof(float)];
};

struct Record{
	char *name;
	union value *values;
};
void debug_print_record(const struct Record*, const int num_headers);
void debug_print_recordbytes(const char *buf, const int num_headers);
int debug_check_record_equality(const struct Record* rc, const struct Record* rc2, const int num_headers);

struct Table{
	char *name;
	char **headers;
	int headers_stored;
	int headers_allocated;
	struct Record **records;
	int records_stored;
	int records_allocated;
};

struct Database{
	struct Table **tables;
	int tables_stored;
	int tables_allocated;
};
void table_alloc_new_records(struct Table *tb, const int num);
void table_alloc_new_headers(struct Table *tb, const int num);
void database_alloc_new_tables(struct Database *db, const int tables_to_allocate);
struct Database *new_database(const int tables_to_allocate);
int record_equality(const struct Record *rc1, const struct Record *rc2, const int value_count);
int table_equality(const struct Table *tb1, const struct Table *tb2);
int database_equality(const struct Database *db1, const struct Database *db2);

#endif