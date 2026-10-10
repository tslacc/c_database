
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
	struct Database *selectedDB;
	int *selectedRows;
	int numSelectedRows;
	int *selectedColumns;
	int numSelectedColumns;
};
struct DBController{
	struct Database *currentDB;
	struct View *currentView;	
};
struct DBController *newDBController(struct Database *currentDB);
void parseStringCommand(const char *cmd, const int cmdsz);
