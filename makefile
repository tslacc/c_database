outdir = /tmp/build/
srcdir = ./src/
objects = $(outdir)libdatabase.o

$(outdir)main.out: $(outdir) $(srcdir)main.c $(objects)
	gcc -Wall -Wextra -o $(outdir)main.out $(srcdir)main.c $(objects)

$(outdir)libdatabase.o: $(srcdir)lib_database.c $(srcdir)lib_database.h
	gcc -Wall -Wextra -shared -fpic -o $(outdir)libdatabase.o $(srcdir)lib_database.c

$(outdir):
	mkdir -p $(outdir)

.PHONY: clean
clean:
	rm main.out $(objects)
