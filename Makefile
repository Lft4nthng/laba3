CC = gcc
TARGET = program
SOURCES = $(DIR_SRC)/main.c $(DIR_SRC)/arguments_parser.c
OBJECTS = $(SOURCES:$(DIR_SRC)/%.c=$(DIR_BUILD)/%.o)
DIR_BUILD = build
DIR_SRC = src
DIR_HEADER = include

$(DIR_BUILD)/$(TARGET): $(OBJECTS)
	$(CC) -o $@ $^ 

$(DIR_BUILD)/%.o: $(DIR_SRC)/%.c
	$(CC) -c $< -o $@ -I$(DIR_HEADER)

clean:
	rm -f $(OBJECTS) $(DIR_BUILD)/$(TARGET) 

.PHONY: clean 