# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -Iinclude -lncurses

# Source files
SRCDIR = src
OBJDIR = obj
INCDIR = include

SOURCES = $(SRCDIR)/main.c $(SRCDIR)/render.c
OBJECTS = $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
TARGET = main

# Default rule
all: $(TARGET)

# Linking
$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@ $(CFLAGS)

# Compiling
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR)
	$(CC) -c $< -o $@ $(CFLAGS)

# Clean up
clean:
	rm -rf $(OBJDIR) $(TARGET)

.PHONY: all clean