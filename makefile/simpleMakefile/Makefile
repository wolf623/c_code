TARGET=makefileversion
CC=gcc
RM=rm
CFLAGS=-g
SRC=$(wildcard *.c)
OBJS=$(SRC:.c=.o)

$(TARGET):$(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

clean:
	$(RM) $(TARGET) $(OBJS)	
