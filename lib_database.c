#include "lib_database.h"

struct Database *new_db(){
	struct Database *result = malloc(sizeof(struct Database));
	result->num_tables = 0;
	return result;
}
struct Record *table_new_record(struct Table *tb, const char *_name, void *value){
	struct Record *result = table_lookup_record(tb, _name);
	if(result != NULL){
		return result;
	}
	result = malloc(sizeof(struct Record *));
	if(tb->max_records <= tb->num_records){
		tb->max_records*=2;
		tb->records=realloc(tb->records,(sizeof(struct Record)*tb->max_records));

	}
	tb->records[tb->num_records] = result;
	tb->num_records++;
	return result;
}
struct Record *table_lookup_record(const struct Table *tb, const char *_name){
	return NULL;
}
void add(char *_name, void *value){
	return;
}
