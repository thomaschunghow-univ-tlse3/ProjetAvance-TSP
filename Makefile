INCLUDES := $(wildcard include/*)

CC := gcc
CFLAGS := -Wall -Wextra -pedantic $(foreach dir,$(INCLUDES),-I$(dir)) -D_GNU_SOURCE -std=gnu2x -DNDEBUG
LDFLAGS := -lm
AFFICHAGE_INTERACTIF_2_OPT := -DAFFICHAGE_INTERACTIF_2_OPT
AFFICHAGE_INTERACTIF_GA := -DAFFICHAGE_INTERACTIF_GA
COMPARAISON_RESULTAT := -DCOMPARAISON_RESULTAT

SRC_DIR := src
OBJ_DIR := bin/obj
BIN_DIR := bin

SRCS := $(wildcard $(SRC_DIR)/*/*.c)
OBJS := $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))
OBJS := $(addprefix $(OBJ_DIR)/, $(notdir $(SRCS:.c=.o)))
TARGET := $(BIN_DIR)/main

all: $(TARGET)

interactive_2opt: CFLAGS += $(AFFICHAGE_INTERACTIF_2_OPT)
interactive_2opt: $(TARGET)

interactive_ga: CFLAGS += $(AFFICHAGE_INTERACTIF_GA)
interactive_ga: $(TARGET)

comparaison_resultat: CFLAGS +=  $(COMPARAISON_RESULTAT)
comparaison_resultat:  $(TARGET)

debug: CFLAGS += -g 
debug: $(TARGET)

$(OBJ_DIR):
	mkdir -p $@

$(BIN_DIR):
	mkdir -p $@

$(TARGET): $(OBJS) | $(OBJ_DIR) $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/*/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -r $(OBJ_DIR)/*.o || true
	rm $(TARGET) || true
	rmdir $(OBJ_DIR) || true
	rmdir $(BIN_DIR) || true

.PHONY: all clean
