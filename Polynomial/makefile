all: test.exe

test.exe: test.o Polynomial.o
	g++ -std=c++11 -Wall -o test.exe test.o Polynomial.o

Polynomial.o: Polynomial.cpp Polynomial.h
	g++ -std=c++11 -o Polynomial.o -c Polynomial.cpp

test.o: test.cpp
	g++ -std=c++11 -o test.o -c test.cpp

clean:
	rm *.o *.exe

