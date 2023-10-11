CC=gcc
TARGET=main.exe
FLAGS=-Wall
INCLUDE=include
SRC=src

$(TARGET): include/*.h bin/main.o bin/building.o bin/gameHandler.o bin/helecopter.o bin/missilePad.o bin/soldier.o bin/utils.o makefile
	gcc bin/*.o -o $(TARGET) -L C:\SDL\SDL2-mingw32\lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image
bin/%.o: src/%.c 
	$(CC) $(FLAGS) -o $@ $^ -c -I $(INCLUDE) -I C:\SDL\SDL2-mingw32\include -I C:\SDL\SDL_image-mingw32\include
clean:
	del bin\*.o