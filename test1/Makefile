CXX = g++
CXXFLAGS = -std=c++20 -Wall

all: run

flighting_utils.o: flighting_utils.cpp flighting_utils.h
	$(CXX) $(CXXFLAGS) -c flighting_utils.cpp

run: main.cpp flighting_utils.o
	$(CXX) $(CXXFLAGS) main.cpp flighting_utils.o -o app
	@echo "Ok: ./app"

clean:
	rm -f *.o test app