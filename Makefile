PROGRAM = ts_utils

GIT_VERSION := $(shell git describe --abbrev=4 --dirty --always --tags)

SRCS := \
	src/ts_utils.c \
	src/msg.c \
	src/opt.c

CC := clang

OBJS = $(SRCS:.c=.o)

CFLAGS = -O0 -Wall -g3 -std=c11 -DGIT_VERSION=\"$(GIT_VERSION)\"

LDFLAGS = -lm

$(PROGRAM): $(OBJS)
	$(CC) $(OBJS) $(LDFLAGS) -o $(PROGRAM)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean

clean:
	rm -f $(PROGRAM) $(OBJS)
