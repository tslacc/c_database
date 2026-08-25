#include "lib_database.h"
#include <string.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
const int RESIZE_SCALE = 2;

//RECORDS	==========================================================================================================

static char *record_to_bytes(const struct Record *rc, const int num_headers){
	char *result = malloc(strlen(rc->name)+1+num_headers*sizeof(union value));
	memcpy(result, rc->name, strlen(rc->name));
	//Null terminate
	*(result+strlen(rc->name)+1) = '\0';
	//Copy the union values
	memcpy(result+strlen(rc->name)+1+1, rc->values, num_headers*sizeof(union value));
	return result;
}
//Allocate a new record.
//Do not populate any values except "name".
static struct Record *new_record(void){
	struct Record *result = malloc(sizeof(struct Record));
	result->to_bytes = record_to_bytes;
	return result;
}
struct Record *new_record_from_bytes(const int num_headers, const char *data, const int data_length){
	int idx = 0;
	//Name length check (null terminated)
	while(*(data+idx)!='\0'&&idx < data_length) idx++;
	if(idx >= data_length) return NULL;
	struct Record *rc = new_record();
	rc->name = malloc(idx);
	memcpy(rc->name, data, idx);
	idx++;
	//Copy in values
	rc->values = malloc(num_headers*sizeof(union value));
	memcpy(rc->values, data+idx+1, num_headers*sizeof(union value));
	return rc;
};


//TABLES	=========================================================================================================
//Searches for an empty slot to enter a new record or returns -1 if non exists.
static int table_search_blank(const struct Table *tb){
	//Basic linear search
	if(tb->num_records>=tb->max_records) return -1;
	for(int i = 0; i < tb->max_records; i++){
		if(tb->records[i]==NULL) return i;
	}
	return -1;
}
//Lookup a single record by name and return the first value.
static struct Record *table_lookup_record(const struct Table *tb, const char *_name){
	for(int i = 0; i < tb->num_records; i++){
		if(strcmp(tb->records[i]->name,_name)==0) return tb->records[i];
	}
	return NULL;
}
static void add_header(struct Table *tb, const char *_name){
	if(tb->num_headers>=tb->max_headers){
		tb->max_headers *= RESIZE_SCALE;
		tb->headers = realloc(tb->headers, (sizeof(char *)*tb->max_headers));
		for(int i = 0; i < tb->num_records; i++){
			tb->records[i]->values = realloc(tb->records[i]->values, sizeof(union value)*tb->max_headers);
		}
	}
	memcpy(tb->headers[tb->num_headers], _name, strlen(_name));
	return;
}
//Adds a new record to the table.
struct Record *table_new_record(struct Table *tb, const char *_name){
	int index = table_search_blank(tb);
	struct Record *result = new_record();
	result->name = malloc(strlen(_name));
	memcpy(result->name, _name, strlen(_name));
	if(index == -1){ //No space exists. Resize and allocate
		tb->max_records*=RESIZE_SCALE;
		tb->records=realloc(tb->records,(sizeof(struct Record)*tb->max_records));
		tb->records[tb->num_records] = result;
	} else {//index != -1 and a valid space exists.
		tb->records[index] = result;
	}
	tb->num_records++;
	result->values = malloc(sizeof(union value)*tb->num_headers);
	return result;
	
}
void remove_header(struct Table *tb, int pos){
	free(tb->headers[pos]);
	if(pos + 1 < tb->num_headers) { //There is a need to move data
		memmove(tb->headers[pos], tb->headers[pos+1], sizeof(char **)*(tb->num_headers-pos));
		for(int i = 0; i<tb->num_records; i++){
			//free(tb->records[i]->values[pos]);
			memmove(tb->records[i]->values+pos, tb->records[i]->values+pos+1, sizeof(union value)*(tb->num_headers-pos));	
		}
	}
	tb->num_headers--;
	return;
}
//Allocate a new table.
static struct Table *new_table(const char *name){
	struct Table *result = malloc(sizeof(struct Table));
	result->num_headers = 1;
	result->max_headers = 1;
	result->headers = malloc(sizeof(char *)*result->max_headers);
	result->max_records = 1;
	result->num_records = 1;
	result->records = malloc(sizeof(struct Record *)*result->max_records);
	result->add_new_record = NULL;
	result->lookup_record_index = NULL;
	result->remove_header = remove_header;
	return result;
}

//DATABASES =============================================================================================================================================================================================
static int database_search_blank(const struct Database *db){
	printf("Begin db search of %u/%u\n", db->num_tables, db->max_tables);
	//Basic linear search on unordered list
	if(db->num_tables>=db->max_tables) return -1;
	for(int i = 0; i < db->max_tables; i++){
		
		printf("db tables[%u] = %p\n", i, db->tables[i]);
		if(db->tables[i]==NULL) return i;
	}
	return -1;
}
static int database_lookup_table(const struct Database *db, const char *_name){
	for(int i = 0; i < db->num_tables; i++){
		if(strcmp(db->tables[i]->name,_name)==0) return i;
	}
	return -1;
}
//Either looks up the matching table or allocates a new table in the db matching the name..
static struct Table *database_new_table(struct Database *db, const char *_name){
	printf("Adding new table.\n");
	int index = database_search_blank(db);
	printf("Index search %u\n", index);
	struct Table *result = new_table(_name);
	printf("Gen new table at %p\n", result);
	if(index==-1){//No space exists. Expand and allocate
		printf("Expand and allocate");
		db->max_tables*=RESIZE_SCALE;
		db->tables=realloc(db->tables,(sizeof(struct Table)*db->max_tables));
		db->tables[db->num_tables] = result;
	} else { //num tables is ok
		printf("Num tables ok, direct place\n");
		db->tables[index] = result;
	}
	db->num_tables++;
	return result;
}
void write_db_to_file(void);

struct Database *new_db(void){
	struct Database *result = malloc(sizeof(struct Database));
	result->num_tables = 0;
	result->max_tables = 1;
	result->tables = malloc(sizeof(struct Table *)*result->max_tables);
	result->add_new_table = database_new_table;
	result->lookup_table_index = database_lookup_table;
	return result;
}

//WRITING TO FILE


