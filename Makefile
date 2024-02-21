CC = gcc
CFLAGS = -Wall -Iinclude
OBJ = src/bitmap.o src/main.o src/templateCode.c src/listComponent.c src/connectionsFinder.c
TARGET = pcb_check

SRC_DIR = src
OBJ_DIR = A3

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

OBJ_DIR/%.o: SRC_DIR/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f src/*.o $(TARGET)

