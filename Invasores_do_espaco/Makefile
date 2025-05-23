CC=gcc
CFLAGS=-std=c99 -I./cli-lib -I.
LDFLAGS=-lncursesw 
SRC=main.c game.c keyboard.c cli-lib/cli-lib.c
TARGET=game       

all:
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET) $(LDFLAGS) # Agora LDFLAGS é -lncursesw

run:
	./$(TARGET)

clean: 
	rm -f $(TARGET)

