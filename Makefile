CC = gcc
TARGET = program.exe
SOURCES = $(DIR_SRC)/main.c $(DIR_SRC)/arguments_parser.c $(DIR_SRC)/building.c $(DIR_SRC)/vector.c $(DIR_SRC)/sorter.c $(DIR_SRC)/inout.c $(DIR_SRC)/generation.c
OBJECTS = $(SOURCES:$(DIR_SRC)/%.c=$(DIR_BUILD)/%.o) 
DIR_BUILD = build
DIR_SRC = src
DIR_HEADER = include

$(DIR_BUILD)/$(TARGET): $(OBJECTS) 
	$(CC) -o $@ $^ -I$(DIR_HEADER) 

$(DIR_BUILD)/%.o: $(DIR_SRC)/%.c
	$(CC) -c $^ -o $@ -I$(DIR_HEADER)

clean:
	rm $(OBJECTS) $(DIR_BUILD)/$(TARGET) 

.PHONY: clean 