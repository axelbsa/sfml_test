CC=g++
CFLAGS=-mavx -g -Wall -std=c++11 -Wno-missing-braces -I /home/axelbs/src/SFML-2.5.1/include/ -L/home/axelbs/src/SFML-2.5.1/lib/
#LFLAGS=-lraylib -lopengl32 -lraylib -lglfw3 -lgdi32

# linux
#LFLAGS=-static-libgcc -static-libstdc++ -lfreetype -ljpeg -lopenal32 -lFLAC -lvorbisenc -lvorbisfile -lvorbis -logg -lsfml-graphics-s -lsfml-window-s -lsfml-audio-s -lsfml-system-s -lGL -lX11 -lm -ldl -lpthread
LFLAGS=-lsfml-graphics -lsfml-window -lsfml-audio -lsfml-system -lGL -lX11 -lm -ldl -lpthread

ifeq ($(OS),Windows_NT)
	CFLAGS= -mavx -g -Wall -std=gnu++11 -Wno-missing-braces
	LFLAGS=-lsfml-graphics -lsfml-window -lsfml-audio -lsfml-system -lopengl32 -lm -lpthread
endif

SOURCES=main.cpp

all:
	$(CC) $(SOURCES) $(CFLAGS) $(LFLAGS) -o main

debug:
	$(CC) -DDEBUG $(SOURCES) $(CFLAGS) $(LFLAGS) -o main

clean:
	del main
