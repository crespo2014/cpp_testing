SRC_DIR := $(CURDIR)
OBJ_DIR := ../obj
SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))
LDFLAGS := 
CPPFLAGS := -std=c++11
CXXFLAGS := 

main: $(OBJ_FILES)
	g++  -o "cpp_testing" $(OBJS) $(USER_OBJS) $(LIBS)
	
all:main

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	g++ $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<