COMPILER := g++
FLAGS := `llvm-config --cxxflags --ldflags --system-libs --libs all`
COMPILE := $(COMPILER)\

SRC := ./src
BIN := ./bin

SOURCE_FILES := $(shell find src -name "*.cpp")
DEP_FILES := $(patsubst %.cpp, $(BIN)/%.o, $(notdir $(SOURCE_FILES)))


all: build run;


build: $(BIN)/main.out $(BIN)/tests.out;


run: $(BIN)/main.out
	$(BIN)/main.out


tests: $(BIN)/tests.out
	$(BIN)/tests.out


./bin/main.out:  $(BIN) $(DEP_FILES) main.cpp
	$(COMPILE) main.cpp $(BIN)/*.o  -o $(BIN)/main.out $(FLAGS)


./bin/tests.out: $(BIN) $(DEP_FILES) tests.cpp
	$(COMPILE) tests.cpp $(BIN)/*.o -o $(BIN)/tests.out $(FLAGS)



$(BIN)/%.o: src/%.cpp
	$(COMPILE) -c $^ -o $@

$(BIN)/%.o: src/*/%.cpp
	$(COMPILE) -c $^ -o $@


$(BIN):
	mkdir $(BIN)


clean: 
	rm -rf ./bin/*

.PHONY: all build run clean tests;