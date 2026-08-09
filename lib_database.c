#include "lib_database.h"

const int RESIZE_SCALE = 2;
struct Database *new_db(){
	struct Database *result = malloc(sizeof(struct Database));
	result->num_tables = 0;
	result->max_tables = 1;
	return result;
}
//For reuse purposes, Lookup will return null IFF there is no de-allocated table in this database.
//If there is a deallocated table, Lookup may return that pointer but pointing to null: if so, create a new table in that location.
struct Table *database_new_table(struct Database *db, const char *_name){
	struct Table *result = database_lookup_table(db, _name);
	if(result!=NULL){
		return result;
	}
	result = malloc(sizeof(struct Table *));
	if(db->max_tables <= db->num_tables){
		db->max_tables*=RESIZE_SCALE;
		db->tables=realloc(db->tables,(sizeof(struct Table)*db->max_tables));
	}
	db->tables[db->num_tables]=result;
	//TODO Change if this new table fills a hole instead;
	db->num_tables++;
	return result;
}
//TODO Implement
struct Table *database_lookup_table(const struct Database *db, const char *_name){
	return NULL;
}


struct Record *table_new_record(struct Table *tb, const char *_name, void *value){
	struct Record *result = table_lookup_record(tb, _name);
	if(result != NULL){
		return result;
	}
	result = malloc(sizeof(struct Record *));
	if(tb->max_records <= tb->num_records){
		tb->max_records*=RESIZE_SCALE;
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
