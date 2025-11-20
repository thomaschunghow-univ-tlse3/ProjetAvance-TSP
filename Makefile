CC := gcc
CFLAGS := -Wall -Wextra -pedantic -DNDEBUG -Iinclude -std=c99
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

$(OBJ_DIR):
	mkdir -p $@

$(BIN_DIR):
	mkdir -p $@

$(TARGET): $(OBJS) | $(OBJ_DIR) $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -r $(OBJ_DIR)/*.o
	rm $(TARGET)
	rmdir $(OBJ_DIR)
	rmdir $(BIN_DIR)

.PHONY: all clean