#include <stdlib.h>
#include <stdio.h>
#include "lib_database.h"
#define true 1
#define false 0
#define USERINPUTMAX 512

struct Database *d;
union{
	int as_int;
	char as_char[USERINPUTMAX];
}u_in;

void table_loop(){
	return;
}
void main_loop(){
	while(true){
		printf("1. Add table\n");
		printf("2. Select table\n");
		printf("3. Print all tables\n");
		printf("0. Exit\n");
		printf("enter choice\n");
		fgets(u_in.as_char, USERINPUTMAX, stdin);
		u_in.as_int = atoi(u_in.as_char);
		switch(u_in.as_int){
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
			case 0: 
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
