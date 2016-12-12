ifeq ($(OS),Windows_NT)
	RM = del /s
else
	ifeq ($(shell uname), Linux)
		RM = rm -rf
	endif
endif

src = $(wildcard src/*.cpp) \
	  $(wildcard src/states/*.cpp) \
	  $(wildcard src/media/*.cpp)
obj = $(src:.cpp=.o)

CC = g++

CXXFLAGS = -std=c++14 -O3 -Wall -Wextra -pedantic
LDFLAGS = -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer

Ludum_Dare_37: $(obj)
	$(CC) -o $@ $^  $(LDFLAGS) $(FLAGS)

.PHONY: clean



clean:
	$(RM) /s *.o
	$(RM) *.exe
