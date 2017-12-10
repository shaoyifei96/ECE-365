Graph.out: main.o graph.o heap.o hash.o
	g++ -o Graph.exe main.o graph.o heap.o hash.o

main.o: main.cpp
	g++ -c main.cpp

graph.o: graph.cpp graph.h
	g++ -c graph.cpp

heap.o: heap.cpp heap.h
	g++ -c heap.cpp

hash.o: hash.cpp hash.h
	g++ -c hash.cpp

debug:
	g++ -g -o GraphDebug.exe main.cpp graph.cpp heap.cpp hash.cpp

clean:
	rm -f *.exe *.o *.stackdump *~