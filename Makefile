CC := gcc
CFLAGS := -Wall -Wextra
LDFLAGS := -lm

SRC_DIR := src
BIN_DIR := bin
SRCS := $(wildcard $(SRC_DIR)/*.c)
OBJS := $(patsubst $(SRC_DIR)/%.c, $(BIN_DIR)/%.o, $(SRCS))
TARGET := $(BIN_DIR)/tsp

all: $(TARGET)

$(BIN_DIR):
	mkdir -p $@

$(TARGET): $(BIN_DIR) $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LDFLAGS)

$(BIN_DIR)/%.o: $(SRC_DIR)/%.c | $(BIN_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(BIN_DIR)/*
	rmdir $(BIN_DIR)

.PHONY: all clean