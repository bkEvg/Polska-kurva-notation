CC = gcc
CFLAGS = -std=c11 -Wall -Werror -Wextra

SRC_ARRAY = dynamic_array.c core.c dynamic_array_test.c

BUILD_DIR = ../build

TEST_ARRAY = $(BUILD_DIR)/ArrayTest

all: test_array

test_array: $(TEST_ARRAY)

$(TEST_ARRAY): $(SRC_ARRAY)
	$(CC) $(CFLAGS) -o $(TEST_ARRAY) $(SRC_ARRAY)


clean:
	rm -f $(BUILD_DIR)/*

rebuild: clean all

.PHONY: test_array