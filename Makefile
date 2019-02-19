#can be overridden by using 'make CXX=gcc-8' or so
CXX=g++

#append these flags to flags passed through command line
override CXXFLAGS+=-O3 --std=c++17

PREFIX=/usr/local

all: configfix

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c -o main.o main.cpp
configfix: main.o
	$(CXX) $(CXXFLAGS) -o configfix main.o

install: configfix
	install -m 775 configfix $(PREFIX)/bin/

clean:
	rm -f *.o
