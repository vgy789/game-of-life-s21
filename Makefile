CC=gcc -std=c11 
CFLAGS=-Wall -Wextra -Werror
LDFLAGS=-lncurses

SRCDIR=src
BUILDDIR=build
BINDIR=bin

SRCS=$(SRCDIR)/game_of_life.c $(SRCDIR)/field.c $(SRCDIR)/rules.c $(SRCDIR)/ui.c
OBJS=$(BUILDDIR)/game_of_life.o $(BUILDDIR)/field.o $(BUILDDIR)/rules.o $(BUILDDIR)/ui.o
TARGET=$(BINDIR)/game_of_life

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $@ $(LDFLAGS)

$(BUILDDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILDDIR)/* $(BINDIR)/*

rebuild: clean all
