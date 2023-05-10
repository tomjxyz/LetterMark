# Adapted from 
# https://github.com/TheNetAdmin/Makefile-Templates

# tool macros
CC=gcc
CFLAGS=-Wall -iquote../../liblm/include -lhpdf
DBGFLAGS=-g
COBJFLAGS := $(CFLAGS) -c

# path macros
BIN_PATH := bin/release
DBG_PATH := bin/debug
OBJ_PATH := build/release
OBJ_DEBUG_PATH := build/debug
SRC_PATH := src

# compile macros
TARGET_NAME := lmcomp
TARGET := $(BIN_PATH)/$(TARGET_NAME)
TARGET_DEBUG := $(DBG_PATH)/$(TARGET_NAME)

# src files & obj files
SRC := $(foreach x, $(SRC_PATH), $(wildcard $(addprefix $(x)/*,.c*)))
OBJ := $(addprefix $(OBJ_PATH)/, $(addsuffix .o, $(notdir $(basename $(SRC)))))
OBJ_DEBUG := $(addprefix $(OBJ_DEBUG_PATH)/, $(addsuffix .o, $(notdir $(basename $(SRC)))))

# clean files list
DISTCLEAN_LIST := $(OBJ) \
                  $(OBJ_DEBUG)
CLEAN_LIST := $(TARGET) \
			  $(TARGET_DEBUG) \
			  $(DISTCLEAN_LIST) \
			  ../liblm/src/liblm.o \
			  ../liblm/liblm.a

LDFLAGS = -L../liblm -llm

# default rule
all: makedir makelib debug
	@cp $(TARGET_DEBUG) ../public_html/cgi-bin/lmcomp

# non-phony targets
$(TARGET): $(OBJ)
	$(CC) -o $@ $(OBJ) $(CFLAGS) $(LDFLAGS)

$(TARGET_DEBUG): $(OBJ_DEBUG)
	$(CC) $(LDFLAGS) $(CFLAGS) $(DBGFLAGS) $(OBJ_DEBUG) -o $@ $(LDFLAGS)

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c*
	$(CC) $(COBJFLAGS) -o $@ $<

$(OBJ_DEBUG_PATH)/%.o: $(SRC_PATH)/%.c*
	$(CC) $(COBJFLAGS) $(DBGFLAGS) -o $@ $<

$(DBG_PATH)/%.o: $(SRC_PATH)/%.c*
	$(CC) $(COBJFLAGS) $(DBGFLAGS) -o $@ $<

# phony rules
.PHONY: makedir
makedir:
	@mkdir -p $(BIN_PATH) $(OBJ_PATH) $(OBJ_DEBUG_PATH) $(DBG_PATH)

.PHONY: makelib
makelib:
	@cd ../liblm && make

.PHONY: release
release: $(TARGET)

.PHONY: debug
debug: $(TARGET_DEBUG)

.PHONY: clean
clean:
	@echo CLEAN $(CLEAN_LIST)
	@rm -f $(CLEAN_LIST)

.PHONY: distclean
distclean:
	@echo CLEAN $(DISTCLEAN_LIST)
	@rm -f $(DISTCLEAN_LIST)

.PHONY: run
run: default
	@./$(TARGET_DEBUG)
