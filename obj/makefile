CC = g++ -std=c++17
CARGS = -c -Wall
S = ../src/

OBJS = main.o ShaderSource.o
LIBS = -Llibs -lglfw3 -lglew32s -lgdi32 -luser32 -lkernel32 -lopengl32
TGP: $(OBJS)
	$(CC) -Wall -static $(OBJS) $(LIBS) -o ../TGP

DEPS =
main.o: $(S)main.cpp $(DEPS)
	$(CC) $(CARGS) $(S)main.cpp -o main.o

ShaderSource.o: $(S)ShaderSource.cpp
	$(CC) $(CARGS) $(S)ShaderSource.cpp -o ShaderSource.o