CC = gcc
CFLAGS = -Wall -Wextra -Iinc -g

SRC = $(wildcard src/*.c) main.c
OBJ = $(patsubst %.c,build/%.o,$(SRC))

TARGET = app

TEST_SRC = tests/circular_buffer_test.c src/circular_buffer.c
TEST_BIN = test_runner

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

build/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf build $(TARGET)

run: all
	./$(TARGET)

test:
	$(CC) $(CFLAGS) -o $(TEST_BIN) $(TEST_SRC)
	./$(TEST_BIN)


	