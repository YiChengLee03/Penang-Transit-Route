CPPINCLUDE = /opt/homebrew/include

all: run

run: main.o adjacencyList.o
	g++ -o run main.o adjacencyList.o

main.o: adjacencyList.o main.cpp
	g++ -c main.cpp -I ${CPPINCLUDE}

adjacencyList.o: adjacencyList.h adjacencyList.cpp
	g++ -c adjacencyList.cpp -I ${CPPINCLUDE}

clean: 
	rm *.o, run