CC=g++
CFLAGS=-std=c++11 -Wall -Wextra
LIBS=-lGL -lGLEW -lglfw
ENGINE_SRC=engine.cpp
CAMERA_SRC=camera.cpp

all: camera engine

engine:
	$(CC) $(CFLAGS) $(ENGINE_SRC) -c

camera:
	$(CC) $(CFLAGS) $(CAMERA_SRC) -c

clean:
	rm *.o
