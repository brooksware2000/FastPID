CFLAGS = -Og -g
CPPFLAGS = -I../src
VPATH = ../src
LIBS =
OBJS = FastPID.o

ALL_TESTS = $(wildcard test_*.c)

%.bin: %.o
	@$(CC) $(LDFLAGS) -o $@ $< $(OBJS) $(LIBS)

%.ok: %.bin
	@echo $@
	@./$< > $@ || { rm -f $@; exit 1; }

all: test

test: $(OBJS) $(ALL_TESTS:.c=.ok)
	@echo "All tests passed."

clean:
	rm -f $(ALL_TESTS:.c=.o) $(ALL_TESTS:.c=.bin) $(ALL_TESTS:.c=.ok) $(OBJS)

.PHONY: clean check test all

ifndef VERBOSE
.SILENT:
endif
