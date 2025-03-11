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

# Dependency files
DEPS = $(OBJS:.o=.d)

# Executable name
EXEC = $(OBJDIR)/jcc

# Default target
all: $(EXEC)

# Link object files to create executable
$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# Compile source files to object files
$(OBJDIR)/%.o: src/%.c | $(OBJDIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) -MMD -MP -c $< -o $@

# Include dependency files
-include $(DEPS)

# Create object files directory if it doesn't exist
$(OBJDIR):
	mkdir -p $(OBJDIR)

# Clean up build files
clean:
	rm -f $(OBJS) $(EXEC) $(DEPS)
	rmdir $(OBJDIR)

.PHONY: all clean
