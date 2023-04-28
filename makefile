# If in Windows, load resources
ifeq ($(OS),Windows_NT)
	RES = windres
	RES_FILE = rsc/resources.res
else
	RES_CMD = :
	RES_FILE = :
endif

# Variables
CXX = g++
SRC_DIR = src
OBJS = $(wildcard $(SRC_DIR)/*.cpp) \
	$(wildcard $(SRC_DIR)/syntree/blocks/*.cpp) \
	$(wildcard $(SRC_DIR)/syntree/pieces/*.cpp) \
	$(wildcard $(SRC_DIR)/syntree/statics/*.cpp)
CXXFLAGS = -finput-charset=UTF-8 -static

# Targets
all: cosmica.exe

cosmica.exe: $(OBJS) $(RES_FILE)
	$(CXX) $(CXXFLAGS) $^ -o $@

$(RES_FILE): rsc/resources.rc
	$(RES_CMD) -O coff -i $< -o $@

.PHONY: clean
clean:
	rm -f cosmica.exe $(RES_FILE) $(OBJS)