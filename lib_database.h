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
	char *(*to_bytes)(const struct Record*, const int num_headers);
};
struct Record *new_record(void);
struct Record *new_record_from_bytes(const char *data, const int num_headers);
void debug_print_record(const struct Record*, const int num_headers);
void debug_print_recordbytes(const char *buf, const int num_headers);
int debug_check_record_equality(const struct Record* rc, const struct Record* rc2, const int num_headers);

struct Table{
	char *name;
	char **headers;
	int headers_used;
	int headers_allocated;
	struct Record **records;
	int records_stored;
	int records_allocated;
	void (*allocate_new_headers)(struct Table *tb, const int amount);
	struct Record *(*make_record)(struct Table *);
	char *(*to_bytes)(const struct Table *);
};
struct Table *new_table(const int record_count, const int header_count);
struct Table *new_table_from_bytes(const char *data, const int record_count, const int header_count);

struct Database{
	struct Table **tables;
	int tables_stored;
	int tables_allocated;
	struct Table *(*make_new_table)(struct Database *db);
	char *(*to_bytes)(const struct Database *);
};

struct Database *new_database(const int tables_to_allocate);


#endif