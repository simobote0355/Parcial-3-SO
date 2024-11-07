# Makefile
CXX = g++
CXXFLAGS = -std=c++17 -Wall
TARGET = lz78_program
OBJ = main.o LZ78Compressor.o

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJ)

main.o: main.cpp LZ78Compressor.h
	$(CXX) $(CXXFLAGS) -c main.cpp

LZ78Compressor.o: LZ78Compressor.cpp LZ78Compressor.h
	$(CXX) $(CXXFLAGS) -c LZ78Compressor.cpp

clean:
	rm -f $(TARGET) $(OBJ)
