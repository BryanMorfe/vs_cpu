MKDIR=mkdir -p
RM=rm -r

SRC_DIR=source/
INC_DIR=source/include/
TEST_DIR=tests/
BLD_DIR=build/
OBJ_DIR=$(BLD_DIR)obj/

SRCS=$(wildcard $(SRC_DIR)*.cpp)
SRC_OBJS=$(patsubst $(SRC_DIR)%.cpp,$(OBJ_DIR)%.o,$(SRCS))

TEST_SRCS=$(wildcard $(TEST_DIR)*.cpp)
TEST_OBJS=$(patsubst $(TEST_DIR)%.cpp,$(OBJ_DIR)%.o,$(TEST_SRCS))
TEST_BINS=$(patsubst $(TEST_DIR)%.cpp,$(BLD_DIR)%,$(TEST_SRCS))

GXX=g++
GFLAGS=-std=c++11 -Wall -I$(INC_DIR)

all: run tests

run: $(SRC_OBJS)
	@echo "\e[1;32mLinking $@\e[0m"
	@$(GXX) $(GFLAGS) $^ -o $@

tests: $(TEST_BINS)

$(BLD_DIR)test_%: $(OBJ_DIR)test_%.o $(OBJ_DIR)%.o
	@echo "\e[1;32mLinking $@\e[0m"
	@$(GXX) $(GFLAGS) $^ -o $@

$(OBJ_DIR)%.o: $(SRC_DIR)%.cpp $(OBJ_DIR)
	@echo "\e[1;32mCompiling $@\e[0m"
	@$(GXX) $(GFLAGS) $< -o $@

$(OBJ_DIR)test_%.o: $(TEST_DIR)test_%.cpp $(OBJ_DIR)
	@echo "\e[1;32mCompiling $@\e[0m"
	@$(GXX) $(GFLAGS) $< -o $@

$(BLD_DIR):
	@$(MKDIR) $@

$(OBJ_DIR): $(BLD_DIR)
	@$(MKDIR) $@
