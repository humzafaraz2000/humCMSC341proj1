CXX = g++
CXXFLAGS = -Wall

mytest: EntryList.o Graph.o mytest.cpp
	$(CXX) $(CXXFLAGS) EntryList.o Graph.o mytest.cpp -o mytest

proj1: EntryList.o Graph.o driver1.cpp
	$(CXX) $(CXXFLAGS) EntryList.o Graph.o driver1.cpp -o proj1

Graph.o: EntryList.o Graph.h Graph.cpp
	$(CXX) $(CXXFLAGS) -c Graph.cpp

EntryList.o: EntryList.h EntryList.cpp
	$(CXX) $(CXXFLAGS) -c EntryList.cpp

run:
	./proj1

test:
	./mytest

val:
	valgrind ./proj1
