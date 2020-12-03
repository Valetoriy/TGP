COMMON = g++ -std=c++17 -Wall
CARGS = -c
S = src/
O = obj/

OBJS = $(O)main.o $(O)ShaderSource.o
LIBS = -Llibs -lglfw3 -lglew32s -lgdi32 -luser32 -lkernel32 -lopengl32
TGP: $(OBJS)
	$(COMMON) -static $(OBJS) $(LIBS) -o TGP

DEPS =
main.o: $(S)main.cpp $(DEPS)
	$(COMMON) $(CARGS) $(S)main.cpp -o $(O)main.o

ShaderSource.o: $(S)ShaderSource.cpp
	$(COMMON) $(CARGS) $(S)ShaderSource.cpp -o $(O)ShaderSource.o