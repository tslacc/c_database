#ifndef LIBCONSOLEINPUT
#define LIBCONSOLEINPUT
#include <stddef.h>

struct consoleInput{
	void (*consoleLineToBuffer)(char *const buffer, const size_t sz);
};
extern struct consoleInput api_console;

#endif
