#include "lib_database.h"
#include <string.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
const int RESIZE_SCALE = 2;

//RECORDS	==========================================================================================================
//Helper function to return the size of the byte record
static int sizeof_record_bytes(const struct Record *rc, const int num_headers){
	return strlen(rc->name)+1+num_headers*sizeof(union value);
}

static char *record_to_bytes(const struct Record *rc, const int num_headers){
	char *result = malloc(sizeof_record_bytes(rc, num_headers));
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
static int sizeof_table_bytes(const struct Table* tb){
	int sum = 0;
	if(tb->name == NULL){
		sum += 1;
	} else {
		sum += strlen(tb->name)+1;
	}
	sum += sizeof(unsigned int);
	for(int i = 0; i<tb->headers_used; i++){
		sum += strlen(tb->headers[i])+1;
	}
	sum += sizeof(tb->records_stored);
	for(int i = 0; i<tb->records_stored; i++){
		sum += sizeof(unsigned int);
		sum += sizeof_record_bytes(tb->records[i], tb->headers_used);
	}	
	return sum;
}
static void table_allocate_new_headers(struct Table *tb, const int amount){
	if(tb->headers_used+amount > tb->headers_allocated){
		while(tb->headers_used+amount > tb->headers_allocated)
			tb->headers_allocated *= RESIZE_SCALE;
		tb->headers = realloc(tb->headers, tb->headers_allocated*sizeof(char*));
	}
	tb->headers_used += amount;
	return;
}
static struct Record *table_make_record(struct Table *tb){
	struct Record *result = new_record();
	if(tb->records_stored == tb->records_allocated){
		if(tb->records_allocated == 0)
			tb->records_allocated = 1;
		else
			tb->records_allocated *= RESIZE_SCALE;
		tb->records = realloc(tb->records, sizeof(char*)*tb->records_allocated);
	}
	tb->records[tb->records_stored] = result;
	tb->records_stored++;
	return result;
}
static char *table_to_bytes(const struct Table *tb){
	union{
		unsigned int as_int;
		char as_char[sizeof(int)];
	} int_convert;
	char *result = malloc(sizeof_table_bytes(tb));
	memset(result, 0, sizeof_table_bytes(tb));
	int idx = 0;
	if(tb->name == NULL){
		*(result+idx) = 0;
		idx+=1;
	} else {
		memcpy(result+idx, tb->name, strlen(tb->name));
		idx += strlen(tb->name);
		*(result+idx) = 0;
		idx += 1;
	}
	//write num headers
	int_convert.as_int = tb->headers_used;
	memcpy(result+idx, int_convert.as_char, sizeof(int));
	idx+=sizeof(tb->headers_used);	
	for(int i = 0; i < tb->headers_used; i++){
		memcpy(result+idx, (tb->headers)+i, strlen(*(tb->headers+i)));
		idx += strlen(*(tb->headers+i));
		*(result+idx) = 0;
		idx += 1;
	}
	//write num records
	int_convert.as_int = tb->records_stored;
	memcpy(result+idx, int_convert.as_char, sizeof(unsigned int));
	idx+=sizeof(unsigned int);
	for(int i = 0; i < tb->records_stored; i++){
		int sz_next_record = sizeof_record_bytes(tb->records[i], tb->headers_used);
		int_convert.as_int = sz_next_record;
		memcpy(result+idx, int_convert.as_char, sizeof(int));
		idx += sizeof(int);
		
		char *tmp_char = tb->records[i]->to_bytes(tb->records[i], tb->headers_used);
		memcpy(result+idx, tmp_char, sz_next_record);
		free(tmp_char);
		idx += sz_next_record;
	}
	return result;
}
struct Table *new_table(const int record_count, const int header_count){
	struct Table *result = malloc(sizeof(struct Table));
	result->name = malloc(sizeof(char));
	result->headers_allocated = header_count;
	result->headers = malloc(sizeof(char *)*result->headers_allocated);
	result->headers_used = 0;
	result->records = malloc(sizeof(struct Record)*record_count);
	result->records_stored = 0;
	result->records_allocated = record_count;
	result->allocate_new_headers = table_allocate_new_headers;
	result->make_record = table_make_record;
	result->to_bytes = table_to_bytes;
	return result;
}

//Database ==================================================================

struct Database *new_database(const int tables_to_allocate){
	struct Database *result = malloc(sizeof(struct Database));
	result->tables_stored = 0;
	result->tables_allocated = tables_to_allocate;
	result->tables = malloc(tables_to_allocate*sizeof(struct Table*));
	return result;
}