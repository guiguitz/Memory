# Install mingw64 to use g++: https://www.mingw-w64.org/downloads/
# Install chocolatey to use Makefile: https://chocolatey.org/install
# Run: choco install make

# Compile: make run
# Clean compilation: make clean

GCC      := C:\msys64\mingw64
CXX      := $(GCC)\bin\g++
CXXFLAGS := -Wall -Wextra -Werror -DDEBUG -g -std=c++0x
LD_LIBRARY_PATH      := $(GCC)/lib64
LDFLAGS  := -L$(LD_LIBRARY_PATH)
TARGET   := main
SRC      := $(wildcard *.cpp)
OBJ      := $(SRC:%.cpp=%.o)


.PHONY: all clean asan ubsan

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJ) $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< $(LDFLAGS)

asan: CXXFLAGS += -fno-omit-frame-pointer -fsanitize=address -fsanitize=leak
asan: all

ubsan: CXXFLAGS += -fsanitize=undefined
ubsan: all

run:
	export LD_LIBRARY_PATH
	@echo
	@echo
	@echo
	./main

clean:
	rm -rf *.o
	rm -rf $(TARGET)
