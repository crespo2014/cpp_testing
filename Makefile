SRC_DIR := $(CURDIR)
OBJ_DIR := obj
SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))
LDFLAGS := 
CPPFLAGS := -std=c++11
CXXFLAGS := 


$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp 
	g++ $(CPPFLAGS) $(CXXFLAGS) -g -c -o $@ $<
	
cpp_testing: $(SRC_FILES)
	g++  -ggdb -O3 -o "cpp_testing" $(SRC_FILES)
#	$(OBJS) $(USER_OBJS) $(LIBS)
	
all : cpp_testing	