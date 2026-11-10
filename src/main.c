#include "lib_database.h"
#include "lib_consoleInput.h"
#include "dbController.h"
#include "strTokenizer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){	
	struct Database *db = newDatabase();
	struct DBController *dbc = newDBController(db);
	// loop and accept commands
	dbcControlLoop(dbc);
	
	free(db);
	free(dbc);
}
