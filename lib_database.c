#include "lib_database.h"
#include <string.h>
#include <stddef.h>
#include <stdlib.h>

const int RESIZE_SCALE = 2;

//TODO Implement
//Modification: now returns the integer offset of the pointer to EITHER a complete match (Table exists and name matches) or a blank table (Table doesn't exist but resize isn't needed)
static int database_lookup_table(const struct Database *db, const char *_name){
	return -1;
}

//Either looks up the matching table or allocates a new table in the db matching the name..
static struct Table *database_lookup_or_new_table(struct Database *db, const char *_name){
	int index = database_lookup_table(db, _name);
	if(index!=-1 && db->tables[index] != NULL){ //A table already exists
		return db->tables[index];
	} else if (index!=-1 && db->tables[index] == NULL) { //A table doesn't already exist, but *result points to NULL and therefore can be changed to point to a new struct.
		db->tables[index] = malloc(sizeof(struct Table));
		db->num_tables++;
		return db->tables[index];
	} else { //No table exists: resize and allocate.
		if(db->max_tables <= db->num_tables){
			db->max_tables*=RESIZE_SCALE;
			db->tables=realloc(db->tables,(sizeof(struct Table)*db->max_tables));
		}
		db->tables[db->num_tables] = malloc(sizeof(struct Table));
		db->num_tables++;
		return db->tables[db->num_tables-1];
	}
		
}
static struct Table *new_table(const char *name){
	struct Table *result = malloc(sizeof(struct Table));
	result->max_records = result->num_records = 1;
	result->add_new_record = NULL;
	result->lookup_record_index = NULL;
	return result;
}
static struct Record *new_record(const char *name){
	struct Record *result = malloc(sizeof(struct Record));
	memcpy(result->name, name, strlen(name));
	result->value.as_int = 0;
	return result;
}
struct Database *new_db(){
	struct Database *result = malloc(sizeof(struct Database));
	result->num_tables = 0;
	result->max_tables = 1;
	result->lookup_or_new_table = database_lookup_or_new_table;
	result->lookup_table_index = database_lookup_table;
	return result;
}
//TODO finish implementing logic
struct Record *table_new_record(struct Table *tb, const char *_name, void *value){
	int index = tb->lookup_record_index(tb, _name);
	
	if(index == -1){ //no record exists and no space exists, realloc
		return NULL;
	} else if(index != -1 && tb->records[index]==NULL){ //No record exists but space exists. Allocate object
		
	} else { //Matching record already exists. Return this struct.
		return tb->records[index];
	}
	struct Record *result = malloc(sizeof(struct Record *));
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
