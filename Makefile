CC		= gcc
CFLAGS	= -MMD -MP -O2
LDFLAGS	=

TARGET 	= bin/bfc
SRCS	= $(wildcard src/*.c)
OBJS	= $(patsubst src/%.c,obj/%.o,$(SRCS))
DEPS	= $(patsubst %.o,%.d,$(OBJS))


all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $^ $(LDFLAGS) -o $@

obj/%.o: src/%.c
	$(CC) -c $(CFLAGS) $< $(LDFLAGS) -o $@

clean:
	rm -f $(OBJS) $(DEPS) $(TARGET)

.PHONY: all clean

-include $(DEPS)