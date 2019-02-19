CC=gcc
CXX=g++
CXXFLAGS=-O3 --std=c++17
CFLAGS=-O3
PREFIX=/usr/local

all: configfix

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c -o main.o main.cpp
configfix: main.o
	$(CXX) $(CXXFLAGS) -o configfix main.o

install: configfix
	install -m 775 configfix $(PREFIX)/bin/
