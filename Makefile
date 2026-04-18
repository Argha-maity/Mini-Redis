CC := gcc
CFLAGS := -Wall -Wextra -I./src
SRCDIR := src
BUILDDIR := build
TARGET := server

SRCS := $(wildcard $(SRCDIR)/**/*.c) $(wildcard $(SRCDIR)/*.c)

OBJS := $(patsubst $(SRCDIR)/%.c,$(BUILDDIR)/%.o,$(SRCS))

all: $(TARGET)

$(BUILDDIR)/%.o: $(SRCDIR)/%.c | $(BUILDDIR)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $(TARGET)

client: tests/main.c tests/client.c
	$(CC) $(CFLAGS) $^ -o client

hashmap: src/hashmap/hashmap.c src/lru/lru.c
	$(CC) $(CFLAGS) $^ -o hashmap

lru: src/lru/lru.c
	$(CC) $(CFLAGS) $^ -o lru

# Build a standalone parser test if needed
parser-test: src/parser/parser.c
	$(CC) -DPARSER_TEST $(CFLAGS) $^ -o parser

run-server: $(TARGET)
	./$(TARGET)

run-client: client
	./client

run-hashmap: hashmap
	./hashmap

run-lru: lru
	./lru

clean:
	rm -rf $(BUILDDIR) $(TARGET) client hashmap lru parser

.PHONY: all client hashmap lru parser-test run-server run-client run-hashmap run-lru clean