CXX = g++
CXXFLAGS = -std=c++17 -Wall

all: test run

flighting_utils.o: flighting_utils.cpp flighting_utils.h
	$(CXX) $(CXXFLAGS) -c flighting_utils.cpp

test: test.cpp flighting_utils.o
	$(CXX) $(CXXFLAGS) test.cpp flighting_utils.o -o test
	./test
	rm -f test

run: main.cpp flighting_utils.o
	$(CXX) $(CXXFLAGS) main.cpp flighting_utils.o -o app
	@echo "Ok: ./app"

clean:
	rm -f *.o test app