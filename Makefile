CXXFLAGS=-g -O3 -std=c++17 -Wall
CXXFLAGS=-g -O0 -std=c++17 -Wall
SRCS=$(wildcard *.cpp)
OBJS=$(SRCS:.cpp=.o)

sorter: $(OBJS)
	g++ $(CXXFLAGS) $(OBJS) -lopencv_imgcodecs -lopencv_core -lopencv_imgproc -L "/usr/local/lib/" -o out

$(OBJS): main.hpp
