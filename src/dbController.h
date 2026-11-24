
enum OPS{
	NOP,
	CREATE
};
struct Operator{
	int op;
	struct Operator *next;
};
struct Operand{
	char *ope;
	struct Operand *next;
};
struct View{
	struct Database *db;
	struct Relation *rel;
	int *selectedRows;
	int numSelectedRows;
	unsigned int *selectedColumns;
	unsigned int numSelectedColumns;
};
struct DBController{
	struct Database *currentDB;
	struct View *view;
	char uInput[255];
};
struct DBController *newDBController(struct Database *currentDB);
void dbcControlLoop(struct DBController *const dbc);

