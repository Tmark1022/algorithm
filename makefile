Src = $(wildcard *.cpp)
Res = $(patsubst %.cpp, %, $(Src))

all:$(Res)

$(Res):%:%.cpp
	g++  $< -o $@ -Wall -g

clean:
	-rm -rf $(Res) 

.PHONY:all







