CC=gcc
TARGET=main.exec
FLAGS=-Wall
INCLUDE=include
SRC=src

$(TARGET): bin/main.o bin/building.o bin/gameHandler.o bin/helecopter.o bin/missilePad.o bin/soldier.o bin/utils.o makefile
	gcc bin/*.o -o $(TARGET) -lSDL2main -lSDL2 -lSDL2_image
bin/%.o: src/%.c 
	$(CC) $(FLAGS) -o $@ $^ -c -I $(INCLUDE)
clean:
	rm bin/*.o
