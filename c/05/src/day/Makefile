CC      = gcc
CFLAGS  = -ansi -Wall -Wextra -Werror -Wno-trigraphs -trigraphs -fno-builtin
TARGET  = $(notdir $(CURDIR))

SRCS    = main.c day.c month_name.c

.PHONY: all clean

all: $(SRCS)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRCS)

clean:
	rm -f *.o $(TARGET)