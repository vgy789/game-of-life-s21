CC=gcc -std=c11 
CFLAGS=-Wall -Wextra -Werror
LDFLAGS=-lncurses

SRCS=game_of_life.c field.c rules.c ui.c
OBJS=$(SRCS:.c=.o)
TARGET=game_of_life

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $@ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

rebuild: clean all
