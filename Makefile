# ----------+ FLAGS +----------
CFLAGS = -O2 -Wall -Wextra
INCLUDE = -Ilib
CC = gcc
LIB = -lsqlite3
CHOPDAT = lib/chopdat
DVECTOR = lib/dvector

# ----------+ INPUT FILES +----------

INGREDIENTS = db/i.csv
MEALS = ./db/m.csv
PLANS = ./db/p.csv

# ----------+ LINKING & COMPILING +----------
all : artie

artie : main.o artie.o chopdat.o dvector_ptr.o
	$(CC) $(CFLAGS) main.o chopdat.o dvector_ptr.o -o artie $(LIB)
	etags *.[ch]

artie.o : artie.c artie.c
	$(CC) $(CFLAGS) $(INCLUDE) -c artie.c -o artie.o

chopdat.o : $(CHOPDAT)/chopdat.c $(CHOPDAT)/chopdat.h
	$(CC) $(CFLAGS) $(INCLUDE) -c $(CHOPDAT)/chopdat.c -o chopdat.o

dvector_ptr.o : $(DVECTOR)/dvector_ptr.c $(DVECTOR)/dvector.h
	$(CC) $(CFLAGS) $(INCLUDE) -c $(DVECTOR)/dvector_ptr.c -o dvector_ptr.o

main.o : main.c $(CHOPDAT)/chopdat.h $(DVECTOR)/dvector.h
	$(CC) $(CFLAGS) $(INCLUDE) -c main.c -o main.o

# ----------+ CLEAN UP +----------
clean :
	rm -f *.o artie

# ----------+ QUICK RUN +----------
ingredients : artie
	./artie $(INGREDIENTS)

meals : artie
	./artie $(MEALS)

plans : artie
	./artie $(PLANS)
