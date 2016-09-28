OUTPUT_NAME=program
CC=g++
OPENGL_FLAGS=-framework OpenGL -lglfw3 -lglew
APPLE_BULLSHIT=-L/usr/local/lib -I/usr/local/include


all: main.o application.o
	$(CC) application.o main.o $(APPLE_BULLSHIT) $(OPENGL_FLAGS) -o $(OUTPUT_NAME)

main.o: main.cpp
	$(CC) -c -Wall main.cpp $(APPLE_BULLSHIT) $(OPENGL_FLAGS)

application.o: application.cpp
	$(CC) -c -Wall application.cpp $(APPLE_BULLSHIT) $(OPENGL_FLAGS)

clean:
	rm *.o
