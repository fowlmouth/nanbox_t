
SRCS := nanbox.c
OBJS := nanbox.o

LIB_NAME := libnanbox.a
TESTS_BIN_NAME := nanbox-tests

EXTRA_CFLAGS ?= 
CFLAGS = -std=c17 -Iinclude/ -Wall $(EXTRA_CFLAGS)

all: $(LIB_NAME) $(TESTS_BIN_NAME)

$(LIB_NAME): $(OBJS)
	ar rcs $(LIB_NAME) $^

$(TESTS_BIN_NAME): tests.c $(LIB_NAME)
	cc $(CFLAGS) -o $(TESTS_BIN_NAME) $^

clean:
	rm -rf $(OBJS) $(LIB_NAME) $(TESTS_BIN_NAME) 
