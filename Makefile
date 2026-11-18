# ----------+ FLAGS +----------
CFLAGS= -O2 -Wall -Wextra
CC= gcc
LIB= -lsqlite3

# ----------+ DIRS AND FILENAMES +----------
SRC = src
TARGET = artie

INGREDIENTS = db/input.ingr
MEALS = ./db/input.meal
PLANS = ./db/input.plan

# ----------+ LINKING & COMPILING +----------
$(TARGET) :
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)/main.c $(LIB)

# ----------+ CLEAN UP +----------
clean :
	rm -f $(BUILD)/*.o $(TARGET)

# ----------+ QUICK RUN +----------
ingredients : $(TARGET)
	./$(TARGET) $(INGREDIENTS)

meals : $(TARGET)
	./$(TARGET) $(MEALS)

plans : $(TARGET)
	./$(TARGET) $(PLANS)
