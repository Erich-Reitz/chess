CXX := g++ 
CXXFLAGS := -Wall -Wextra -pedantic-errors -Wno-unused-parameter  -g -std=c++17 
SRC_DIR = ./src
OBJ_DIR := ./obj
SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp) $(wildcard ${SRC_DIR}/pieces/*.cpp)  
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))
LDFLAGS := -lsfml-graphics -lsfml-window -lsfml-system 

PROGRAM_NAME := sfml-app

all: $(OBJ_FILES)
	$(CXX) $(CXXFLAGS) $(OBJ_FILES) $(LDFLAGS) -o $(PROGRAM_NAME)

make: $(OBJ_FILES)
	$(CXX) $(CXXFLAGS) $(OBJ_FILES) $(LDFLAGS) -o $(PROGRAM_NAME)
	./$(PROGRAM_NAME)

sfml-app: $(OBJ_FILES)
	$(CXX) -o ${PROGRAM_NAME} $(OBJ_FILES) $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $^

clean:
	rm -f ${PROGRAM_NAME} $(OBJ_FILES)
	rm -f err.txt
	rm -f ${PROGRAM_NAME}

check:
	cppcheck --enable=all src/ 2> err.txt

format:
	-astyle --style=google --break-blocks=all ${SRC_DIR}/*.*pp ${SRC_DIR}/pieces/*.*pp -xe 
	
	rm -f ${SRC_DIR}/*.orig ${SRC_DIR}/pieces/*.orig

run: $(PROGRAM_NAME)
	./$(PROGRAM_NAME)
	
.PHONY: test 
test: 
	@cd test && ./test.sh

echo:
	echo ${SRC_FILES}
	echo ${OBJ_FILES}