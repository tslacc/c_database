#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <errno.h>
#include "lib_database.h"



struct Database *d;

//Get single int
int l_getint(){
	char buf[64];
	//Read at most 33 chars
	int i = 0; 
	int c = 0;
	while(i<32 && (c=getc(stdin))!='\n'){
		//printf("insert %d at %u\n", c, i);
		buf[i] = c;
		i++;
	}
	//printf("Not inserting char %d\n",c);
	if(c!='\n') {
		//printf("no endline reached. flush buffer\n");
		while((c=getc(stdin))!='\n'){
		//	printf("Read and discard c %d\n",c);
		}
		//printf("last c read is %d\n",c);
		return -1;
	}
	buf[i]='\0';
	return atoi(buf);
}
void table_loop(struct Table *tb){
	while(true){
		printf("Selected table: %s\n", tb->name);
		printf("1. Print all\n");
		printf("2. Add header\n");
		printf("3. Delete header\n");
		printf("4. Select record\n");
		printf("5. Return to main db\n");
		int u_ch = l_getint();
		switch(u_ch){
			case(1):
				printf("\t");
				for(int i = 0; i < tb->num_headers; i++){
					printf("%s\t", tb->headers[i]);
				}
				printf("\n");
				for(int i = 0; i < tb->num_records; i++){
					printf("%s\t",tb->records[i]->name);
					for(int j = 0; j < tb->num_headers; j++){
						printf("%s\t", tb->records[i]->values[j].as_int);
					}
					printf("\n");
				}
				break;
			case(2):
				printf("Skipping request header\n");
				break;
			case(3):
				printf("Header ID to remove:\n");
				printf("Not yet implemented\n");
				break;
			case(4):
				printf("Select record by num:\n");
				printf("Not yet implemented\n");
				break;
			case(5):
				return;
		}
	}
	return;
}
void main_loop(){
	while(true){
		printf("1. Add table\n");
		printf("2. Select table\n");
		printf("3. Print all tables\n");
		printf("4. Exit\n");
		printf("enter choice\n");
		int u_ch = l_getint();
		printf("u_ch %d\n", u_ch);
		switch(u_ch){
			case 1:
				//add table or ask user for input
				break;
			case 2:
				//Select table and enter sub-loop
				break;
			case 3:
				printf("List of tables n = %u\n", d->num_tables);
				for(int i = 0; i < d->num_tables; i++){
					printf(d->tables[i]->name);
				}
				break;
			case 4:
				return;
		}
	}
	return;
}
int main(int argc, char * argv[]){	
	d = new_db();
	main_loop();
	printf("End program\n");
	return 0;
}
