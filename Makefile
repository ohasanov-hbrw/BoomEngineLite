CC = g++
cflags = -std=c++17 -g -O3
cflags += -Ivendor/raylib/src -Iinclude
ldflags += -lstdc++ -Lvendor/raylib/src -lraylib -lpthread -ldl
name = BoomEngine 

sources = $(wildcard src/*.cpp)
objects = $(patsubst src/%, object/%,$(sources:.cpp=.o))
deps = $(objects:.o=.d)

-include $(deps)
.PHONY: all clean

all: files deps $(name)

files:
	mkdir -p bin object

deps:
	cd vendor/raylib/src/ && $(MAKE)
run: $(name)
	mkdir -p beatmaps
	bin/$(name)

$(name): $(objects)
	$(CC) -o bin/$(name) $^ $(ldflags)

object/%.o: src/%.cpp
	$(CC) -MMD -o $@ -c $< $(cflags)

clean:
	rm -rf vendor/raylib/src/*.o vendor/raylib/src/libraylib.a bin/$(name) $(objects) object/*.d vendor/raylib/src/external/glfw/build
