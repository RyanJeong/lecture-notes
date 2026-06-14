CC      = g++
CFLAGS  = -std=c++14 -Wall -Wextra -Werror -fno-builtin
INC     = -I../singly-linked-list
TARGET  = $(notdir $(CURDIR))

SRCS    = main.cc

.PHONY: all clean

all: $(SRCS)
	$(CC) $(CFLAGS) $(INC) -o $(TARGET) $(SRCS)

clean:
	rm -f *.o $(TARGET)