.POSIX:

BIN = renamer
VERSION = 0.0.1
OBJS = main.o
PREFIX = /usr/local
CC = cc
CFLAGS = -std=c99 -pedantic -O2 \
	  -Wall -Wextra -Wsign-compare -Werror=vla \
	  -fstack-protector-strong -fpie \
	  -D_FORTIFY_SOURCE=2 $(shell pkg-config --libs readline) \
	  $(shell pkg-config --cflags readline) \
	  -DVERSION='"$(VERSION)"'

all: $(BIN)

$(BIN): $(OBJS)
	$(CC) -o $(BIN) $(OBJS) $(CFLAGS)

clean:
	@rm -vf $(BIN)
	@find . -name \*.o -exec rm -v {} +
