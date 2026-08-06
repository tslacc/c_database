#include "lib_database.h"

struct Database *new_db(){
	struct Database *result = malloc(sizeof(struct Database));
	result->num.tables = 0;
	return result;
}
struct Table *lookup(const struct Database, const char *_name){
	return NULL;
}
void add(char *_name, void *value){
	return;
}
