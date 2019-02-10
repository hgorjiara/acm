BASE := ../..
MKDIR_P = mkdir -p
OBJ_DIR = bin

CXX := g++
OUT_FILE := main
OBJECTS := $(patsubst %.cc, ./bin/%.o, $(wildcard *.cc))
CFLAGS := -std=c++11
PHONY += directories

all: directories $(OUT_FILE)

directories: ${OBJ_DIR}
	
${OBJ_DIR}:
	${MKDIR_P} ${OBJ_DIR}
	
$(OUT_FILE): $(OBJECTS)
	$(CXX) -g -o $(OUT_FILE) $+ $(CFLAGS)

${OBJ_DIR}/%.o: %.cc
	$(CXX) -g -c $< -o $@ $(CFLAGS) -L$(BASE)/bin/ -l_cons_comp

PHONY += clean
clean::
	rm -rf $(OBJ_DIR)
	rm -f $(OUT_FILE)

.PHONY: $(PHONY)
