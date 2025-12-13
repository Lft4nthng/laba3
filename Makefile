CC = gcc
TARGET = program
SOURCES = main.c arguments_parser.c
OBJECTS = $(SOURCES:.c=.o)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^ 

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ -I.\

clean:
	rm -f $(OBJECTS) $(TARGET) 

.PHONY: clean 