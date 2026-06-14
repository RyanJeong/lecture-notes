CC      = gcc
CFLAGS  = -ansi -Wall -Wextra -Werror -Wno-trigraphs -trigraphs -fno-builtin
TARGET  = $(notdir $(CURDIR))

SRCS    = main.c getch.c getop.c stack.c

.PHONY: all clean

all: $(SRCS)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRCS)

clean:
	rm -f *.o $(TARGET)