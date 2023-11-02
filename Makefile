CC = gcc
CFLAGS = -g -Wall
LIBS = -lSDL2 -ljson-c
SRC_DIR = src
BIN_DIR = bin

SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c,$(BIN_DIR)/%.o,$(SRCS))

$(BIN_DIR)/gymnux: $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS)

$(BIN_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(BIN_DIR)/*.o $(BIN_DIR)/gymnux

