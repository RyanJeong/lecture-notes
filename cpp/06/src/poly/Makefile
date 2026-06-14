CC      = g++
CFLAGS  = -std=c++14 -Wall -Wextra -Werror -fno-builtin
TARGET  = $(notdir $(CURDIR))

SRCS    = main.cc person.cc student.cc

.PHONY: all clean

all: $(SRCS)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRCS)

clean:
	rm -f *.o $(TARGET)