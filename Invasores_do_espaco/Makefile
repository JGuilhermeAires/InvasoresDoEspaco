CC=gcc
CFLAGS=-std=c99 -I./cli-lib -I.
LDFLAGS=-lncursesw # <--- PARA ISTO  # Adiciona o linker flag para ncurses
SRC=main.c game.c keyboard.c cli-lib/cli-lib.c
TARGET=game       # Nome do executável mais comum no Linux (sem .exe)

all:
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET) $(LDFLAGS) # Agora LDFLAGS é -lncursesw

run:
	./$(TARGET)

clean: # Adicionado um alvo 'clean' para remover o executável
	rm -f $(TARGET)

