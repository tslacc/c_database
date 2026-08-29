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
struct Record *new_record(void){
	struct Record *result = malloc(sizeof(struct Record));
	result->to_bytes = record_to_bytes;
	return result;
}
struct Record *new_record_from_bytes(const char *data, const int num_headers){
	int idx = 0;
	//Name length check (null terminated)
	while(*(data+idx)!='\0') idx++;
	struct Record *rc = new_record();
	rc->name = malloc(idx);
	memcpy(rc->name, data, idx);
	idx++;
	//Copy in values
	rc->values = malloc(num_headers*sizeof(union value));
	memcpy(rc->values, data+idx+1, num_headers*sizeof(union value));
	return rc;
};
void debug_print_record(const struct Record* rc, const int num_headers){
	printf("%p %s\nValues:", rc, rc->name);
	for (int i = 0; i<num_headers; i++){
		printf("\n\t%d", *(rc->values+i));
	}
	printf("\n");
}
void debug_print_recordbytes(const char *buf, const int num_headers){
	int max = strlen(buf)+1+num_headers*sizeof(union value);
	int i = 0;
	for (; i<max; i++){
		printf("%d ", *(buf+i));
	}
	printf("\n");
}
int debug_check_record_equality(const struct Record* rc, const struct Record* rc2, const int num_headers){
	if(strcmp(rc->name,rc2->name)!=0) return 0;
	for(int i = 0; i<num_headers; i++){
		if(rc->values[i].as_float!=rc2->values[i].as_float) return 0;
	}
	return 1;
}
static void table_expand(struct Table *tb){
	tb->records_allocated *= RESIZE_SCALE;
	tb->records = realloc(tb->records, sizeof(struct Record)*tb->records_allocated);
	return;
}
static struct Record *table_make_record(struct Table *tb){
	struct Record *result = new_record();
	if(tb->records_used >= tb->records_allocated){
		table_expand(tb);
	}
	tb->records[tb->records_used] = result;
	result->values = malloc(sizeof(union value)*tb->headers_used);
	tb->records_used++;
	return result;
	
}
static char *table_to_bytes(const struct Table *tb){
	return NULL;
}
struct Table *new_table(const int record_count, const int header_count){
	struct Table *result = malloc(sizeof(struct Table));
	result->headers = malloc(sizeof(char *)*header_count);
	result->headers_used = 0;
	result->headers_allocated = header_count;
	result->records = malloc(sizeof(struct Record)*record_count);
	result->records_used = 0;
	result->records_allocated = record_count;
	result->make_record = table_make_record;
	result->to_bytes = table_to_bytes;
	return result;
}