Src = $(wildcard *.cpp)
Res = $(patsubst %.cpp, %, $(Src))

all:$(Res)

$(Res):%:%.cpp
	g++  $< -o $@ -Wall -g --std=c++11

clean:
	-rm -rf $(Res) 

.PHONY:all







