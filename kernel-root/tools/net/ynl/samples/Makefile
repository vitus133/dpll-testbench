# SPDX-License-Identifier: GPL-2.0

include ../Makefile.deps

JSON_C_DIR=/usr/lib64

CC=gcc
CFLAGS=-std=gnu11 -O2 -W -Wall -Wextra -Wno-unused-parameter -Wshadow \
	-I../lib/ -I../generated/ -idirafter $(UAPI_PATH)
ifeq ("$(DEBUG)","1")
  CFLAGS += -g -fsanitize=address -fsanitize=leak -static-libasan
endif

LDLIBS=-lmnl ../lib/ynl.a ../generated/protos.a
LDFLAGS+= -L$(JSON_C_DIR) -ljson-c

SRCS=$(wildcard *.c)
BINS=$(patsubst %.c,%,${SRCS})

include $(wildcard *.d)

all: $(BINS)

$(BINS): ../lib/ynl.a ../generated/protos.a

clean:
	rm -f *.o *.d *~

hardclean: clean
	rm -f $(BINS)

.PHONY: all clean
.DEFAULT_GOAL=all
