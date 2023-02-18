COMPILER := g++
FLAGS := -O3
COMPILE := $(COMPILER) $(FLAGS)

INCLUDE_PATH := /usr/include
LIB_PATH := /usr/lib/x86_64-linux-gnu/
LIB_NAME := test

INCLUDE := ./include
SRC := ./src
BIN := ./bin

SOURCE_FILES := $(notdir $(shell find $(SRC) -name "*.cpp"))
DEP_FILES := $(patsubst %.cpp, %.o, $(SOURCE_FILES))

vpath %.hpp $(INCLUDE)
vpath %.cpp $(SRC)
vpath %.o $(BIN)

all: build run;


build: $(BIN)/main.out $(BIN)/tests.out;


run: $(BIN)/main.out
	$(BIN)/main.out

tests: $(BIN)/tests.out
	$(BIN)/tests.out


./bin/main.out:  $(BIN) $(DEP_FILES) main.cpp
	$(COMPILE) main.cpp $(patsubst %, $(BIN)/%, $(DEP_FILES)) -o $(BIN)/main.out

./bin/tests.out: $(BIN) $(DEP_FILES) tests.cpp
	$(COMPILE) tests.cpp $(patsubst %, $(BIN)/%, $(DEP_FILES)) -o $(BIN)/tests.out

%.o: %.cpp
	$(COMPILE) -c $^ -o $(BIN)/$@


$(BIN):
	mkdir $(BIN)


$(INCLUDE_PATH)/$(LIB_NAME): 
	mkdir $(INCLUDE_PATH)/$(LIB_NAME)


install: $(DEP_FILES) $(INCLUDE_PATH)/$(LIB_NAME)
	ar crf $(BIN)/lib$(LIB_NAME).a $(patsubst %, $(BIN)/%, $(DEP_FILES))
	cp -r include/*.hpp $(INCLUDE_PATH)/$(LIB_NAME)
	cp $(BIN)/lib$(LIB_NAME).a $(LIB_PATH)


clean: 
	rm -rf ./bin/*


.PHONY: all build run install clean;