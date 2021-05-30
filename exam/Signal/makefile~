CC=g++
CFLAGS=-c -g -Wall `root-config --cflags`
LDFLAGS=`root-config --glibs`
SOURCES=test.cpp PolyPlot.cpp Polynomial.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=test.exe

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@ $(LDFLAGS)

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm ./*~ ./*.o ./main
