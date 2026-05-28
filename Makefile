CC = gcc
CFLAGS = -I include
SRC = main.c src/*.c
TARGET = hospital_system

all:
	$(CC) $(SRC) $(CFLAGS) -o $(TARGET)

run: all
	./$(TARGET)

clean:
	rm -f $(TARGET)