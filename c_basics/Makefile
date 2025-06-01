# Compiler and Linker
CC = gcc

# Compiler flags
# -Wall: Turn on all warnings (recommended)
# -Wextra: Turn on even more warnings
# -g: Generate debugging information (for GDB)
# -std=c11: Use the C11 standard (or c99, c17, etc.)
# -O2: Optimization level 2 (for release builds, you might use -O0 or -Og for debug)
CFLAGS = -Wall -Wextra -g -std=c11 -O0

# Linker flags (if any, e.g., -lm for math library)
LDFLAGS =

# Executable name
TARGET = flight_sim

# Source files (.c files)
# Automatically find all .c files in the current directory
# SRCS = $(wildcard *.c)
# Or list them explicitly if they are in different locations or you need specific order (not usually)
SRCS = main.c sensor_module.c rudder_control.c command_protocol.c

# Object files (derived from source files, .o)
# This replaces the .c extension with .o for each source file
OBJS = $(SRCS:.c=.o)

# Default target: what happens when you just type 'make'
.PHONY: all
all: $(TARGET)

# Rule to link the executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET) $(LDFLAGS)
	@echo "Build complete: $(TARGET) created."

# Rule to compile .c files into .o files
# $< is an automatic variable representing the first prerequisite (the .c file)
# $@ is an automatic variable representing the target name (the .o file)
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up build files
.PHONY: clean
clean:
	rm -f $(OBJS) $(TARGET)
	@echo "Cleaned up build files."

# Phony targets are targets that are not actual files.
# 'all' and 'clean' are common examples.
.PHONY: help
help:
	@echo "Available targets:"
	@echo "  make all       (or just 'make') Build the project (default)"
	@echo "  make clean     Remove build artifacts"
	@echo "  make help      Show this help message" 