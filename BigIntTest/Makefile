CC= g++
CFLAGS= -ggdb -std=c++11

run: prueba.o
	$(CC) $^ -o $@ $(CFLAGS)

%.o: %.cpp
	$(CC) $< -c -o $@ $(CFLAGS)
