CC      = g++
CFLAGS  = -std=c++14 -Wall -Wextra -Werror -fno-builtin
TARGET  = $(notdir $(CURDIR))

SRCS    = main.cc course_roster.cc course.cc student_schedule.cc student.cc

.PHONY: all clean

all: $(SRCS)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRCS)

clean:
	rm -f *.o $(TARGET)