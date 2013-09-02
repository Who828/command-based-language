CC=gcc
CFLAGS=-c -Wall --std=c99
LDFLAGS=
SOURCES=example.c ../src/command_language.c
OBJECTS=$(SOURCES:.c=.o)
	EXECUTABLE=example

all: $(SOURCES) $(EXECUTABLE)
		
$(EXECUTABLE): $(OBJECTS) 
		$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.c.o:
		$(CC) $(CFLAGS) $< -o $@

