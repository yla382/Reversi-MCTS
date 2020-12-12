output: main.o
	g++ -std=c++11 main.o -o output
main.o: main.cpp node.h mcts.h
	g++ -c main.cpp
clean:
	rm *.o output
