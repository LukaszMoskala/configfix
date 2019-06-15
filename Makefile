#can be overridden by using 'make CXX=gcc-8' or so
CXX=g++
STRIP=strip
#append these flags to flags passed through command line
override CXXFLAGS+=-O3 --std=c++17 -static -static-libgcc

PREFIX=/usr/local

all: configfix

main.o: main.cpp version.hpp
	$(CXX) $(CXXFLAGS) -c -o main.o main.cpp
configfix: main.o
	$(CXX) $(CXXFLAGS) -o configfix main.o
	$(STRIP) configfix
install: configfix
	install -m 775 configfix $(PREFIX)/bin/

clean:
	rm -f *.o
