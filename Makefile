CC=g++
CXXFLAGS=-g
LDFLAGS=-g

all: netplan

netplan: graphs.o

graph.o:  vertex.hpp graphs.hpp epdges.hpp graphs.cpp

vertex.o: edges.hpp vertex.hpp 

edge.o: vertex.hpp edges.hpp 

clean:
	rm -f netplan *.o core*


