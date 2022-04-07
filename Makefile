CXX = g++
CFLAGS = -Wall --std=c++11

all:
	$(CXX) $(CFLAGS) main.cpp NDArray.cpp -o main

run: all
	main.exe
