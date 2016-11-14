dijkstra.exe: usegraph.o graph.o heap.o hash.o
	g++ -o dijkstra.exe usegraph.o graph.o heap.o hash.o

usegraph.o: usegraph.cpp
	g++ -c usegraph.cpp --std=c++11

graph.o: graph.cpp
	g++ -c graph.cpp --std=c++11

heap.o: heap.cpp heap.h
	g++ -c heap.cpp --std=c++11

hash.o: hash.cpp hash.h
	g++ -c hash.cpp --std=c++11

debug:
	g++ -g -o useHeapDebug.exe useHeap.cpp heap.cpp hash.cpp

clean:
	rm -f *.exe *.o *.stackdump *~

backup:
	test -d backups || mkdir backups
	cp *.cpp backups
	cp *.h backups
	cp Makefile backups
