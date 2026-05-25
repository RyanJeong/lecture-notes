CC      = gcc
CFLAGS  = -ansi -Wall -Wextra -Werror -Wno-trigraphs -trigraphs -fno-builtin
TARGET  = $(notdir $(CURDIR))

SRCS    = main.c itoa.c strdup.c table.c

.PHONY: all clean

all: $(SRCS)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRCS)

clean:
	rm -f *.o $(TARGET)