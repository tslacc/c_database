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
#endif