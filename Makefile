COMPILER := g++
FLAGS := `llvm-config --cxxflags --ldflags --system-libs --libs all`
COMPILE := $(COMPILER)\


TEMP := ./temp

SRC := ./src
BIN := ./bin

STD := ./std
IR := ./IR

SOURCE_DIRS := $(shell find src -type d)
vpath %.cpp $(SOURCE_DIRS)


SOURCE_FILES := $(shell find $(SRC) -name "*.cpp")
DEP_FILES := $(patsubst %.cpp, $(BIN)/%.o, $(notdir $(SOURCE_FILES)))


all: build;


std: std/std.cpp
	clang++ -stdlib=libc++ -S -emit-llvm $^ -o "IR/std.ll"



build: $(BIN)/main.out $(BIN)/tests.out;


run: $(BIN)/main.out
	$(BIN)/main.out


tests: $(BIN)/tests.out
	$(BIN)/tests.out


$(BIN)/main.out:  $(BIN) $(DEP_FILES) main.cpp
	$(COMPILE) main.cpp $(BIN)/*.o  -o $(BIN)/main.out $(FLAGS)


$(BIN)/tests.out: $(BIN) $(DEP_FILES) tests.cpp
	$(COMPILE) tests.cpp $(BIN)/*.o -o $(BIN)/tests.out $(FLAGS)



$(BIN)/%.o: %.cpp
	$(COMPILE) -c $^ -o $@

$(BIN):
	mkdir $(BIN)

$(IR):
	mkdir $(IR)


clean: 
	rm -rf ./bin/*

.PHONY: all build run clean tests std;