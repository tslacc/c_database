#include "lib_database.h"
#include <string.h>
#include <stddef.h>
#include <stdlib.h>

const int RESIZE_SCALE = 2;

//RECORDS	==========================================================================================================
//Allocate a new record.
//Do not populate any values except "name".
static struct Record *new_record(const char *name){
	struct Record *result = malloc(sizeof(struct Record));
	memcpy(result->name, name, strlen(name));
	return result;
}

//TABLES	=========================================================================================================
//Searches for an empty slot to enter a new record or returns -1 if non exists.
static int table_search_blank(const struct Table *tb){
	return -1;
}
//TODO change to string-based parsing
//Lookup a single record by name and return the first value.
static struct Record *table_lookup_record(const struct Table *tb, const char *_name){
	return NULL;
}
//Adds a new record to the table.
struct Record *table_new_record(struct Table *tb, const char *_name){
	int index = table_search_blank(tb);
	struct Record *result = new_record(_name);
	if(index == -1){ //No space exists. Resize and allocate
		tb->max_records*=RESIZE_SCALE;
		tb->records=realloc(tb->records,(sizeof(struct Record)*tb->max_records));
		tb->records[tb->num_records] = result;
	} else {//index != -1 and a valid space exists.
		tb->records[index] = result;
	}
	tb->num_records++;
	return result;
	
}

//Allocate a new table.
static struct Table *new_table(const char *name){
	struct Table *result = malloc(sizeof(struct Table));
	result->max_records = result->num_records = 1;
	result->add_new_record = NULL;
	result->lookup_record_index = NULL;
	return result;
}

//DATABASES =============================================================================================================================================================================================
static int database_search_blank(const struct Database *db){
	return -1;
}
static int database_lookup_table(const struct Database *db, const char *_name){
	return -1;
}
//Either looks up the matching table or allocates a new table in the db matching the name..
static struct Table *database_new_table(struct Database *db, const char *_name){
	int index = database_lookup_table(db, _name);
	struct Table *result = new_table(_name);
	if(index==-1){//No space exists. Expand and allocate
		db->max_tables*=RESIZE_SCALE;
		db->tables=realloc(db->tables,(sizeof(struct Table)*db->max_tables));
		db->tables[db->num_tables] = result;
	} else { //num tables is ok
		db->tables[index] = result;
	}
	db->num_tables++;
	return result;
}

struct Database *new_db(){
	struct Database *result = malloc(sizeof(struct Database));
	result->num_tables = 0;
	result->max_tables = 1;
	result->lookup_or_new_table = database_new_table;
	result->lookup_table_index = database_lookup_table;
	return result;
}



