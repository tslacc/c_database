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
	void (*from_bytes)(const char*, const int num_headers, const char *data, const int data_length);
};
//Basic database containing a list of struct Record.
//Each record contains exactly one name and one value.
struct Database{
	char *path;
	struct Table **tables;
	int num_tables;
	int max_tables;
	struct Table * (*add_new_table)(struct Database *db, const char *_name);
	int (*lookup_table_index)(const struct Database *db, const char *_name);
	void (*write_to_file)(const struct Database *db, const char *_path);
	void (*read_from_file)(struct Database *db, const char *_path);
};
struct Table{
	char *name;
	char **headers;
	int num_headers;
	int max_headers;
	struct Record **records;
	int num_records;
	int max_records;
	struct Record * (*add_new_record)(struct Table *tb, const char *_name);
	int (*lookup_record_index)(const struct Table *tb, const char *_name);
	void (*remove_header)(struct Table *tb, int index);
};

struct Database *new_db();


void debug_print();

#endif