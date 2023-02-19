COMPILER := g++
FLAGS := `llvm-config --cxxflags --ldflags --system-libs --libs all`
COMPILE := $(COMPILER)\


TEMP := ./temp

SRC := ./src
BIN := ./bin

STD := ./std
IR := ./IR

STD_FILES := $(shell find $(STD) -name "*.cpp")
STD_DEP_FILES := $(patsubst %.cpp, $(TEMP)/%.ll, $(notdir $(STD_FILES)))


SOURCE_FILES := $(shell find $(SRC) -name "*.cpp")
DEP_FILES := $(patsubst %.cpp, $(BIN)/%.o, $(notdir $(SOURCE_FILES)))


all: std build run;


std: $(TEMP) $(STD_DEP_FILES)
	llvm-link $(STD_DEP_FILES) -S -o $(IR)/out.ll
	rm -r $(TEMP)
	

$(TEMP)/%.ll: $(STD)/%.cpp
	clang++ -stdlib=libc++ -S -emit-llvm $^ -o $@



build: $(BIN)/main.out $(BIN)/tests.out;


run: $(BIN)/main.out
	$(BIN)/main.out


tests: $(BIN)/tests.out
	$(BIN)/tests.out


./bin/main.out:  $(BIN) $(DEP_FILES) main.cpp
	$(COMPILE) main.cpp $(BIN)/*.o  -o $(BIN)/main.out $(FLAGS)


./bin/tests.out: $(BIN) $(DEP_FILES) tests.cpp
	$(COMPILE) tests.cpp $(BIN)/*.o -o $(BIN)/tests.out $(FLAGS)



$(BIN)/%.o: $(SRC)/%.cpp
	$(COMPILE) -c $^ -o $@

$(BIN)/%.o: $(SRC)/*/%.cpp
	$(COMPILE) -c $^ -o $@


$(BIN):
	mkdir $(BIN)

$(IR):
	mkdir $(IR)

$(TEMP):
	mkdir $(TEMP)



clean: 
	rm -rf ./bin/*

.PHONY: all build run clean tests std;