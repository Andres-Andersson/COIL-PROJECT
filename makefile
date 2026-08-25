TARGET = COIL-PROJECT

CC = gcc

ALL_DIRS = $(shell find . -type d)
INCLUDES = $(addprefix -I, $(ALL_DIRS))

CFLAGS = -Wall -Wextra -std=c99 -MMD $(INCLUDES)
LDFLAGS = -lncurses

SRCS = $(shell find . -name "*.c")

OBJS = $(SRCS:.c=.o)
DEPS = $(SRCS:.c=.d)

# REGLAS
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
	
-include $(DEPS)

clean:
	rm -f $(OBJS) $(DEPS) $(TARGET)
