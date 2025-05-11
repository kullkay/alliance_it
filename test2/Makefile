CXX = g++
CXXFLAGS = -std=c++20 -Wall

all: run

run: main.cpp ../test1/flighting_utils.cpp ../test1/flighting_utils.h
	$(CXX) $(CXXFLAGS) main.cpp ../test1/flighting_utils.cpp ../test1/flighting_utils.h -o app
	@echo "Ok: ./app"

clean:
	rm -f *.o test app *out.txt