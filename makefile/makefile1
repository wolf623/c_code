CC=gcc
RM=rm
CFLAGS=-Wall
LFLAGS=

RELEASE=0
BITS=

ifeq ($(RELEASE),0)
	#debug
	CFLAGS += -g
else
	CFLAGS += -static -O3 -DWOLF
	LFLAGS += -static
endif

TARGET = abc
OBJS = abc.o

all: $(OBJS)
	$(CC) $(OBJS) -o $(TARGET) $(LFLAGS)

abc.o:abc.c
	$(CC) -c abc.c $(CFLAGS)

.PHONY: clean clena
clean:
	-$(RM) -rf *.o $(TARGET)
clena:
	-$(RM) -rf *.o $(TARGET)
	
