CC := gcc
CFLAGS := -Wall -Wextra -pedantic -Iinclude -std=gnu99 -DNDEBUG
LDFLAGS := -lm
AFFICHAGE_INTERACTIF := -DAFFICHAGE_INTERACTIF

SRC_DIR := src
OBJ_DIR := bin/obj
BIN_DIR := bin

SRCS := $(wildcard $(SRC_DIR)/*.c)
OBJS := $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))
TARGET := $(BIN_DIR)/main

all: $(TARGET)

interactive: CFLAGS += $(AFFICHAGE_INTERACTIF)
interactive: $(TARGET)

debug: CFLAGS += -g 
debug: $(TARGET)

$(OBJ_DIR):
	mkdir -p $@

$(BIN_DIR):
	mkdir -p $@

$(TARGET): $(OBJS) | $(OBJ_DIR) $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -r $(OBJ_DIR)/*.o || true
	rm $(TARGET) || true
	rmdir $(OBJ_DIR) || true
	rmdir $(BIN_DIR) || true

.PHONY: all clean