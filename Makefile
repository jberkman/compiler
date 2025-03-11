# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -Wextra -pedantic -std=c11
CPPFLAGS = -Iinclude

# Source files
SRCS = $(wildcard src/*.c)

# Object files directory
OBJDIR = bin

# Object files
OBJS = $(patsubst src/%.c, $(OBJDIR)/%.o, $(SRCS))

# Executable name
EXEC = $(OBJDIR)/jcc

# Default target
all: $(EXEC)

# Link object files to create executable
$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# Compile source files to object files
$(OBJDIR)/%.o: src/%.c | $(OBJDIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

# Create object files directory if it doesn't exist
$(OBJDIR):
	mkdir -p $(OBJDIR)

# Clean up build files
clean:
	rm -f $(OBJS) $(EXEC)
	rmdir $(OBJDIR)

.PHONY: all clean
