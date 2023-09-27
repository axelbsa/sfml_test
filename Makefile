CC=clang++

# Linux
CFLAGS=-mavx -g -Wall -std=c++11 -Wno-missing-braces -I /home/axelbs/src/SFML-2.5.1/include/ -L/home/axelbs/src/SFML-2.5.1/lib/
LFLAGS=-lsfml-graphics -lsfml-window -lsfml-audio -lsfml-system -lGL -lX11 -lm -ldl -lpthread

$(echo \"TEST\")

ifeq ($(OS),Windows_NT)
    CFLAGS= -mavx -g -Wall -std=gnu++11 -Wno-missing-braces
    LFLAGS=-lsfml-graphics -lsfml-window -lsfml-audio -lsfml-system -lopengl32 -lm -lpthread
else
	UNAME_S := $(shell uname -s)
    ifeq ($(UNAME_S),Darwin)
        CFLAGS=-std=c++17 -O2 -Wall -I/opt/local/include/
        LFLAGS=-L/opt/local/lib -lsfml-graphics -lsfml-window -lsfml-system -framework OpenGL -framework Cocoa -framework IOKit -framework CoreAudio -framework CoreVideo
    endif
endif

SOURCES=main.cpp
BINARY=grfx

all:
	$(CC) $(SOURCES) $(CFLAGS) $(LFLAGS) -o $(BINARY)

debug:
	$(CC) -DDEBUG $(SOURCES) $(CFLAGS) $(LFLAGS) -o $(BINARY)

clean:
	del $(BINARY)
