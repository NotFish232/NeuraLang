COMPILER := g++
FLAGS := -O3
COMPILE := $(COMPILER) $(FLAGS)

SRC := ./src
BIN := ./bin


SOURCE_FILES := $(shell find $(SRC)/ -type f -name '*.cpp')
DEP_FILES := $(patsubst %.cpp, %.o, $(SOURCE_FILES))


all: build run;


build: $(BIN)/main.out $(BIN)/tests.out;


run: $(BIN)/main.out
	$(BIN)/main.out


tests: $(BIN)/tests.out
	$(BIN)/tests.out


./bin/main.out:  $(BIN) $(DEP_FILES) main.cpp
	$(COMPILE) main.cpp $(BIN)/*.o -o $(BIN)/main.out


./bin/tests.out: $(BIN) $(DEP_FILES) tests.cpp
	$(COMPILE) tests.cpp $(BIN)/*.o -o $(BIN)/tests.out


%.o: %.cpp
	$(COMPILE) -c $^ -o $(BIN)/$(notdir $@)


$(BIN):
	mkdir $(BIN)


clean: 
	rm -rf ./bin/*


.PHONY: all build run clean;