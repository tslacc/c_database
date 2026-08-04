//Basic database containing a list of struct Record.
//Each record contains exactly one name and one value.

struct Record{
	char *name;
	union{
		int as_int;
		float as_float;
		char as_char[sizeof(float)];
	} value;
};

void lookup();
void add(char *_name, void *value);
